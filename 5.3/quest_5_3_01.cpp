#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <stdexcept>
#include <clocale>

struct ListNode
{
public:
    ListNode(int value, ListNode *prev = nullptr, ListNode *next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr)
            prev->next = this;
        if (next != nullptr)
            next->prev = this;
    }

public:
    int value;
    ListNode *prev;
    ListNode *next;
};

class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
          m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty())
            throw std::runtime_error("список пуст");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty())
            throw std::runtime_error("список пуст");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode *extractPrev(ListNode *node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode *m_head;
    ListNode *m_tail;
    unsigned long m_size;
};

TEST_CASE("Empty на свежесозданном списке", "[Empty]")
{
    List list;
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Empty после добавления элементов", "[Empty]")
{
    List list;
    list.PushBack(10);
    REQUIRE(list.Empty() == false);

    list.PushFront(20);
    REQUIRE(list.Empty() == false);
}

TEST_CASE("Empty после очистки", "[Empty]")
{
    List list;
    list.PushBack(1);
    list.PushBack(2);
    list.Clear();
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Size свежего списка равен нулю", "[Size]")
{
    List list;
    REQUIRE(list.Size() == 0);
}

TEST_CASE("Size корректно считает элементы", "[Size]")
{
    List list;

    list.PushBack(1);
    REQUIRE(list.Size() == 1);

    list.PushBack(2);
    list.PushFront(3);
    REQUIRE(list.Size() == 3);

    list.PushFront(4);
    list.PushBack(5);
    REQUIRE(list.Size() == 5);

    list.PopFront();
    REQUIRE(list.Size() == 4);

    list.PopBack();
    REQUIRE(list.Size() == 3);
}

TEST_CASE("Size совпадает с реальным числом элементов", "[Size]")
{
    List list;
    list.PushBack(100);
    list.PushBack(200);
    list.PushBack(300);

    REQUIRE(list.Size() == 3);
    REQUIRE(list.PopFront() == 100);
    REQUIRE(list.PopBack() == 300);
    REQUIRE(list.PopFront() == 200);
    REQUIRE(list.Size() == 0);
}

TEST_CASE("Clear обнуляет размер", "[Clear]")
{
    List list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    REQUIRE(list.Size() == 3);

    list.Clear();

    REQUIRE(list.Size() == 0);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Clear на пустом списке безопасен", "[Clear]")
{
    List list;
    REQUIRE_NOTHROW(list.Clear());
    REQUIRE(list.Size() == 0);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Повторный вызов Clear", "[Clear]")
{
    List list;
    list.PushBack(1);
    list.Clear();
    list.Clear();
    REQUIRE(list.Size() == 0);
}

TEST_CASE("Список используется после Clear", "[Clear]")
{
    List list;
    list.PushBack(5);
    list.PushBack(6);
    list.Clear();

    list.PushBack(7);
    list.PushFront(8);

    REQUIRE(list.Size() == 2);
    REQUIRE(list.PopFront() == 8);
    REQUIRE(list.PopBack() == 7);
    REQUIRE(list.Size() == 0);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    return Catch::Session().run(argc, argv);
}