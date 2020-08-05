#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Graph.h"
#include <regex>
#include <map>

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
    std::cout << PROMPT;
    std::string input;
    std::getline(std::cin, input);
    std::map<std::string, Graph> variables;
    while (toUpper(input) != "QUIT")
    {
        // Handle the logic here.
        Graph temp;
        std::cout << "Input:" << input << std::endl;
        if (std::regex_search(input, defRegexp))
        {
            std::cout << "Valid constructor!!!" << std::endl;
            // Check if we have a valid middle splitter.
        }
        if (std::regex_search(input, definitionExp))
        {
            std::cout << "Valid defintion." << std::endl;
        }

        if (std::regex_search(input, printExp))
        {
            // Print the given variable.
        }
        std::cout << PROMPT;
        std::getline(std::cin, input);
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
