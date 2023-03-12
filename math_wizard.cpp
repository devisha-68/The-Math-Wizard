#include <bits/stdc++.h>
#include <regex>
#include <string>
#include <cerrno>
#include <cstdlib>
using namespace std;

long double applyOp(long double a, long double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

long double evaluate(string tokens)
{
    float i;
    stack<long double> values;
    stack<char> ops;

    for (i = 0; i < tokens.length(); i++)
    {
        if (tokens[i] == ' ')
            continue;
        else if (tokens[i] == '(')
        {
            ops.push(tokens[i]);
        }

        else if (isdigit(tokens[i]))
        {
            long double val = 0;

            while (i < tokens.length() &&
                   isdigit(tokens[i]))
            {
                val = (val * 10) + (tokens[i] - '0');
                i++;
            }

            values.push(val);
            i--;
        }

        else if (tokens[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                long double val2 = values.top();
                values.pop();

                long double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }

            if (!ops.empty())
                ops.pop();
        }

        else
        {

            while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
            {
                long double val2 = values.top();
                values.pop();

                long double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }

    while (!ops.empty())
    {
        long double val2 = values.top();
        values.pop();
        long double val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("TMW_small_mine.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    while (t--)
    {
        string str;
        cin >> str;
        str = regex_replace(str, std::regex("seven"), "7");
        str = regex_replace(str, std::regex("division"), "/");
        str = regex_replace(str, std::regex("one"), "1");
        str = regex_replace(str, std::regex("two"), "2");
        str = regex_replace(str, std::regex("three"), "3");
        str = regex_replace(str, std::regex("four"), "4");
        str = regex_replace(str, std::regex("five"), "5");
        str = regex_replace(str, std::regex("six"), "6");
        str = regex_replace(str, std::regex("eight"), "8");
        str = regex_replace(str, std::regex("nine"), "9");
        str = regex_replace(str, std::regex("tem"), "10");
        str = regex_replace(str, std::regex("equals"), "=");
        str = regex_replace(str, std::regex("substract"), "-");
        str = regex_replace(str, std::regex("plus"), "+");
        str = regex_replace(str, std::regex("multiple"), "+");
        //cout << str << endl;

        string input,x;

        for (float i = 0; i < str.length(); i++)
        {
            if (str[i] == '=')
                break;
            input += str[i];
        }
        //cout << input << endl;

        long double ans = evaluate(input);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(16) << ans;
        std::string s = stream.str();

        for (int i = 0; i < s.length(); i++)
        {
            s = regex_replace(s, std::regex(".0000000000000000"), "\0");
        }
        //cout << s << endl;

        for (int i = str.length() - 1; str[i] != '='; i--)
        {
            x = x + str[i];
        }
        reverse(x.begin(), x.end());
        /* for(int i=0;i<33-x.length();i++)
        {
            x=x+'0';
        } */
        //cout << x << endl;

        long double val{stold(x)};
        if (ans == val)
        {
            cout << "True\n";
        }
        else
        {
            cout << "False\n";
        }
    }
    // cout << "----" << endl;
    // double pi = 44.6688738857692;
    // std::stringstream stream;
    // stream << std::fixed << std::setprecision(13) << pi;
    // std::string s = stream.str();
    // cout << s << endl;
}
