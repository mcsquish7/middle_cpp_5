#include <iostream>
#include <stdexcept>

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
        if (m_ptr == nullptr)
            throw std::runtime_error("dereferencing null unique_ptr");
        return *m_ptr;
    }

    T *operator->() const
    {
        if (m_ptr == nullptr)
            throw std::runtime_error("dereferencing null unique_ptr");
        return m_ptr;
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

struct point
{
    int x;
    int y;
};

int main()
{
    unique_ptr<int> p(new int(91));

    std::cout << *p << '\n';

    int *raw = p.release();
    std::cout << *raw << '\n';
    delete raw;

    unique_ptr<int> empty;
    try
    {
        std::cout << *empty << '\n';
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "error: " << e.what() << '\n';
    }

    unique_ptr<point> pt(new point{3, 4});
    std::cout << pt->x << ' ' << pt->y << '\n';

    return 0;
}