#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

using namespace std;

mutex printMutex;
mutex finishMutex;
condition_variable cv;

int finishedCount = 0;

void safePrint(string name, int value) {
    lock_guard<mutex> lock(printMutex);
    cout << name << ": " << value << endl;
}


void notifyFinished(string name) {
    {
        lock_guard<mutex> lock(finishMutex);
        finishedCount++;
        cout << name << " завершил работу" << endl;
    }

    cv.notify_one();
}

// Поток 1: числа Фибоначчи
void fibonacciTask(string name, int n) {
    int a = 0;
    int b = 1;

    for (int i = 0; i < n; i++) {
        this_thread::sleep_for(chrono::milliseconds(10));

        safePrint(name, a);

        int next = a + b;
        a = b;
        b = next;
    }

    notifyFinished(name);
}

// Поток 2: натуральные числа
void naturalTask(string name, int n) {
    for (int i = 1; i <= n; i++) {
        this_thread::sleep_for(chrono::milliseconds(10));

        safePrint(name, i);
    }

    notifyFinished(name);
}

// Поток 3: случайные числа
void randomTask(string name, int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < n; i++) {
        this_thread::sleep_for(chrono::milliseconds(10));

        safePrint(name, dist(gen));
    }

    notifyFinished(name);
}

void runWithThread() {
    cout << endl;
    cout << "Вариант через thread " << endl;

    finishedCount = 0;

    int n1 = 20;
    int n2 = 20;
    int n3 = 20;

    thread t1(fibonacciTask, "thread1", n1);
    thread t2(naturalTask, "thread2", n2);
    thread t3(randomTask, "thread3", n3);

    while (finishedCount < 3) {
        unique_lock<mutex> lock(finishMutex);

        cv.wait(lock, []() {
            return finishedCount > 0;
        });

        cout << "Главный поток получил уведомление. Завершено потоков: "
             << finishedCount << endl;

        if (finishedCount == 3) {
            break;
        }
    }

    t1.join();
    t2.join();
    t3.join();

    cout << "Главный поток завершил работу thread-версии" << endl;
}


void runWithAsync() {
    cout << endl;
    cout << "Вариант через async и future " << endl;

    finishedCount = 0;

    int n1 = 20;
    int n2 = 20;
    int n3 = 20;

    future<void> f1 = async(launch::async, fibonacciTask, "async1", n1);
    future<void> f2 = async(launch::async, naturalTask, "async2", n2);
    future<void> f3 = async(launch::async, randomTask, "async3", n3);

    while (finishedCount < 3) {
        unique_lock<mutex> lock(finishMutex);

        cv.wait(lock, []() {
            return finishedCount > 0;
        });

        cout << "Главный поток получил уведомление. Завершено потоков: "
             << finishedCount << endl;

        if (finishedCount == 3) {
            break;
        }
    }

    f1.get();
    f2.get();
    f3.get();

    cout << "Главный поток завершил работу async-версии" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    runWithThread();
    runWithAsync();

    cout << endl;
    cout << "Программа полностью завершена" << endl;

    return 0;
}