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
#define VALID "( )*\\(( )*[a-zA-Z]+[a-zA-Z0-9]*( )*([+\\-*^]( )*[a-zA-Z]+[a-zA-Z0-9]*)*( )*\\)( )*"
#define VALID_DEF "( )*[!]*\\(*[!]*((( )*(load)\\(( )*.*( )*\\))|([a-zA-Z]+[a-zA-Z0-9]*)|(( )*\\{( )*("\
                "[a-zA-Z[;\\]0-9]+( )*(,( )*[a-zA-Z[;\\]0-9]*( )*)*)*(( )*\\|( )*(<( )*[a-zA-Z[;\\]0-9]+"\
                "( )*,( )*[a-zA-Z[;\\]0-9]+( )*>)*(( )*,( )*<( )*[a-zA-Z[;\\]0-9]+( )*,( )*[a-zA-Z[;\\]"\
                "0-9]+( )*>)*)*( )*\\}( )*))\\)*(( )*[*+-^]( )*[!]*(\\(*((( )*(load)\\(( )*.*( )*\\))|"\
                "([a-zA-Z]+[a-zA-Z0-9]*)|(( )*\\{( )*([a-zA-Z[;\\]0-9]+( )*(,( )*[a-zA-Z[;\\]0-9]*( )*)*)"\
                "*(( )*\\|( )*(<( )*[a-zA-Z[;\\]0-9]+( )*,( )*[a-zA-Z[;\\]0-9]+( )*>)*(( )*,( )*<( )*[a-zA-Z"\
                "[;\\]0-9]+( )*,( )*[a-zA-Z[;\\]0-9]+( )*>)*)*( )*\\}( )*)))( )*\\)*( )*)*"
#define VALID_OPERATION "( )*[*+-^]( )*"
#define VALID_PARENTHESIS "[\\(\\)]"
#define VARIABLE "( )*[!]{0,1}[a-zA-Z]+[a-zA-Z0-9]*( )*"
#define GRAPH_DEF "( )*[!]{0,1}( )*\\{( )*([a-zA-Z[;\\]0-9]+( )*(,( )*[a-zA-Z[;\\]0-9]+( )*)*)*(( )*\\|"\
                "( )*(<( )*[a-zA-Z[;\\]0-9]+( )*,( )*[a-zA-Z[;\\]0-9]+( )*>)"\
                "*(( )*,( )*<( )*[a-zA-Z[;\\]0-9]+( )*,( )*[a-zA-Z[;\\]0-9]+( )*>)*)*( )*\\}( )*"
#define VALID_VARIABLE "( )*[a-zA-Z]+[a-zA-Z0-9]*( )*=( )*"
#define FUNCTIONS ['!', '+', '^', '*', '-']
#define QUIT "( )*(quit)( )*"
#define PRINT "( )*(print)( )*\\(( )*.*( )*\\)( )*"
#define DELETE "( )*(delete)( )*\\(( )*.*( )*\\)( )*"
#define WHO "( )*(who)( )*"
#define RESET "( )*(reset)( )*"
#define ARGUMENTS "\\(( )*.*( )*\\)"
#define LOAD "( )*[!]{0,1}( )*(load)( )*\\(( )*.*( )*\\)( )*"
#define LOAD_KEYWORD "( )*(load)( )*"
#define SAVE "( )*(save)( )*\\(( )*.+( )*,( )*.+( )*\\)( )*"
#define SAVE_ARGUMENTS "\\(( )*.+( )*,( )*.+( )*\\)"
#define RESERVED_KEYWORD "( )*(delete)|(print)|(who)|(delete)|(reset)|(quit)|(load)|(save)( )*"
#define FILENAME "( )*.+( )*"
using namespace mtm;
std::ofstream outputFile;
std::ifstream inputFile;

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

std::ostream& getOutput()
{
    if (outputFile && outputFile.is_open())
    {
        return outputFile;
    }
    else
    {
        return std::cout;
    }
}

std::istream& getInput()
{
    if (inputFile && inputFile.is_open())
    {
        return inputFile;
    }
    else
    {
        return std::cin;
    }
}

// TODO: Create a function that receives the parameters after the assignment operator. It processes and checks if the given expression is valid, and returns
// the result of the given expression.

bool isExpressionValid(std::string str)
{
    // Check according to regex if it meets the requirements.
    std::regex defExpression(VALID_DEF);
    return std::regex_match(str, defExpression) && str.find("=") == std::string::npos;
}

bool isValidLoad(std::string arguments, std::string load)
{
    // Check if the arguments are valid for a filename.
    std::regex fileExp(FILENAME);
    return std::regex_match(arguments, fileExp) && load.find(arguments)!=std::string::npos;
}

Graph loadBinaryFile(std::string command)
{
    // Format the string.
    removeWhitespace(&command);
    // Remove the load.
    std::string name = std::string(command.begin()+5, command.end()-1);
    // Check if the name is even valid, first of all.
    std::ifstream file(name, std::ios_base::binary);
    if (!file || !file.is_open())
    {
        throw InvalidFilename(name);
    }
    // Get the number of vertices.
    unsigned int vertices = 0, edges=0;
    file.read((char*)&vertices, sizeof(unsigned int));
    file.read((char*)&edges, sizeof(unsigned int));

    Graph g;
    // Go through the actual vertices.
    for (unsigned int i=0;i<vertices;i++)
    {
        unsigned int characters = 0;
        file.read((char*)&characters, sizeof(int));
        // We now need to read the name.
        // Read a char.
        char* item = new char[characters+1];
        file.read((char*)item, sizeof(char)*characters);
        item[characters]='\0';
        g.addVertex(item);
    }

    for (unsigned int i=0;i<edges;i++)
    {
        unsigned int originCharacters = 0;
        file.read((char*)&originCharacters, 4);
        // We now need to read the name.
        // Read a char.
        char* origin = new char[originCharacters+1];
        file.read((char*)origin, originCharacters*sizeof(char));
        origin[originCharacters]='\0';
        unsigned int destChars = 0;
        file.read((char*)&destChars, 4);
        char* dest = new char[destChars];
        file.read((char*)dest, destChars*sizeof(char));
        dest[destChars]='\0';
        g.addEdge(origin, dest);
    }
    file.close();
    return g;
}

Graph createDefinition(std::string command, std::map<std::string, mtm::Graph> varTable)
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
        if(varTable.find(current) != varTable.end()) {
            throw ReservedKeyword(current);
        }
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
    bool define = std::regex_match(command, defintionExp), complement = false;
    std::regex loadExp(LOAD);
    if (std::regex_match(command, loadExp))
    {
        // We have to load the variable.
        if (command.at(0) == '!')
        {
            complement = true;
            command = command.substr(1, command.length()-1);
        }
        // TODO: Function call to read data from file.
        throw InvalidFilename("You have reached here.");
    }
    if (!define)
    {
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
        // Check if we have a complement.
        if (command.at(0) == '!')
        {
            complement = true;
            command = command.substr(1, command.length()-1);
        }
        Graph current = createDefinition(command, varTable);
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
    std::regex loadExp(LOAD);
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
        else if (std::regex_match(*it, loadExp))
        {
            // Remove the load text and grab the file name.
            temp = loadBinaryFile(*it);
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
        else if (expression[i] == '(')
        {
            if (parenthesis.empty())
            {
                // We have an invalid command.
                throw UnknownVariable(expression);
            }
            // Pop the latest index, substring and push into vector.
            int match = parenthesis.top();
            parenthesis.pop();
            depth.push_back(expression.substr(i, match-i + 1));
        }
    }
    if (parenthesis.size() != 0)
    {
        throw UnknownVariable(expression);
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
        // Get the previous item. Check if it meets the regex for loading.
        std::regex loadExp(LOAD);
        // We have to check if the next item is a load. If so, remove the current item from depth.
        std::smatch match;
        if (it+1<depth.end() && std::regex_search(*(it+1), match, loadExp) && match[0].str().find(*it)!=std::string::npos)
        {
            // We have a valid load expression. Remove the current item.
            continue;
        }
        if (it != depth.begin() && !std::regex_search(*it, loadExp))
        {
            // We can replace.
            *it = it->replace(it->find(*(it-1)), (it-1)->length(), "temp");
        }

        if (!isExpressionValid(*it))
        {
            // Not a valid expression at all. Break completely.
            throw UnknownVariable(*it);
        }

        std::string current = *it;
        removeWhitespace(&current);
        std::vector<std::string> commandsSplit;
        auto left = current.begin();
        std::regex variableExp(VARIABLE);
        std::regex defintionExp(GRAPH_DEF);
        std::regex operationExp(VALID_OPERATION);
        std::regex parenthesisExp(VALID_PARENTHESIS);
        std::regex loadKey(LOAD_KEYWORD);
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
                    bool isVar = true;
                    while (varIt<=current.end())
                    {
                        std::string varSub = std::string(left, varIt);
                        if (!std::regex_match(varSub, variableExp))
                        {
                            // The last one is a valid variable.
                            isVar = true;
                            break;
                        }
                        if (std::regex_match(varSub, loadKey))
                        {
                            // We have a valid load keyword. Exit the variable section.
                            isVar = false;
                            break;
                        }
                        ++varIt;
                    }
                    if (isVar)
                    {
                        commandsSplit.push_back(std::string(left, varIt-1));
                        left = varIt-1;
                    }
                    else
                    {
                        strit = varIt;
                    }
                }
            }
            else if (std::regex_match(sub, operationExp)|| std::regex_match(sub, defintionExp) || std::regex_match(sub, loadExp))
            {
                // Push into the vector.
                commandsSplit.push_back(sub);
                left = strit;
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

    std::string input = "init";
    std::regex defintionExp(VALID_VARIABLE);
    std::regex argumentsExp(ARGUMENTS);
    std::regex variableExp(VARIABLE);
    std::regex quit(QUIT);
    std::regex who(WHO);
    std::regex print(PRINT);
    std::regex deleteExp(DELETE);
    std::regex resetExp(RESET);
    std::regex reservedWord(RESERVED_KEYWORD);
    std::regex saveExp(SAVE);
    std::regex saveArguments(SAVE_ARGUMENTS);
    std::map<std::string, mtm::Graph> varTable;
    while (!std::regex_match(input, quit) && !getInput().eof() && !input.empty())
    {
        if (!automatic)
        {
            getOutput() << PROMPT;
            std::getline(std::cin, input);
        }
        else
        {
            std::getline(inputFile, input);
        }
        try
        {
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
                    getOutput() << it->first << std::endl;
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
                getOutput() << result << std::endl;
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
            else if (std::regex_match(input, saveExp))
            {
                // We have a save command. Grab the arguments.
                std::regex_search(input, matches, saveArguments);
                // Get the comma and substring accordingly.
                std::string arguments = matches[0];
                int comma = arguments.find_last_of(',');
                // Substring accordingly.
                std::string expression = arguments.substr(1, comma-1), filename = arguments.substr(comma+1, arguments.length()-comma-2);
                std::regex_search(filename, matches, std::regex("[^ ].+"));
                filename = matches[0];
                Graph g = validateExpression(expression, varTable);
                g.writeBinary(filename);
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
        catch (const mtm::Exception& e)
        {
            getOutput() << e.what() << std::endl;
        }
    }
}


int main(int argCount, char *args[])
{
    switch (argCount)
    {
    case 1:
    {
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
        outputFile.open(args[2]);
        inputFile.open(args[1]);
        if (!inputFile.is_open())
        {
            std::cerr << "Error: Invalid input file '" << args[1] << "'" << std::endl;
        }
        else
        {
            // Change the buffers for the text.
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
