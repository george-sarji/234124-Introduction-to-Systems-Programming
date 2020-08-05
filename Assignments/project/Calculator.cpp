#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Graph.h"
#include <regex>
#include <map>

#define PROMPT "Gcalc> "
#define SHELL_DEF "\\{\\s*[a-z,A-Z,;[\\]]\\s*(\\s*,\\s*[a-z,A-Z,;[\\]]\\s*)*\\s*(\\|\\s*(<\\s*[a-z,A-Z,;[\\]]\\s*,\\s*[a-z,A-Z,;[\\]]\\s*>)(\\s*,\\s*<\\s*[a-z,A-Z,;[\\]]\\s*,\\s*[a-z,A-Z,;[\\]]\\s*>)*)*\\}"

using namespace mtm;

std::string toUpper(std::string str)
{
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        *it = std::toupper(*it);
    }
    return str;
}

void shellMode()
{
    std::regex defRegexp(SHELL_DEF);
    // This will contain all the logic for the shell itself.
    std::cout << PROMPT;
    std::string input;
    std::getline(std::cin, input);

    while (toUpper(input) != "EXIT")
    {
        // Handle the logic here.
        std::cout << toUpper(input) << std::endl;
        if (input == "")
        {
            std::cout << PROMPT;
            std::getline(std::cin, input);
            continue;
        }
        if (std::regex_match(input, defRegexp))
        {
            std::cout << "Valid constructor!!!" << std::endl;
        }

        else
        {
            std::cout << "Error: Invalid command." << std::endl;
        }
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
    else
    {
        // BATCH
        return 0;
    }
    return 1;
}
