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

// TODO: Create a function that receives the parameters after the assignment operator. It processes and checks if the given expression is valid, and returns
// the result of the given expression.

bool isExpressionValid(std::string str)
{
    // Check according to regex if it meets the requirements.
    std::regex expression(VALID);
    return std::regex_match(str, expression);
}

Graph validateExpression(std::string expression)
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
    }
    return Graph();
}

int main(int argCount, char *args[])
{
    // std::cout << argCount << std::endl;
    if (argCount == 1)
    {
        // SHELL
        try
        {
            validateExpression("(G3+ (G1))");
        }
        catch (const Exception& e)
        {
            std::cout << e.what() << std::endl;
        }

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
