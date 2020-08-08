#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Graph.h"
#include <regex>
#include <map>
#include <fstream>
#include "Exceptions.h"

#define PROMPT "Gcalc> "
#define VALID "\\s*\\(\\s*[a-zA-Z]+[a-zA-Z0-9]*\\s*([+\\-\\*^]\\s*[a-zA-Z]+[a-zA-Z0-9]*)*\\s*\\)\\s*"
#define VALID_DEF "(\\s*\\s*[!]{0,1}(([!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*)|"\
            "\\s*[!]{0,1}\\{(\\s*[a-zA-Z[;\\]0-9]+\\s*(,\\s*[a-zA-Z[;\\]0-9]+\\s*)*)*"\
            "(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*"\
            "(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*)\\s*"\
            "([+\\-\\*^]\\s*[!]{0,1}(([!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*)|\\s*[!]{0,1}\\{\\s*[a-zA-Z[;\\]0-9]+\\s*"\
            "(,\\s*[a-zA-Z[;\\]0-9]+\\s*)*(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*"\
            "(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*))*\\s*\\s*)"\
            "|(\\s*\\(\\s*[!]{0,1}(([!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*)|"\
            "\\s*[!]{0,1}\\{\\s*[a-zA-Z[;\\]0-9]+\\s*(,\\s*[a-zA-Z[;\\]0-9]+\\s*)*"\
            "(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*"\
            "(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*)\\s*"\
            "([+\\-\\*^]\\s*[!]{0,1}(([!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*)|\\s*[!]{0,1}\\{\\s*[a-zA-Z[;\\]0-9]+\\s*"\
            "(,\\s*[a-zA-Z[;\\]0-9]*\\s*)*(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*"\
            "(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*))*\\s*\\)\\s*)"
#define VALID_OPERATION "\\s*[+\\-\\*^]\\s*"
#define VALID_PARENTHESIS "[\\(\\)]"
#define VARIABLE "\\s*[!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*\\s*"
#define GRAPH_DEF "\\s*[!]{0,1}\\s*\\{\\s*([a-zA-Z[;\\]0-9]+\\s*(,\\s*[a-zA-Z[;\\]0-9]+\\s*)*)*(\\s*\\|\\s*(<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)"\
                "*(\\s*,\\s*<\\s*[a-zA-Z[;\\]0-9]+\\s*,\\s*[a-zA-Z[;\\]0-9]+\\s*>)*)*\\s*\\}\\s*"
#define VALID_VARIABLE "\\s*[a-zA-Z]+[a-zA-Z0-9]*\\s*=\\s*"
#define FUNCTIONS ['!', '+', '^', '*', '-']
#define QUIT "\\s*(quit)\\s*"
#define PRINT "\\s*(print)\\s*\\(\\s*.*\\s*\\)\\s*"
#define DELETE "\\s*(delete)\\s*\\(\\s*.*\\s*\\)\\s*"
#define WHO "\\s*(who)\\s*"
#define RESET "\\s*(reset)\\s*"
#define ARGUMENTS "\\(\\s*.*\\s*\\)"
#define RESERVED_KEYWORD "\\s*(delete)|(print)|(who)|(delete)|(reset)|(quit)\\s*"
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
        std::string current = vertices.substr(0, firstComma);
        // Get the current vertix.
        graph.addVertex(current);
        // Substring.
        vertices.erase(0, current.length()+1);
    }
    // Go through the edges defined.
    std::string edges = command.substr(splitterPos+1, command.length()-1);
    while (!edges.empty() && !errorFlag)
    {
        // Get the first closing and ending tags, with the comma.
        int comma = edges.find(",");
        int openingTag = edges.find("<"), closingTag = edges.find(">");
        int firstVertex = comma-openingTag-1, secondVertex = closingTag-comma-1;
        if (firstVertex < 0 || secondVertex < 0)
        {
            break;
        }
        // Attempt to add.
        graph.addEdge(edges.substr(openingTag+1, firstVertex), edges.substr(comma+1, secondVertex));
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
            throw UnknownVariable(command);
        }
        else
        {
            // We have a valid variable. Fetch the variable.
            current = varTable[command];
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
        }
    }
    if (parenthesis.size() != 0)
    {
        throw IllegalCommand(expression);
    }
    if (*(expression.begin()) != '(')
        depth.push_back(expression);

    // Go through the depths and work accordingly.
    Graph t;
    // Start from the beginning and assess the strings.
    for (auto it = depth.begin();it!=depth.end();++it)
    {
        // Check if the expression is actually valid according to regex.
        // Replace with the current pointer the old substring with the keyword 'temp'
        // Check if we have something before.
        if (it != depth.begin())
        {
            // We can replace.
            *it = it->replace(it->find(*(it-1)), (it-1)->length(), "temp");
        }
        if (!isExpressionValid(*it))
        {
            // Not a valid expression at all. Break completely.
            throw UnknownVariable(*it);
        }
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

        for (auto strit = current.begin(); strit<=current.end() && left <= strit;++strit)
        {
            // Get the current substring.
            bool subDef = false;
            std::string sub = std::string(left, strit);
            // Check if the current sub matches a variable.
            std::smatch match;
            if (std::regex_match(sub, parenthesisExp))
            {
                left = strit;
            }
            else if (std::regex_match(sub, operationExp)|| std::regex_match(sub, defintionExp))
            {
                // Push into the vector.
                commandsSplit.push_back(sub);
                left = strit;
            }
            else if (std::regex_match(sub, variableExp))
            {
                // Check if we have a definition in our command.
                if (std::regex_search(current, match, defintionExp))
                {
                    // Check if the sub is contained within the match.
                    for (auto matchIterator = match.begin(); matchIterator!=match.end();++matchIterator)
                    {
                        if (matchIterator->str().find(sub) != std::string::npos)
                        {
                            // It's a substring.
                            subDef = true;
                            break;
                        }
                    }
                }
                // We might have a continuation to the variable. Go through the variable until we don't have a match.
                if (!subDef)
                {
                    auto varIt = strit+1;
                    while (varIt<=current.end())
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
            }
        }
        t = calculateCommands(commandsSplit, vars, t);
    }
    return t;
}

void saveVariable(std::string key, Graph graph, std::map<std::string, Graph> &varTable)
{
    // Check if the key is already valid.
    if (varTable.count(key) == 0)
    {
        varTable.insert(std::pair<std::string, Graph>(key, graph));
    }
    else
    {
        varTable[key] = graph;
    }
}

void shell(bool automatic)
{
    std::string input = "";
    std::regex defintionExp(VALID_VARIABLE);
    std::regex argumentsExp(ARGUMENTS);
    std::regex variableExp(VARIABLE);
    std::regex quit(QUIT);
    std::regex who(WHO);
    std::regex print(PRINT);
    std::regex deleteExp(DELETE);
    std::regex resetExp(RESET);
    std::regex reservedWord(RESERVED_KEYWORD);
    std::map<std::string, mtm::Graph> varTable;
    while (!std::regex_match(input, quit) && !std::cin.eof())
    {
        try
        {
            if (!automatic)
            {
                std::cout << PROMPT;
            }
            std::getline(std::cin, input);
            std::smatch matches;
            if (std::regex_search(input, matches, defintionExp))
            {
                // Get the matched definition.
                std::string matchedDef = matches[0];
                std::string formattedInput=input.substr(matchedDef.length(), input.length() - matchedDef.length());
                // Remove the whitespaces.
                removeWhitespace(&matchedDef);
                // Get the variable.
                std::smatch matchedVar;
                std::regex_search(matchedDef, matchedVar, variableExp);
                std::string variable = matchedVar[0];
                if (std::regex_match(variable, reservedWord))
                {
                    throw ReservedKeyword(variable);
                }
                // Get the result of the command.
                if (formattedInput.empty())
                {
                    throw IllegalCommand(input);
                }
                Graph result= validateExpression(formattedInput, varTable);
                // Add the result into the variable table.
                saveVariable(variable, result, varTable);
            }
            else if (std::regex_match(input, who))
            {
                // We got a valid who. Print out the map.
                for (auto it = varTable.begin(); it!= varTable.end();++it)
                {
                    std::cout << it->first << std::endl;
                }
            }
            else if (std::regex_search(input, matches, print))
            {
                // Get the matched print.
                std::string matchedPrint = matches[0];
                // Get the matched expression.
                std::smatch matchedArguments;
                std::regex_search(input, matchedArguments, argumentsExp);
                std::string match = matchedArguments[0];
                Graph result= validateExpression(matchedArguments[0], varTable);
                // Add the result into the variable table.
                std::cout << result << std::endl;
            }
            else if (std::regex_search(input, matches, deleteExp))
            {
                // Get the matched expression.
                std::regex_search(input, matches, argumentsExp);
                std::string match = matches[0];
                std::regex_search(match, matches, variableExp);
                match = matches[0];
                if (varTable.count(match) == 0)
                {
                    throw UnknownVariable(match);
                }
                else
                {
                    varTable.erase(match);
                }
            }
            else if (std::regex_match(input, resetExp))
            {
                // Valid reset. Wipe the table.
                varTable.clear();
            }
            else if (!std::regex_match(input, quit) && !input.empty())
            {
                // No recognized command. Throw an error.
                throw IllegalCommand(input);
            }
        }
        catch (const Exception& e)
        {
            std::cout << e.what() <<std::endl;
        }
    }
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
            shell(false);
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        break;
    }
    case 3:
    {
        // Take the arguments and use them accordingly.
        std::fstream outputFile, inputFile;
        outputFile.open(args[2]);
        inputFile.open(args[1]);
        if (!inputFile.is_open())
        {
            std::cerr << "Error: Invalid input file '" << args[1] << "'" << std::endl;
        }
        else if (!outputFile.is_open())
        {
            std::cerr << "Error: Invalid output file '" << args[2] << "'" << std::endl;
        }
        else
        {
            // Change the buffers for the text.
            std::cout.rdbuf(outputFile.rdbuf());
            std::cin.rdbuf(inputFile.rdbuf());
            shell(true);
        }
        outputFile.close();
        inputFile.close();
        break;
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
