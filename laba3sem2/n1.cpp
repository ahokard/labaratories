#include <iostream>
#include <string>

using namespace std;

// Базовый класс "Автомобиль"
class Car
{
protected:
    string model;      // Модель автомобиля
    double maxSpeed;   // Максимальная скорость

public:
    // Конструктор
    Car(string m = "Неизвестно", double s = 0)
    {
        model = m;
        maxSpeed = s;
        cout << "Создан объект класса Car" << endl;
    }

    // Деструктор
    virtual ~Car()
    {
        cout << "Удален объект класса Car" << endl;
    }

    // Функция для получения модели
    string getModel()
    {
        return model;
    }

    // Функция для получения максимальной скорости
    double getMaxSpeed()
    {
        return maxSpeed;
    }

    // Виртуальная функция печати
    virtual void print()
    {
        cout << "Автомобиль:" << endl;
        cout << "Модель: " << model << endl;
        cout << "Максимальная скорость: " << maxSpeed << " км/ч" << endl;
    }
};

// Производный класс "Грузовой автомобиль"
class Truck : public Car
{
private:
    double loadCapacity;   // Грузоподъемность

public:
    // Конструктор
    Truck(string m = "Неизвестно", double s = 0, double l = 0) : Car(m, s)
    {
        loadCapacity = l;
        cout << "Создан объект класса Truck" << endl;
    }

    // Деструктор
    ~Truck()
    {
        cout << "Удален объект класса Truck" << endl;
    }

    // Функция для получения грузоподъемности
    double getLoadCapacity()
    {
        return loadCapacity;
    }

    void print() override
    {
        Car::print();
        cout << "Грузоподъемность: " << loadCapacity << " т" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "=== Создание объектов ===" << endl;
    Car car("Toyota Camry", 210);
    cout << endl;

    Truck truck("Volvo FH16", 180, 25);
    cout << endl;

    cout << "=== Прямой вызов функций ===" << endl;
    car.print();
    cout << endl;
    truck.print();
    cout << endl;

    cout << "=== Использование get-функций ===" << endl;
    cout << "Модель легкового автомобиля: " << car.getModel() << endl;
    cout << "Скорость легкового автомобиля: " << car.getMaxSpeed() << " км/ч" << endl;
    cout << endl;

    cout << "Модель грузового автомобиля: " << truck.getModel() << endl;
    cout << "Скорость грузового автомобиля: " << truck.getMaxSpeed() << " км/ч" << endl;
    cout << "Грузоподъемность грузового автомобиля: " << truck.getLoadCapacity() << " т" << endl;
    cout << endl;

    cout << "=== Статический полиморфизм ===" << endl;
    car.print();
    cout << endl;
    truck.print();
    cout << endl;

    cout << "Динамический полиморфизм" << endl;
    Car* p;

    p = &car;
    cout << "Указатель p указывает на объект класса Car:" << endl;
    p->print();
    cout << endl;

    p = &truck;
    cout << "Указатель p указывает на объект класса Truck:" << endl;
    p->print();
    cout << endl;

    cout << "Работа через ссылку базового класса " << endl;
    Car& ref = truck;
    ref.print();
    cout << endl;

    return 0;
}