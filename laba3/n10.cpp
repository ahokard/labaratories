//
// Created by Антон Деев
//
#include <iostream>
#include <string>
using namespace std;

int main ()
{
    string s;
    cout << "Напишите предложение: ";
    getline (cin,s);
    string a="aA";
    string pr = " ";
    long long procent;
    int x=0;
    int lenn = 0;
    for (int i=0; i<s.length(); i++){
        if ((s[i]==a[0]) or (s[i] == a[1])) {
            x++;
        }
        if (s[i] != pr[0]){
            lenn++;
        }
    }
    procent = (x*100)/lenn;
    cout << procent<<"%";
}