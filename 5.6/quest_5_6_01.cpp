#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v = {1, 1, 2, 5, 6, 1, 2, 4};
    sort(v.begin(), v.end(), [](const auto &a, const auto &b)
         { return a < b; });
    v.erase(unique(v.begin(), v.end()), v.end());

    for (const auto &el : v)
    {
        cout << el << " ";
    }
    return 0;
}