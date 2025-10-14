#include <iostream>
using namespace std;
int main() {
    int x,y,z;
    std::cin>>x>>y>>z;
    if (x%2 != 0 && y%2 != 0) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    if ((x<20 && y>=20) || (x>=20 && y<20)) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    if (x==0 || y==0) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    if (x==0 || y==0) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    if (x<0 && y<0 && z<0) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    if ((x%5==0 && y%5!=0 && z%5!=0) || (x%5!=0 && y%5==0 && z%5!=0) || (x%5!=0 && y%5!=0 && z%5==0)) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    if (x>100 || y>100 || z>100) {
        cout<<"condition is true"<<endl;
    } else {
        cout<<"condition is false"<<endl;
    }

    return 0;
}