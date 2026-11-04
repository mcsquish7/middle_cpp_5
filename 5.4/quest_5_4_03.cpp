#include <iostream>
#include <vector>

using namespace std;

class DivByThreeCounter
{
public:
    void operator()(int x)
    {
        if (x % 3 == 0)
        {
            sum += x;
            ++count;
        }
    }

    int get_sum() const { return sum; }
    int get_count() const { return count; }

private:
    int sum = 0;
    int count = 0;
};

int main()
{
    DivByThreeCounter counter;

    vector<int> vec = {4, 1, 3, 6, 25, 54};

    for (auto el : vec)
    {
        counter(el);
    }

    cout << "get_sum() = " << counter.get_sum() << endl;
    cout << "get_count() = " << counter.get_count() << endl;

    return 0;
}