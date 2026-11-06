#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void print_container(const T &cont)
{
    bool first = true;
    for (const auto &el : cont)
    {
        if (!first)
        {
            cout << ", ";
        }
        cout << el;
        first = false;
    }
    cout << endl;
}

int main()
{
    set<string> test_set = {"one", "two", "three", "four"};
    print_container(test_set); // four one three two

    list<string> test_list = {"one", "two", "three", "four"};
    print_container(test_list); // one, two, three, four

    vector<string> test_vector = {"one", "two", "three", "four"};
    print_container(test_vector); // one, two, three, four
    return 0;
}