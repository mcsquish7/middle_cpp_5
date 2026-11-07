#include <iostream>
#include <string>
#include <vector>

template <class T>
void move_vectors(std::vector<T> &from, std::vector<T> &to)
{
    to = std::move(from);
}

int main()
{
    std::vector<std::string> one = {"test_string1", "test_string2"};
    std::vector<std::string> two;

    move_vectors(one, two);

    std::cout << "two size: " << two.size() << '\n';
    std::cout << "one size: " << one.size() << '\n';

    for (const auto &s : two)
        std::cout << s << '\n';

    return 0;
}