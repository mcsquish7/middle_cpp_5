#include <iostream>

template <typename T>
class unique_ptr
{
public:
    unique_ptr(T *ptr = nullptr) : m_ptr(ptr) {}

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;

    ~unique_ptr()
    {
        delete m_ptr;
    }

    T &operator*() const
    {
        return *m_ptr;
    }

    T *release()
    {
        T *tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

private:
    T *m_ptr;
};

int main()
{
    unique_ptr<int> p(new int(91));

    std::cout << *p << '\n';

    int *raw = p.release();
    std::cout << *raw << '\n';

    delete raw;

    return 0;
}