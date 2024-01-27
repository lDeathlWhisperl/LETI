#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include <stack>
#include "func.h"

int getOperationWeight(char operation)
{
    switch (operation)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 0;
    default:
        return -1;
    }
}

int calc(int var_1, int var_2, char operation)
{
    switch (operation)
    {
    case '+':
        return var_1 + var_2;
    case '-':
        return var_1 - var_2;
    case '*':
        return var_1 * var_2;
    }
    return var_1 / var_2;
}

void deleteChar(std::string& str, char ch)
{
    str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}

void toReverseNotation(std::string str, std::string& res, bool isDisplay = true)
{
    std::stack<char> st;
    std::stack<char> st_copy;

    if (isDisplay) std::cout <<
        "+==========+===============+=============================+\n"
        "|   Char   |     Stack     |        Result string        |\n"
        "+==========+===============+=============================+\n";

    std::string num;
    for (size_t i = 0; i < str.length(); i++)
    {
        switch (getOperationWeight(str[i]))
        {
        case 1:
            num = "";
            if (!st.empty() && getOperationWeight(st.top()) == 1)
            {
                res += st.top();
                st.pop();
                res += ' ';
            }
            while (!st.empty() && getOperationWeight(st.top()) == 2)
            {
                res += st.top();
                st.pop();
                res += ' ';
            }
            st.push(str[i]);
            break;

        case 2:
            num = "";
            while (!st.empty() && getOperationWeight(st.top()) == 2)
            {
                res += st.top();
                st.pop();
                res += ' ';
            }
            st.push(str[i]);
            break;

        case 0:
            num = "";
            if (str[i] == ')')
                while (st.size())
                {
                    if (st.top() == '(')
                    {
                        st.pop();
                        break;
                    }
                    res += st.top();
                    st.pop();
                    res += ' ';
                }
            else
                st.push(str[i]);
            break;

        case -1:
            res += str[i];
            num += str[i];
            if (getOperationWeight(str[i + 1]) > -1)
                res += ' ';
        }
        
        st_copy = st;
        if (isDisplay)
            if (num.length() && (getOperationWeight(str[i + 1]) > -1 || i == str.length() - 1))
            {
                std::cout << "| " << std::left << std::setw(8) << num << " | ";// << std::setw(14);
                while (!st_copy.empty())
                {
                    std::cout << st_copy.top() << ',';
                    st_copy.pop();
                }
                std::cout << "| " << std::setw(28) << res << "|\n";
            }
            else if (!num.length())
            {
                std::cout << "| " << std::left << std::setw(8) << str[i] << " | ";// << std::setw(14);
                while (!st_copy.empty())
                {
                    std::cout << st_copy.top() << ',';
                    st_copy.pop();
                }
                std::cout << "| " << std::setw(28) << res << "|\n";

            }
        
    }

    if (isDisplay) std::cout <<
        "+==========+===============+=============================+\n\nAttach the stack in reverse order to the output line: ";

    if (res[res.length() - 1] == ' ')
        res.pop_back();

    while (st.size())
    {
        res += ' ';
        res += st.top();
        st.pop();
    }

    if (isDisplay)
        std::cout << res << "\n\n\nThe initial expression: " << str << "\nThe reverse polish notation: " << res << '\n';
}

int solveExpression(std::string str)
{
    std::stack<int> numbers;
    std::string expression, num;

    toReverseNotation(str, expression, false);
    size_t size = expression.length();

    for (size_t i = 0; i < size; i++)
    {
        if (expression[i] == ' ')
        {
            if (num.length())
                numbers.push(std::stoi(num));
            num = "";
            continue;
        }

        if (isdigit(expression[i]))
            num += expression[i];

        if (getOperationWeight(expression[i]) >= 1)
        {
            int var_2 = numbers.top();
            numbers.pop();
            int var_1 = numbers.top();
            numbers.pop();

            int res = calc(var_1, var_2, expression[i]);
            numbers.push(res);
        }
    }
    return numbers.top();
}

bool isMistake(std::string str)
{
    size_t size = str.length();
    int brackets = 0;

    if (size == 0)
        return true;

    //if the first or the most recent character is an operation
    if (getOperationWeight(str[0]) >= 1 || getOperationWeight(str[size - 1]) >= 1)
        return true;

    for (size_t i = 0; i < size; i++)
    {
        //all characters except +,-,*,/
        if (!isalnum(str[i]) && getOperationWeight(str[i]) < 0)
            return true;

        //if two variables are neighbours
        if (isalpha(str[i]) && isalpha(str[i + 1]))
            return true;

        //if '(' is followed by an operation 
        if (str[i] == '(' && getOperationWeight(str[i + 1]) >= 0)
            return true;

        //if an operation is followed by ')'
        if (getOperationWeight(str[i]) >= 0 && str[i + 1] == ')')
            return true;

        //if two operations are neighbours
        if (getOperationWeight(str[i]) >= 1 && getOperationWeight(str[i + 1]) >= 1)
            return true;

        if (str[i] == '(')
            brackets++;
        if (str[i] == ')')
            brackets--;

        //if the first bracket is the closing one
        if (brackets < 0)
            return true;
    }
    //checking an even bracket count
    if (brackets)
        return true;

    return false;
}

void varInit(std::string& str)
{
    int num = NULL;
    std::string res;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        while (isalpha(str[i]))
        {
            std::cout << "Please init the variable " << str[i] << " = ";
            std::cin >> num;
            if (num != NULL)
                break;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }
        }
        if (num != NULL)
            res += std::to_string(num);
        else
            res += str[i];
        num = NULL;
    }

    str = res;
}

void mainMenu()
{
    std::string str, res = "";
    std::cout << "Input an expression: ";
    getline(std::cin, str);
    deleteChar(str, ' ');
    
    if (!isMistake(str))
    {
        varInit(str);
        toReverseNotation(str, res);
    }
    else
        std::cout << "you entered the wrong expression";
    
}