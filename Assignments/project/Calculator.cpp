#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Graph.h"
#include <regex>
#include <map>
#include "GraphException.h"

#define PROMPT "Gcalc> "
#define SHELL_DEF "\\{\\s*[a-zA-Z;[\\]]\\s*(\\s*,\\s*[a-zA-Z;[\\]]\\s*)*\\s*(\\|\\s*(<\\s*[a-zA-Z;[\\]]\\s*,\\s*[a-zA-Z;[\\]]\\s*>)(\\s*,\\s*<\\s*[a-zA-Z;[\\]]\\s*,\\s*[a-zA-Z;[\\]]\\s*>)*)*\\}"
#define DEFINITION "\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*=\\s*"
#define ADDITION "\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*\\+\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*"
#define SUBTRACTION "\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*\\-\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*"
#define MULTIPLICATION "\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*\\*\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*"
#define INTERSECTION "\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*\\^\\s*[a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*\\s*"
#define COMPLEMENT "\\s*![a-zA-Z]+[0-9]*[a-zA-Z0-9]*\\s*=\\s*"
#define PRINT "\\s*(print)\\s*(\\s*\\(\\s*)+([a-zA-Z]+[0-9]*[a-zA-Z0-9]*)(\\s*\\)\\s*)+"
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

void shellMode()
{
    std::regex defRegexp(SHELL_DEF);
    std::regex definitionExp(DEFINITION);
    std::regex additionExp(ADDITION);
    std::regex printExp(PRINT);

    // This will contain all the logic for the shell itself.
    std::string input;
    std::map<std::string, Graph> variables;
    while (toUpper(input) != "QUIT")
    {
        std::cout << PROMPT;
        std::getline(std::cin, input);
        // Handle the logic here.
        Graph temp;
        std::cout << "Input:" << input << std::endl;
        if (std::regex_search(input, defRegexp))
        {
            std::cout << "Valid constructor!!!" << std::endl;
            // Go through the proposed vertices.
            std::smatch definition;
            std::regex_search(input, definition, defRegexp);
            // Go through the given text.
            std::string validText = definition[0];
            validText.erase(std::remove_if(validText.begin(), validText.end(), isspace), validText.end());
            std::cout << "Matched text:" << validText << std::endl;
            // Ignore the curly braces (always in the first and last positions.)
            // Get the position of the splitter.
            int splitterPos = validText.find("|");
            if (splitterPos == -1) splitterPos = validText.length()-1;
            // Go through the vertices. Work from pos 1 to splitterPos-1.
            std::string vertices = validText.substr(1, splitterPos-1);
            bool errorFlag = false;
            // Go through the substring and repeat the process.
            while (!vertices.empty() && !errorFlag) {
                int firstComma = vertices.find(",");
                // Get the current vertix.
                try {
                    temp.addVertex(vertices.substr(0, firstComma));
                }
                catch (const mtm::Exception &e) {
                    std::cout << e.what() << std::endl;
                    errorFlag = true;
                }
                // Substring.
                vertices = vertices.substr(firstComma+1, vertices.length()-1);
            }
            // Go through the edges defined.
            std::string edges = validText.substr(splitterPos+1, validText.length()-1);
            while (!edges.empty() && !errorFlag) {
                // Get the first closing and ending tags, with the comma.
                int comma = edges.find(",");
                int openingTag = edges.find("<"), closingTag = edges.find(">");
                int firstVertex = comma-openingTag-1, secondVertex = closingTag-comma-1;
                // Attempt to add.
                try {
                    temp.addEdge(edges.substr(openingTag+1, firstVertex), edges.substr(comma+1, secondVertex));
                }
                catch (const mtm::Exception &e) {
                    std::cout << e.what() << std::endl;
                    errorFlag = true;
                }
                // Substring accordingly.
                edges = edges.substr(closingTag+2, edges.length()-1);
            }
            if (errorFlag) {
                continue;
            }
            std::cout << temp << std::endl;
        }
        if (std::regex_search(input, definitionExp))
        {
            std::cout << "Valid defintion." << std::endl;
        }

        if (std::regex_search(input, printExp))
        {
            // Print the given variable.
        }
        // std::cout << "Error: Invalid command." << std::endl;
    }
}

int main(int argCount, char *args[])
{
    std::cout << argCount << std::endl;
    if (argCount == 1)
    {
        // SHELL
        shellMode();
    }
    else if (argCount != 3)
    {
        // Error!
        std::cout << "Error: Provide the proper syntax: gcalc input.txt output.txt" << std::endl;
    }
    else
    {
        // Batch mode.
        return 0;
    }
    return 1;
}
