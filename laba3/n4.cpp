//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> v;
    int s[] = {1,2,-3,4,-5,6,7,8,9,10,11};
    int size;
    int range2;
    int range1;
    size = sizeof(s)/sizeof(s[0]);
    for(int i=0; i < size;i++){
        if(s[i]<0){
            range1 = i;
            break;
        }
    }
    for(int i=0; i < size;i++){
        if (i != range1){
            v.push_back(s[i]);
        }
    }
    cout << "1. ";
    for(int i = 0;i < (size-1); i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    for(int i = (size-2); i >= 0;i--){
        if(v[i]%2 == 0){
            v.erase(v.begin()+i);
            break;
        }
    }
    cout << "2. ";
    for(int i = 0;i < (size-2); i++) {
        cout << v[i] << " ";
    }
}