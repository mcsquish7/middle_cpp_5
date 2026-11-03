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
            throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty())
            throw std::runtime_error("list is empty");
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

TEST_CASE("PushBack добавляет элемент в конец", "[PushBack]")
{
    List list;

    list.PushBack(10);
    REQUIRE(list.Size() == 1);
    REQUIRE(list.PopBack() == 10);

    list.PushBack(20);
    list.PushBack(30);
    REQUIRE(list.Size() == 2);
    REQUIRE(list.PopBack() == 30);
    REQUIRE(list.PopBack() == 20);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("PushFront добавляет элемент в начало", "[PushFront]")
{
    List list;

    list.PushFront(10);
    REQUIRE(list.Size() == 1);
    REQUIRE(list.PopFront() == 10);

    list.PushFront(20);
    list.PushFront(30);
    REQUIRE(list.Size() == 2);
    REQUIRE(list.PopFront() == 30);
    REQUIRE(list.PopFront() == 20);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("PopBack на пустом списке бросает исключение", "[PopBack]")
{
    List list;
    REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
    REQUIRE(list.Size() == 0);
}

TEST_CASE("PopFront на пустом списке бросает исключение", "[PopFront]")
{
    List list;
    REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    REQUIRE(list.Size() == 0);
}

TEST_CASE("PopFront и PopBack возвращают значения в правильном порядке", "[Сценарий]")
{
    List list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushFront(0);

    REQUIRE(list.Size() == 4);
    REQUIRE(list.PopFront() == 0);
    REQUIRE(list.PopBack() == 3);
    REQUIRE(list.PopFront() == 1);
    REQUIRE(list.PopBack() == 2);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Смешанные операции добавления и извлечения", "[Сценарий]")
{
    List list;

    list.PushBack(10);
    list.PushFront(5);
    list.PushBack(20);
    REQUIRE(list.Size() == 3);

    REQUIRE(list.PopFront() == 5);
    list.PushFront(1);
    list.PushBack(30);
    REQUIRE(list.Size() == 4);

    REQUIRE(list.PopBack() == 30);
    REQUIRE(list.PopFront() == 1);
    REQUIRE(list.PopBack() == 20);
    REQUIRE(list.PopFront() == 10);
    REQUIRE(list.Empty() == true);
}

TEST_CASE("Список можно переиспользовать после полного опустошения", "[Сценарий]")
{
    List list;

    list.PushBack(1);
    list.PushBack(2);
    REQUIRE(list.PopFront() == 1);
    REQUIRE(list.PopBack() == 2);
    REQUIRE(list.Empty() == true);

    list.PushFront(100);
    list.PushBack(200);
    REQUIRE(list.Size() == 2);
    REQUIRE(list.PopFront() == 100);
    REQUIRE(list.PopBack() == 200);
    REQUIRE(list.Empty() == true);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    return Catch::Session().run(argc, argv);
}