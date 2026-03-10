#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <cstddef>

template <class T>
class vector {
private:
    T* arr;
    size_t sz;
    size_t cap;

public:
    using value_type = T;

    class iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(T* p = nullptr) : ptr(p) {}

        reference operator*() const {
            return *ptr;
        }

        pointer operator->() const {
            return ptr;
        }

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp(*this);
            ++ptr;
            return temp;
        }

        iterator& operator--() {
            --ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator temp(*this);
            --ptr;
            return temp;
        }

        iterator operator+(difference_type n) const {
            return iterator(ptr + n);
        }

        iterator operator-(difference_type n) const {
            return iterator(ptr - n);
        }

        difference_type operator-(const iterator& other) const {
            return ptr - other.ptr;
        }

        iterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }

        iterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }

        reference operator[](difference_type n) const {
            return *(ptr + n);
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        bool operator<(const iterator& other) const {
            return ptr < other.ptr;
        }

        bool operator>(const iterator& other) const {
            return ptr > other.ptr;
        }

        bool operator<=(const iterator& other) const {
            return ptr <= other.ptr;
        }

        bool operator>=(const iterator& other) const {
            return ptr >= other.ptr;
        }
    };

    vector() : arr(nullptr), sz(0), cap(0) {}

    vector(size_t n, const T& value) {
        sz = n;
        cap = n;
        arr = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            arr[i] = value;
        }
    }

    vector(const vector& other) {
        sz = other.sz;
        cap = other.cap;
        arr = new T[cap];
        for (size_t i = 0; i < sz; ++i) {
            arr[i] = other.arr[i];
        }
    }

    ~vector() {
        delete[] arr;
    }

    vector& operator=(const vector& other) {
        if (this != &other) {
            delete[] arr;
            sz = other.sz;
            cap = other.cap;
            arr = new T[cap];
            for (size_t i = 0; i < sz; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    T& operator[](size_t index) {
        return arr[index];
    }

    const T& operator[](size_t index) const {
        return arr[index];
    }

    T& at(size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& at(size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return arr[0];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return arr[sz - 1];
    }

    T* data() {
        return arr;
    }

    iterator begin() {
        return iterator(arr);
    }

    iterator end() {
        return iterator(arr + sz);
    }

    bool empty() const {
        return sz == 0;
    }

    size_t size() const {
        return sz;
    }

    size_t capacity() const {
        return cap;
    }

    void reserve(size_t new_cap) {
        if (new_cap <= cap) {
            return;
        }

        T* new_arr = new T[new_cap];
        for (size_t i = 0; i < sz; ++i) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        cap = new_cap;
    }

    void clear() {
        sz = 0;
    }

    void push_back(const T& value) {
        if (sz == cap) {
            if (cap == 0) {
                reserve(1);
            } else {
                reserve(cap * 2);
            }
        }
        arr[sz] = value;
        ++sz;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        --sz;
    }

    iterator insert(iterator pos, const T& value) {
        size_t index = pos - begin();

        if (index > sz) {
            throw std::out_of_range("Invalid position");
        }

        if (sz == cap) {
            if (cap == 0) {
                reserve(1);
            } else {
                reserve(cap * 2);
            }
        }

        for (size_t i = sz; i > index; --i) {
            arr[i] = arr[i - 1];
        }

        arr[index] = value;
        ++sz;

        return iterator(arr + index);
    }

    void swap(vector& other) {
        std::swap(arr, other.arr);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
    }
};

int main() {
    return 0;
}
