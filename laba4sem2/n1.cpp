#include <iostream>
#include <utility>

class Test
{
public:
    int value;
    Test(int v) : value(v)
    {
        std::cout << "Конструктор Test: value = " << value << std::endl;
    }

    ~Test()
    {
        std::cout << "Деструктор Test: value = " << value << std::endl;
    }

    void show() const
    {
        std::cout << "Значение value = " << value << std::endl;
    }
};

// ЧАСТЬ 1
template<class T>
class MyUnique
{
private:
    T* p;

public:
    MyUnique() : p(nullptr) {}

    MyUnique(T* ptr) : p(ptr) {}

    ~MyUnique()
    {
        delete p;
    }


    MyUnique(const MyUnique&) = delete;

    MyUnique& operator=(const MyUnique&) = delete;

    // Новый объект забирает указатель у другого объекта
    MyUnique(MyUnique&& other) noexcept : p(other.p)
    {
        other.p = nullptr; // старый объект больше не владеет памятью
    }

    MyUnique& operator=(MyUnique&& other) noexcept
    {
        if (this != &other)
        {
            delete p;       // освобождаем старую память
            p = other.p;    // забираем указатель
            other.p = nullptr;
        }
        return *this;
    }

    T* get() const
    {
        return p;
    }


    T& operator*()
    {
        return *p;
    }

    T* operator->()
    {
        return p;
    }
};

// ЧАСТЬ 2
template<class T>
class MyShared
{
private:
    T* p;        // указатель на объект
    int* count;  // счетчик владельцев

    // Вспомогательный метод уменьшения счетчика
    void release()
    {
        if (count != nullptr)
        {
            (*count)--;   // уменьшаем число владельцев

            std::cout << "Уменьшение счетчика, count = " << *count << std::endl;

            if (*count == 0)
            {
                delete p;      // удаляем сам объект
                delete count;  // удаляем счетчик
                std::cout << "Память освобождена" << std::endl;
            }
        }

        p = nullptr;
        count = nullptr;
    }

public:
    MyShared() : p(nullptr), count(nullptr) {}


    MyShared(T* ptr) : p(ptr)
    {
        if (ptr != nullptr)
            count = new int(1);
        else
            count = nullptr;
    }

    ~MyShared()
    {
        release();
    }

    MyShared(const MyShared& other) : p(other.p), count(other.count)
    {
        if (count != nullptr)
        {
            (*count)++;
        }
    }

    MyShared& operator=(const MyShared& other)
    {
        if (this != &other)
        {
            release();

            p = other.p;
            count = other.count;

            if (count != nullptr)
            {
                (*count)++;
            }
        }
        return *this;
    }

    MyShared(MyShared&& other) noexcept : p(other.p), count(other.count)
    {
        other.p = nullptr;
        other.count = nullptr;
    }

    MyShared& operator=(MyShared&& other) noexcept
    {
        if (this != &other)
        {
            release();

            p = other.p;
            count = other.count;

            other.p = nullptr;
            other.count = nullptr;
        }
        return *this;
    }

    T* get() const
    {
        return p;
    }

    T& operator*()
    {
        return *p;
    }

    T* operator->()
    {
        return p;
    }

    int use_count() const
    {
        if (count != nullptr)
            return *count;
        return 0;
    }
};


int main()
{
    std::cout << "ЧАСТЬ 1. Проверка MyUnique" << std::endl;

    MyUnique<Test> u1(new Test(10));

    std::cout << "u1.get() = " << u1.get() << std::endl;

    u1->show();

    std::cout << "(*u1).value = " << (*u1).value << std::endl;

    std::cout << "\nПеремещение u1 в u2" << std::endl;
    MyUnique<Test> u2(std::move(u1));

    std::cout << "После перемещения:" << std::endl;
    std::cout << "u1.get() = " << u1.get() << std::endl;
    std::cout << "u2.get() = " << u2.get() << std::endl;
    u2->show();

    std::cout << "\nПеремещающее присваивание u2 в u3" << std::endl;
    MyUnique<Test> u3;
    u3 = std::move(u2);

    std::cout << "После присваивания:" << std::endl;
    std::cout << "u2.get() = " << u2.get() << std::endl;
    std::cout << "u3.get() = " << u3.get() << std::endl;
    u3->show();


    std::cout << "ЧАСТЬ 2. Проверка MyShared" << std::endl;

    MyShared<Test> s1(new Test(20));

    std::cout << "s1.get() = " << s1.get() << std::endl;
    std::cout << "s1.use_count() = " << s1.use_count() << std::endl;

    s1->show();


    std::cout << "(*s1).value = " << (*s1).value << std::endl;

    std::cout << "\nКопирование s1 в s2" << std::endl;
    MyShared<Test> s2 = s1;

    std::cout << "После копирования:" << std::endl;
    std::cout << "s1.use_count() = " << s1.use_count() << std::endl;
    std::cout << "s2.use_count() = " << s2.use_count() << std::endl;

    std::cout << "\nКопирующее присваивание s2 в s3" << std::endl;
    MyShared<Test> s3;
    s3 = s2;

    std::cout << "После копирующего присваивания:" << std::endl;
    std::cout << "s1.use_count() = " << s1.use_count() << std::endl;
    std::cout << "s2.use_count() = " << s2.use_count() << std::endl;
    std::cout << "s3.use_count() = " << s3.use_count() << std::endl;

    std::cout << "\nПеремещение s3 в s4" << std::endl;
    MyShared<Test> s4(std::move(s3));

    std::cout << "После перемещения:" << std::endl;
    std::cout << "s3.use_count() = " << s3.use_count() << std::endl;
    std::cout << "s4.use_count() = " << s4.use_count() << std::endl;

    s4->show();


    return 0;
}