#include <iostream>
#include <set>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int num = 0, val;
    cin >> num;
    set<int> s;
    for (int i = 0; i < num; i++)
    {
        cin >> val;
        s.insert(val);
    }

    for (auto it = s.rbegin(); it != s.rend(); ++it)
    {
        cout << *it << endl;
    }
    return 0;
}