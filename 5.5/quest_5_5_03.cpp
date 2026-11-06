#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class MyVector
{
private:
    T *data;
    int sz;
    int cap;

public:
    MyVector()
    {
        data = nullptr;
        sz = 0;
        cap = 0;
    }

    ~MyVector()
    {
        delete[] data;
    }

    void push_back(T value)
    {
        if (sz == cap)
        {
            int newCap;
            if (cap == 0)
                newCap = 1;
            else
                newCap = cap * 2;

            T *newData = new T[newCap];
            for (int i = 0; i < sz; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;

            data = newData;
            cap = newCap;
        }
        data[sz] = value;
        sz++;
    }

    T &at(int index)
    {
        if (index < 0 || index >= sz)
        {
            throw out_of_range("index out of range");
        }
        return data[index];
    }

    int size()
    {
        return sz;
    }

    int capacity()
    {
        return cap;
    }
};

int main()
{
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "size = " << v.size() << endl;
    cout << "cap  = " << v.capacity() << endl;

    for (int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;

    try
    {
        v.at(100);
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
    }
}