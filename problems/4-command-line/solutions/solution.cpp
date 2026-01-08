/* 命令行选项 for problem 4 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    string line;
    if (!getline(cin, line)) return 0;

    istringstream iss(line);
    set<string> options;

    string token;
    while (iss >> token)
    {
        if (!token.empty() && token.front() == '-')
            options.insert(token);
    }

    if (options.empty())
    {
        std::cout << "no\n";
        return 0;
    }

    bool first = true;
    for (const auto& opt : options)
    {
        if (!first)
            first = false;
        else
            std::cout << ' ';
        std::cout << opt;
    }

    std::cout << '\n';
    return 0;
}
