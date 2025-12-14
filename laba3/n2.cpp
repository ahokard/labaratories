//
// Created by Антон Деев
//
#include <iostream>
using namespace std;
#include <cmath>
int main() {
    int mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double sum1=0, size, sum2=0, sum3=0, k1, k2, sum4=0,s1, s2, sum=0, count=0;
    double sred5, sred6;
    cout << "Enter k1 and k2:" << endl;
    cin >> k1 >> k2;
    cout << "Enter s1 and s2:" << endl;
    cin >> s1 >> s2;
    size = sizeof(mass) / sizeof(mass[0]);
    for (int i = 0; i < size; ++i) {
        sum1 += mass[i];
        sum2 += pow(mass[i], 2);
    }
    for (int i = 0; i < 6; ++i) {
        sum3+= mass[i];
    }
    for (int i=k1-1; i <= k2-1; ++i) {
        sum4+= mass[i];
    }
    sred5= sum1/ size;
    for (int i=s1-1; i <= s2-1; ++i) {
        sum += mass[i];
        ++count;
    }
    sred6= sum / count;
    cout << "i. " << sum1 << endl;
    cout << "ii. " << sum2 << endl;
    cout << "iii. " << sum3 << endl;
    cout << "iv. " << sum4<< endl;
    cout << "v. " << sred5<< endl;
    cout << "vi. " << sred6 << endl;
}