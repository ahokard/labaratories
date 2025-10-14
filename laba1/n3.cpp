#include <iostream>
using namespace std;
int main() {
    for (int i = 1; i < 10; ++i) {
        cout << i << "*" << 7 << "=" << i*7 << endl;
    }

    int n;
    cin >> n;
    for (int i = 1; i < 10; ++i) {
        cout << i << "*" << n << "=" << i*n << endl;
    }

    return 0;
}