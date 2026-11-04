#include <iostream>
#include <vector>

using namespace std;

template <class T>
T power(T a)
{
    return a * a;
}
template <class T>
vector<T> power(vector<T> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec.at(i) *= vec.at(i);
    }
    return vec;
}

int main()
{
    int a = 4;
    vector<int> vec = {-1, 4, 8};

    cout << "[IN]: " << a << endl;
    cout << "[OUT]: " << power(a) << endl;

    cout << "[IN]: ";
    for (int i = 0; i < vec.size(); i++)
    {
        if (i != vec.size() - 1)
            cout << vec.at(i) << ", ";
        else
            cout << vec.at(i) << endl;
    }
    cout << "[OUT]: ";
    vec = power(vec);
    for (int i = 0; i < vec.size(); i++)
    {
        if (i != vec.size() - 1)
            cout << vec.at(i) << ", ";
        else
            cout << vec.at(i) << endl;
    }

    return 0;
}