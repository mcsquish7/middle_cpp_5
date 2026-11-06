#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    unordered_map<char, int> m;
    string str = "Hello world!";

    for (const auto &el : str)
    {
        m[el]++;
    }

    vector<pair<char, int>> vec(m.begin(), m.end());

    sort(vec.begin(), vec.end(),
         [](const pair<char, int> &a, const pair<char, int> &b)
         {
             return a.second > b.second;
         });

    for (const auto &el : vec)
    {
        cout << el.first << ": " << el.second << endl;
    }

    return 0;
}