/* 括号匹配 for problem 74 on XDOJ by LyCecilion - C++ version */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if (!(cin >> line))
        return 0;

    vector<char> st;
    st.reserve(line.size());

    auto expected_open = [](char close) -> char {
        switch (close)
        {
            case ')': return '(';
            case ']': return '[';
            case '}': return '{';
            default: return 0;
        } };

    for (char ch : line)
    {
        switch (ch)
        {
            case '(': case '[': case '{':
                st.push_back(ch);
                break;
            case ')': case ']': case '}':
            {
                if (st.empty() || st.back() != expected_open(ch))
                {
                    std::cout << "no\n";
                    return 0;
                }
                st.pop_back();
                break;
            }
        }
    }

    std::cout << (st.empty() ? "yes\n" : "no\n");
    return 0;
}