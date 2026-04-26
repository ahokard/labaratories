#include <iostream>
#include <stdexcept>

using namespace std;


class ProgressionException : public invalid_argument {
private:
    int* arr;
    int size;

public:
    ProgressionException(const string& msg, int* a, int n)
        : invalid_argument(msg), size(n) {
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = a[i];
        }
    }

    void printData() {
        cout << "Неверный массив: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~ProgressionException() {
        delete[] arr;
    }
};


class ArithmeticProgression {
private:
    int a1;
    int d;
    int* arr;
    int size;

public:
    ArithmeticProgression(int* a, int n) {
        size = n;
        arr = new int[size];

        for (int i = 0; i < size; i++) {
            arr[i] = a[i];
        }

        a1 = arr[0];
        d = arr[1] - arr[0];

        for (int i = 1; i < size; i++) {
            if (arr[i] != arr[i - 1] + d) {
                throw ProgressionException("Это не арифметическая прогрессия!", arr, size);
            }
        }
    }

    void print() {
        cout << "Арифметическая прогрессия: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~ArithmeticProgression() {
        delete[] arr;
    }
};

int main() {
    try {
        int good[] = {2, 4, 6, 8, 10};
        ArithmeticProgression p1(good, 5);
        p1.print();
    }
    catch (ProgressionException& e) {
        cout << e.what() << endl;
        e.printData();
    }

    cout << endl;

    try {
        int bad[] = {1, 2, 4, 8};
        ArithmeticProgression p2(bad, 4);
        p2.print();
    }
    catch (ProgressionException& e) {
        cout << e.what() << endl;
        e.printData();
    }

    return 0;
}