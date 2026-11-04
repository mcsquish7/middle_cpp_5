#include <iostream>
#include <vector>

using namespace std;

template <class T>
class table
{
public:
    table(int rows, int cols)
    {
        vec.assign(rows, vector<T>(cols));
    }

    vector<T> &operator[](int i)
    {
        return vec[i];
    }

    const vector<T> &operator[](int i) const
    {
        return vec[i];
    }

private:
    vector<vector<T>> vec;
};

int main()
{
    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0]; // выводит 4
    return 0;
}