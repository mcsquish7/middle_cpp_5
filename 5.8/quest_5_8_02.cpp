#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

class big_integer
{
public:
    big_integer() : m_digits("0") {}

    big_integer(const std::string &value) : m_digits(value) {}

    big_integer(const big_integer &) = default;
    big_integer &operator=(const big_integer &) = default;

    big_integer(big_integer &&other) noexcept
        : m_digits(std::move(other.m_digits))
    {
        other.m_digits = "0";
    }

    big_integer &operator=(big_integer &&other) noexcept
    {
        if (this != &other)
        {
            m_digits = std::move(other.m_digits);
            other.m_digits = "0";
        }
        return *this;
    }

    friend big_integer operator+(const big_integer &a, const big_integer &b)
    {
        std::string result;
        int i = static_cast<int>(a.m_digits.size()) - 1;
        int j = static_cast<int>(b.m_digits.size()) - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry != 0)
        {
            int sum = carry;
            if (i >= 0)
                sum += a.m_digits[i--] - '0';
            if (j >= 0)
                sum += b.m_digits[j--] - '0';

            result.push_back(static_cast<char>('0' + sum % 10));
            carry = sum / 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    friend big_integer operator*(const big_integer &a, int multiplier)
    {
        if (multiplier == 0 || a.m_digits == "0")
            return big_integer("0");

        std::string result;
        long long carry = 0;

        for (int i = static_cast<int>(a.m_digits.size()) - 1;
             i >= 0 || carry != 0;
             --i)
        {
            long long cur = carry;
            if (i >= 0)
                cur += (a.m_digits[i] - '0') * 1LL * multiplier;

            result.push_back(static_cast<char>('0' + cur % 10));
            carry = cur / 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    friend big_integer operator*(int multiplier, const big_integer &a)
    {
        return a * multiplier;
    }

    friend std::ostream &operator<<(std::ostream &os, const big_integer &a)
    {
        return os << a.m_digits;
    }

private:
    std::string m_digits;
};

int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");

    auto result = number1 + number2;
    std::cout << result << '\n'; // 193099

    auto multiplied = number1 * 3;
    std::cout << multiplied << '\n'; // 343725

    return 0;
}