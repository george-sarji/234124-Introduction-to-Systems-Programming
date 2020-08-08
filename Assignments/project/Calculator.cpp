#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Graph.h"
#include <regex>
#include <map>
#include "GraphException.h"
#include <stdlib.h>

#define PROMPT "Gcalc> "
#define VALID "\\s*\\(\\s*[a-zA-Z]+[a-zA-Z0-9]*\\s*([+\\-\\*^]\\s*[a-zA-Z]+[a-zA-Z0-9]*)*\\s*\\)\\s*"
#define VALID_DEF "\\s*\\(\\s*[!]{0,1}(([!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*)|"\
            "\\s*[!]{0,1}\\{\\s*[a-zA-Z[;\\]0-9]+\\s*(,\\s*[a-zA-Z[;\\]0-9]*\\s*)*"\
            "(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*"\
            "(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*)\\s*"\
            "([+\\-\\*^]\\s*[!]{0,1}(([!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*)|\\s*[!]{0,1}\\{\\s*[a-zA-Z[;\\]0-9]+\\s*"\
            "(,\\s*[a-zA-Z[;\\]0-9]*\\s*)*(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*"\
            "(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*))*\\s*\\)\\s*"
#define VALID_OPERATION "\\s*[+\\-\\*^]\\s*"
#define VALID_PARENTHESIS "[\\(\\)]"
#define VARIABLE "\\s*[!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*\\s*"
#define GRAPH_DEF "\\s*[!]{0,1}\\s*\\{\\s*[a-zA-Z[;\\]0-9]+\\s*(,\\s*[a-zA-Z[;\\]0-9]*\\s*)*(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)"\
                "*(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*"
#define FUNCTIONS ['!', '+', '^', '*', '-']
using namespace mtm;

std::string toUpper(std::string str)
{
    std::string newStr;
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        newStr += std::toupper(*it);
    }
    return newStr;
}

void removeWhitespace(std::string *str)
{
    str->erase(std::remove_if(str->begin(), str->end(), isspace), str->end());
}

// TODO: Create a function that receives the parameters after the assignment operator. It processes and checks if the given expression is valid, and returns
// the result of the given expression.

bool isExpressionValid(std::string str)
{
    // Check according to regex if it meets the requirements.
    std::regex defExpression(VALID_DEF);
    return std::regex_match(str, defExpression);
}

Graph createDefinition(std::string command)
{
    Graph graph;
    int splitterPos = command.find("|");
    if (splitterPos == -1) splitterPos = command.length()-1;
    // Go through the vertices. Work from pos 1 to splitterPos-1.
    std::string vertices = command.substr(1, splitterPos-1);
    bool errorFlag = false;
    // Go through the substring and repeat the process.
    while (!vertices.empty() && !errorFlag)
    {
        int firstComma = vertices.find(",");
        // Get the current vertix.
        try
        {
            graph.addVertex(vertices.substr(0, firstComma));
        }
        catch (const mtm::Exception &e)
        {
            throw(e);
        }
        // Substring.
        vertices = vertices.substr(firstComma+1, vertices.length()-1);
    }
    // Go through the edges defined.
    std::string edges = command.substr(splitterPos+1, command.length()-1);
    while (!edges.empty() && !errorFlag)
    {
        // Get the first closing and ending tags, with the comma.
        int comma = edges.find(",");
        int openingTag = edges.find("<"), closingTag = edges.find(">");
        int firstVertex = comma-openingTag-1, secondVertex = closingTag-comma-1;
        // Attempt to add.
        try
        {
            graph.addEdge(edges.substr(openingTag+1, firstVertex), edges.substr(comma+1, secondVertex));
        }
        catch (const mtm::Exception &e)
        {
            throw(e);
        }
        // Substring accordingly.
        edges = edges.substr(closingTag+2, edges.length()-1);
    }
    return graph;

}

Graph fetchVariable(std::string command, std::map<std::string, Graph> varTable, Graph temp)
{
    std::regex defintionExp(GRAPH_DEF);
    bool define = std::regex_match(command, defintionExp);
    if (!define)
    {
        bool complement=false;
        if (command.at(0) == '!')
        {
            complement = true;
            command = command.substr(1, command.length()-1);
            std::cout << command << std::endl;
        }
        Graph current;
        if (command == "temp")
        {
            current = temp;
        }
        // Fetch the variable from the vartable.
        else if (varTable.count(command) == 0)
        {
            // Unknown variable.
            throw UnknownVariable();
        }
        else
        {
            // We have a valid variable. Fetch the variable.
            Graph current = varTable[command];
        }
        // Check if it's a complement.
        if (complement)
        {
            // Change to a complement.
            current = !current;
        }
        return current;
    }
    else
    {
        bool complement = false;
        // Check if we have a complement.
        if (command.at(0) == '!')
        {
            complement = true;
            command = command.substr(1, command.length()-1);
        }
        Graph current = createDefinition(command);
        if (complement)
        {
            current = !current;
        }
        // Check if we initiated.
        return current;
    }
    return Graph();
}


Graph calculateCommands(std::vector<std::string> commands, std::map<std::string, mtm::Graph> varTable, Graph graph)
{
    std::regex variableExp(VARIABLE);
    std::regex defintionExp(GRAPH_DEF);
    std::regex operationExp(VALID_OPERATION);
    bool initiated=false;
    Graph temp;
    // Go through the vector.
    for (auto it = commands.begin();it!=commands.end();++it)
    {
        // Check if we have a variable.
        if (std::regex_match(*it, variableExp) || std::regex_match(*it, defintionExp))
        {
            Graph current = fetchVariable(*it, varTable, graph);
            // Check if we initiated already.
            if (!initiated)
            {
                temp = temp + current;
            }
        }
        else if (std::regex_match(*it, operationExp))
        {
            // We have a valid operation. Get the next variable in line.
            std::string command = *it;
            ++it;
            // Get the next variable.
            Graph next = fetchVariable(*it, varTable, graph);
            if (command == "+")
            {
                temp = temp + next;
            }
            if (command == "-")
            {
                temp = temp - next;
            }
            if (command == "^")
            {
                temp = temp ^ next;
            }
            if (command == "*")
            {
                temp = temp*next;
            }
        }
    }

    return temp;
}


Graph validateExpression(std::string expression, std::map<std::string, mtm::Graph> vars)
{
    // Go through the expression, check for the parenthesis and work by order.
    int currentOpening = 0;
    auto left = expression.begin();
    auto right = expression.end()-1;
    std::vector<std::string> depth;
    std::stack<int> parenthesis;
    for (int i = expression.length()-1; i>= 0;i--)
    {
        if (expression[i] == ')')
        {
            // Push into the stack.
            parenthesis.push(i);
        }
        if (expression[i] == '(')
        {
            // Pop the latest index, substring and push into vector.
            int match = parenthesis.top();
            parenthesis.pop();
            depth.push_back(expression.substr(i, match-i + 1));
            // std::cout << *(depth.end()-1) << std::endl;
        }
    }
    if (*(expression.begin()) != '(')
        depth.push_back(expression);

    // Go through the depths and work accordingly.
    Graph t;
    // Start from the beginning and assess the strings.
    for (auto it = depth.begin();it!=depth.end();++it)
    {
        std::cout << "Current string: " << *it << std::endl;
        // Check if the expression is actually valid according to regex.
        // Replace with the current pointer the old substring with the keyword 'temp'
        // Check if we have something before.
        if (it != depth.begin())
        {
            // We can replace.
            int index = it->find(*(it-1));
            *it = it->replace(it->find(*(it-1)), (it-1)->length(), "temp");
        }
        if (!isExpressionValid(*it))
        {
            // Not a valid expression at all. Break completely.
            throw IllegalCommand();
        }
        std::cout << isExpressionValid(*it);
        // TODO: Add the value calculation logic here. Also add the variable table. Also add the DEFINITION regex
        // TODO: Make a string splitter according to spaces or regex, split up the current string into seperate keywords.
        std::string current = *it;
        removeWhitespace(&current);
        std::vector<std::string> commandsSplit;
        auto left = current.begin();
        std::regex variableExp(VARIABLE);
        std::regex defintionExp(GRAPH_DEF);
        std::regex operationExp(VALID_OPERATION);
        std::regex parenthesisExp(VALID_PARENTHESIS);

        for (auto strit = current.begin(); strit!=current.end() && left <= strit;++strit)
        {
            // Get the current substring.
            std::string sub = std::string(left, strit);
            // Check if the current sub matches a variable.
            if (std::regex_match(sub, parenthesisExp))
            {
                left = strit;
            }
            if (std::regex_match(sub, variableExp))
            {
                // We might have a continuation to the variable. Go through the variable until we don't have a match.
                auto varIt = strit+1;
                while (varIt!=current.end())
                {
                    std::string varSub = std::string(left, varIt);
                    if (!std::regex_match(varSub, variableExp))
                    {
                        // The last one is a valid variable.
                        break;
                    }
                    ++varIt;
                }
                commandsSplit.push_back(std::string(left, varIt-1));
                left = varIt-1;
            }
            else if (std::regex_match(sub, operationExp)|| std::regex_match(sub, defintionExp))
            {
                // Push into the vector.
                sub.erase(std::remove_if(sub.begin(), sub.end(), isspace), sub.end());
                commandsSplit.push_back(sub);
                left = strit;
            }
        }
        // Iterate through the string that we have.
        // Each iteration, check for a substring regexp hit for function, variable or definition
        // If function, throw error except for complement
        // If variable, look for variable in varmap. If no result, throw error.
        // Substring the regexp hit from current and carry on with iterations
        // If last hit was operation, look for variable. 
        // Go through the commands vector.
        t = calculateCommands(commandsSplit, vars, t);
        std::cout << t;
    }
    return Graph();
}

int main(int argCount, char *args[])
{
    // std::cout << argCount << std::endl;
    switch (argCount)
    {
    case 1:
    {
        std::map<std::string, mtm::Graph> vars;
        // SHELL
        try
        {
            validateExpression("(!{a,b|<a,b>} + {c,d} + !({f,g}*{e,h}))", vars);
        }
        catch (const Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        break;
    }
    case 3:
    {
        // BATCH
    }
    default:
    {
        std::cerr << "Error: Use the proper syntax gcalc OR gcalc in.txt out.txt" << std::endl;
        break;
    }
    }
    return 1;
}
