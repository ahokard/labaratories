#include <iostream>


using namespace std;

int main() {
    pair<unsigned char, unsigned char> positionA, positionB;

    cout << "координаты первой фигуры (a b): ";
    cin >> positionA.first >> positionA.second;

    cout << "координаты второй клетки (c d): ";
    cin >> positionB.first >> positionB.second;

    unsigned char a = positionA.first;
    unsigned char b = positionA.second;
    unsigned char c = positionB.first;
    unsigned char d = positionB.second;

    if (a == c || b == d)
        cout << "Ладья угрожает полю (" << c << ", " << d << ")"<<endl;
    else
        cout << "Ладья не угрожает полю"<<endl;


    if (abs(a - c) == abs(b - d))
        cout << "Слон угрожает полю"<<endl;
    else
        cout << "Слон не угрожает полю"<<endl;

    if (abs(a - c) <= 1 && abs(b - d) <= 1)
        cout << "Король может попасть на поле"<<endl;
    else
        cout << "Король не может попасть на поле"<<endl;


    if (a == c || b == d || abs(a - c) == abs(b - d))
        cout << "Ферзь угрожает полю"<<endl;
    else
        cout << "Ферзь не угрожает полю"<<endl;


    if (c == a && d == b + 1)
        cout << "Пешка может сделать обычный ход"<<endl;
    else
        cout << "Пешка не может сделать обычный ход"<<endl;


    if ((c == a + 1 || c == a - 1) && d == b + 1)
        cout << "Пешка может атаковать"<<endl;
    else
        cout << "Пешка не может атаковать"<<endl;

    return 0;
}
