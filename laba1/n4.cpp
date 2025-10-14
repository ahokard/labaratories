 #include <iostream>
using namespace std;
int main() {
    for (int i = 8; i <16; 0) {
        cout << i * (i+1)* (i+2)* (i+3)* (i+4)* (i+5)* (i+6)* (i+7)<< endl;
        break;
    }

    int a;
    cin >> a;
    if (a > 1 && a < 20) {
        long long prod = 1;
        for (int i = a; i <= 20; ++i) {
            prod *= i;
        }
        cout << prod << endl;
    } else {
        cout << "Ошибка" << endl;
    }

    int b;
    cin >> b;
    if (b > 1 && b < 20) {
        long long prod = 1;
        for (int i =1; i <= b; ++i) {
            prod *= i;
        }
        cout << prod << endl;
    } else {
        cout << "Ошибка" << endl;
    }

    int a2,b2;
    cin >> a2 >>b2;
    if (b2 >=a2) {
        long long prod = 1;
        for (int i =a2; i <= b2; ++i) {
            prod *= i;
        }
        cout << prod << endl;
    } else {
        cout << "Ошибка" << endl;
    }


    return 0;
}
