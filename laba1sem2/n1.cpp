#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <utility>

class String {
private:
    char* data_;
    std::size_t size_;

public:
    String() : data_(new char[1]), size_(0) {
        data_[0] = '\0';
    }

    String(const char* str) {
        if (str == nullptr) {
            size_ = 0;
            data_ = new char[1];
            data_[0] = '\0';
            return;
        }

        std::size_t len = 0;
        while (str[len] != '\0') {
            ++len;
        }

        size_ = len;
        data_ = new char[size_ + 1];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = str[i];
        }
        data_[size_] = '\0';
    }

    String(const String& other) : data_(new char[other.size_ + 1]), size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        data_[size_] = '\0';
    }

    String(String&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = new char[1];
        other.data_[0] = '\0';
        other.size_ = 0;
    }

    ~String() {
        delete[] data_;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            char* new_data = new char[other.size_ + 1];
            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
            new_data[other.size_] = '\0';

            delete[] data_;
            data_ = new_data;
            size_ = other.size_;
        }
        return *this;
    }

    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data_;

            data_ = other.data_;
            size_ = other.size_;

            other.data_ = new char[1];
            other.data_[0] = '\0';
            other.size_ = 0;
        }
        return *this;
    }

    std::size_t Size() const {
        return size_;
    }

    const char* CStr() const {
        return data_;
    }

    void PushBack(char ch) {
        char* new_data = new char[size_ + 2];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        new_data[size_] = ch;
        new_data[size_ + 1] = '\0';

        delete[] data_;
        data_ = new_data;
        ++size_;
    }

    void Clear() {
        delete[] data_;
        data_ = new char[1];
        data_[0] = '\0';
        size_ = 0;
    }

    char& operator[](std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const char& operator[](std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    bool operator==(const String& other) const {
        if (size_ != other.size_) {
            return false;
        }

        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data_;
        return os;
    }
};

int main() {
    std::cout << "Конструктор по умолчанию \n";
    String s1;
    std::cout << "s1 = \"" << s1 << "\", size = " << s1.Size() << "\n\n";

    std::cout << "Конструктор из const char* \n";
    String s2("Hello");
    std::cout << "s2 = \"" << s2 << "\", size = " << s2.Size() << "\n\n";

    std::cout << "Конструктор копирования \n";
    String s3(s2);
    std::cout << "s3 = \"" << s3 << "\", size = " << s3.Size() << "\n\n";

    std::cout << "Конструктор перемещения \n";
    String s4(std::move(s2));
    std::cout << "s4 = \"" << s4 << "\", size = " << s4.Size() << "\n";
    std::cout << "s2 после move = \"" << s2 << "\", size = " << s2.Size() << "\n\n";

    std::cout << " PushBack \n";
    s4.PushBack('!');
    std::cout << "s4 = \"" << s4 << "\", size = " << s4.Size() << "\n\n";

    std::cout << "operator[] \n";
    s4[0] = 'h';
    std::cout << "s4 после изменения = \"" << s4 << "\"\n\n";

    std::cout << "Копирующее присваивание \n";
    s1 = s4;
    std::cout << "s1 = \"" << s1 << "\", size = " << s1.Size() << "\n\n";

    std::cout << "Перемещающее присваивание \n";
    String s5("World");
    std::cout << "s5 до move = \"" << s5 << "\"\n";
    s5 = std::move(s4);
    std::cout << "s5 после move = \"" << s5 << "\", size = " << s5.Size() << "\n";
    std::cout << "s4 после move = \"" << s4 << "\", size = " << s4.Size() << "\n\n";

    std::cout << " Сравнение \n";
    String s6("hello!");
    std::cout << "s5 = \"" << s5 << "\"\n";
    std::cout << "s6 = \"" << s6 << "\"\n";
    std::cout << "s5 == s6 -> " << (s5 == s6 ? "true" : "false") << "\n";
    std::cout << "s5 != s6 -> " << (s5 != s6 ? "true" : "false") << "\n\n";

    std::cout << "CStr\n";
    std::cout << "s5.CStr() = " << s5.CStr() << "\n\n";

    std::cout << "Clear\n";
    s6.Clear();
    std::cout << "s6 = \"" << s6 << "\", size = " << s6.Size() << "\n\n";

    std::cout << "Проверка выхода за границы \n";
    try {
        std::cout << s5[100] << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}
