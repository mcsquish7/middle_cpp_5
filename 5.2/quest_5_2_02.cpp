#include <iostream>
#include <string>

using namespace std;

class smart_array
{
private:
    int logical_size;
    int actual_size;
    int* arr;
public:
    smart_array(int size)
    {
        logical_size = 0;
        actual_size = size;
        this->arr = new int[actual_size];
    }
    
    void add_element(int value)
    {
        if (logical_size == actual_size)
        {
            actual_size += logical_size;
            int* new_arr = new int[actual_size];
            for (int i = 0; i < logical_size; ++i)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        arr[logical_size] = value;
        logical_size++;
    }

    string get_element(int idx)
    {
        return to_string(arr[idx]);
    }

    smart_array& operator=(const smart_array& other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] arr;

        logical_size = other.logical_size;
        actual_size = other.actual_size;

        if (actual_size > 0)
        {
            arr = new int[actual_size];
            for (int i = 0; i < logical_size; ++i)
            {
                arr[i] = other.arr[i];
            }
        }
        else
        {
            arr = nullptr;
        }
        return *this;
    }

    ~smart_array()
    {
        delete[] arr;
    }
    

};

int main() {
    setlocale(LC_ALL, "Russian");
 
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);

    smart_array new_arr(2);
    arr.add_element(44);
    arr.add_element(34);

    arr = new_arr;

    return 0;
}
