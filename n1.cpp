#include <iostream>
#include <algorithm>
#include <stdexcept>

template <class T>
class vector {
private:
    T* data;
    size_t size;
    size_t capacity;
public:
    vector() {
        size = 0;
        capacity = 0;
        data = nullptr;
    }

    vector(const vector& other) {
        if (other.data == nullptr) {
            data = nullptr;
            size = 0;
            capacity = 0;
            return;
        }
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        std::copy(other.data, other.data + size, data);
    }

    vector(const size_t size, const T& obj) {
        this->size = size;
        capacity = size;
        data = new T[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = obj;
        }
    }

    vector(size_t size, T* arr) {
        this->size = size;
        capacity = size;
        data = new T[size];
        std::copy(arr, arr + size, data);
    }

    ~vector() {
        delete[] data;
    }

    vector& operator=(const vector& other) {
        if (this == &other) {
            return *this;
        }

        if (capacity >= other.size) {
            size = other.size;
            std::copy(other.data, other.data + other.size, data);
        }
        else {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            std::copy(other.data, other.data + other.size, data);
        }
        return *this;
    }

    T& operator[](size_t ind) {
        return data[ind];
    }

    T& at(size_t ind) {
        if (ind < size) {
            return data[ind];
        }
        else {
            throw std::out_of_range("Index is out of range\n");
        }
    }

    T& front() {
        if (size == 0) {
            throw std::out_of_range("Vector is empty\n");
        }
        return data[0];
    }

    T& back() {
        if (size == 0) {
            throw std::out_of_range("Vector is empty\n");
        }
        return data[size - 1];
    }

    T* Data() const {
        return data;
    }

    bool empty() const {
        if (size == 0) {
            return true;
        }
        return false;
    }

    size_t Size() const {
        return size;
    }

    void reserve(size_t new_cp) {
        if (new_cp > capacity) {
            T* arr = new T[new_cp];
            std::copy(data, data + size, arr);
            delete[] data;
            data = arr;
            capacity = new_cp;
        }
    }

    void clear() {
        size = 0;
    }

    void push_back(T value) {
        if (size < capacity) {
            data[size] = value;
            size++;
        }
        else if (size == capacity) {
            if (size == 0) {
                size = 1;
                capacity = 1;
                data = new T[capacity];
                data[0] = value;
            }
            else {
                capacity = 2 * size;
                T* arr = new T[capacity];
                std::copy(data, data + size, arr);
                delete[] data;
                data = arr;
                data[size] = value;
                size++;
            }
        }
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("Vector is empty\n");
        }
        size--;
    }

    size_t Capacity() const {
        return capacity;
    }

    void swap(vector& other) {
        std::swap(this->data, other.data);
        std::swap(this->size, other.size);
        std::swap(this->capacity, other.capacity);
    }
};

int main() {
}