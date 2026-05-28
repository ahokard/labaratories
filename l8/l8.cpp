#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <fstream>
#include <functional>

using namespace std;

// Класс "Автомобиль"
class Car
{
private:
    string model;        // Модель автомобиля
    double maxSpeed;     // Максимальная скорость

public:
    // Конструктор
    Car(string m = "Неизвестно", double s = 0)
    {
        model = m;
        maxSpeed = s;
    }

    // Получение модели
    string getModel() const
    {
        return model;
    }

    // Получение максимальной скорости
    double getMaxSpeed() const
    {
        return maxSpeed;
    }

    // Вывод объекта
    void print() const
    {
        cout << "Модель: " << model << endl;
        cout << "Максимальная скорость: " << maxSpeed << " км/ч" << endl;
    }

    // Перегрузка оператора < для работы с set
    bool operator<(const Car& other) const
    {
        if (model != other.model)
            return model < other.model;

        return maxSpeed < other.maxSpeed;
    }

    // Перегрузка оператора == для работы с unordered_set
    bool operator==(const Car& other) const
    {
        return model == other.model &&
               maxSpeed == other.maxSpeed;
    }
};

// Хешер для класса Car
class CarHasher
{
public:
    size_t operator()(const Car& car) const
    {
        const size_t coef = 2946901;

        hash<string> stringHash;
        hash<double> doubleHash;

        return coef * stringHash(car.getModel()) +
               doubleHash(car.getMaxSpeed());
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    set<Car> carSet;
    unordered_set<Car, CarHasher> carUnorderedSet;

    ifstream fin("input.txt");

    if (!fin)
    {
        cout << "Ошибка открытия файла input.txt" << endl;
        return 1;
    }

    string model;
    double maxSpeed;

    while (fin >> model >> maxSpeed)
    {
        Car car(model, maxSpeed);

        carSet.insert(car);
        carUnorderedSet.insert(car);
    }

    fin.close();

    cout << "=== Контейнер set ===" << endl;
    for (const Car& car : carSet)
    {
        car.print();
        cout << endl;
    }

    cout << "=== Контейнер unordered_set ===" << endl;
    for (const Car& car : carUnorderedSet)
    {
        car.print();
        cout << endl;
    }

    return 0;
}