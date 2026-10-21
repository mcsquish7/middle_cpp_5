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

    ~smart_array()
    {
        delete[] arr;
    }
    

};

int main() {
    setlocale(LC_ALL, "Russian");
    try
    {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        cout << arr.get_element(1) << endl;
    }
    catch (const std::exception& ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}
