
#include <iostream>
#include <algorithm>
#include "bigint.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

int main()
{
    try
    {
        ifstream input("demo.txt");
        if (!input.is_open())
        {
            cout << "Error opening file!";
            return -1;
        }
        string s;             // a string to hold each line
        vector<string> token; // a vector to store each line.
        vector<BigInt> num;   // a vector to store each dight string

        while (getline(input, s))
        {
            token.push_back(s);
        }
        for (size_t i = 0; i < token.size() - 1; i++)
        {
            BigInt temp(token[i]);
            num.push_back(temp);
        }
        string operation = token.back();
        if (operation == "+")
        {
            cout << num[0] << "+" << num[1] << '\n';
            cout << "Result: " << num[0] + num[1] << '\n';
        }
        else if (operation == "+=")
        {

            cout << num[0] << "+=" << num[1] << '\n';
            num[0] += num[1];
            cout << "Result: " << num[0] << '\n';
        }
        else if (operation == "-" && num.size() == 2)
        {
            cout << num[0] << "-" << num[1] << '\n';
            cout << "Result: " << num[0] - num[1] << '\n';
        }
        else if (operation == "-=")
        {

            cout << num[0] << "-=" << num[1] << '\n';
            num[0] -= num[1];
            cout << "Result: " << num[0] << '\n';
        }
        else if (operation == "*")
        {
            cout << num[0] << "*" << num[1] << '\n';
            cout << "Result: " << num[0] * num[1] << '\n';
        }
        else if (operation == "*=")
        {

            cout << num[0] << "*=" << num[1] << '\n';
            num[0] *= num[1];
            cout << "Result: " << num[0] << '\n';
        }
        else if (operation == "-" && num.size() == 1)
        {
            cout << num[0] << '\n';
            -num[0];
            cout << "Result: " << num[0] << '\n';
        }
        else if (operation == "==")
        {
            cout << num[0] << "==" << num[1] << '\n';
            cout << "Result: " << (num[0] == num[1]) << '\n';
        }
        else if (operation == "!=")
        {
            cout << num[0] << "!=" << num[1] << '\n';
            cout << "Result: " << (num[0] != num[1]) << '\n';
        }
        else if (operation == "<")
        {
            cout << num[0] << "<" << num[1] << '\n';
            cout << "Result: " << (num[0] < num[1]) << '\n';
        }
        else if (operation == ">")
        {
            cout << num[0] << ">" << num[1] << '\n';
            cout << "Result: " << (num[0] > num[1]) << '\n';
        }
        else if (operation == "<=")
        {
            cout << num[0] << "<=" << num[1] << '\n';
            cout << "Result: " << (num[0] <= num[1]) << '\n';
        }
        else if (operation == ">=")
        {
            cout << num[0] << ">=" << num[1] << '\n';
            cout << "Result: " << (num[0] >= num[1]) << '\n';
        }
        else if (operation == "=")
        {
            cout << "num1:" << num[0] << "  "
                 << "num2:" << num[1] << '\n';
            cout << "operation: num1 = num2" << '\n';
            num[0] = num[1];
            cout << "num1:" << num[0] << "  "
                 << "num2:" << num[1] << '\n';
        }
        else
        {
            cout << "Please give another valid operation in demo.txt file" << endl;
        }
        input.close();
    }
    catch (const exception &e)
    {
        cout << "Exception caught: " << e.what() << endl;
    }
    return 0;
}