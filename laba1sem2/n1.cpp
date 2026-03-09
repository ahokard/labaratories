#include <iostream>
#include <algorithm>


class String {
private:
    char* data;

    size_t len(const char* str) const {
        size_t len = 0;
        while (str[len]!='\0') {
            len++;
        }
        return len;
    }

    void copy(char* dest, const char* from) {
        for (int i = 0; i < len(from); i++) {
            dest[i] = from[i];
        }
        dest[len(from)] = '\0';
    }
public:
    String() {
        data = new char[1];
        data[0] = '\0';
    }
    String(const String& other) {
        data = new char[len(other.data)+1];
        copy(data,other.data);
    }
    String(const char* data) {
        if (data==nullptr) {
            std::cerr << "Error-строка не может быть nullptr" << '\n';
            std::exit(-1);
        }
        this->data = new char[len(data)+1];
        copy(this->data, data);
    }
    ~String() {
        delete[] data;
    }
    String& operator=(const String& other) {
        data = new char[len(other.data)+1];
        copy(data,other.data);
        return *this;
    }
    String& operator+=(const String& other) {
        char* temp = new char[len(data)+1];
        copy(temp,data);
        delete [] data;
        data = new char[len(temp)+len(other.data)+1];
        for (int i = 0, j = 0; i<len(temp)+len(other.data); i++) {
            if (i<len(temp)) {
                data[i] = temp[i];
            }
            else {
                data[i] = other.data[j];
                j++;
            }
        }
        this->data[len(temp)+len(other.data)]='\0';
        delete [] temp;
        return *this;
    }
    String& operator*=(unsigned int m) {
        char* temp = new char[len(data)+1];
        copy(temp,data);
        delete [] data;
        data = new char[len(temp)*m+1];
        for (int i = 0, j = 0; i < len(temp)*m; i++) {
            if ((i+1)%len(temp)!=0) {
                data[i]=temp[j];
                j++;
            }
            else {
                data[i]=temp[j];
                j=0;
            }
        }
        data[len(temp)*m] = '\0';
        delete [] temp;
        return *this;
    }
    bool operator==(const String& other) const {
        if (len(data)!=len(other.data)) {
            return 0;
        }
        int count = 0;
        for (int i = 0; i < len(data); i++) {
            if (data[i]==other.data[i]) {
                count++;
            }
        }
        if (count==len(data)) {
            return 1;
        }
        return 0;
    }
    bool operator<(const String& other) const {
        if (*this==other){return 0;}
        int min = std::min(len(data),len(other.data));
        for (int i = 0; i < min; i++) {
            if (data[i]<other.data[i]) {
                return 1;
            }
        }
        if (len(data)<len(other.data)) {
            return 1;
        }
        return 0;
    }
    int Find(const String& substr) const {
        if (len(data)<len(substr.data)) {
            std::cerr << "Error - длина подстроки не может быть больше строки" << '\n';
            return -1;
        }
        bool cap;
        for (int i = 0; i < len(data)-len(substr.data)+1;i++) {
            cap = 1;
            for (int j = 0; j < len(substr.data); j++) {
                if (data[i+j] != substr.data[j]) {
                    cap = 0;
                    break;
                }
            }
            if (cap){return i;}
        }
        return -1;
    }
    void Replace(char oldSymbol, char newSymbol) {
        if (!std::count(data,data+len(data),oldSymbol)) {
            std::cerr << "Error - такого символа нет в строке" << '\n';
            std::exit(-1);
        }
        char* temp = new char[len(data)+1];
        copy(temp,data);
        if (data!=nullptr) {
            delete [] data;
        }
        data = new char[len(temp)+1];
        for (int i = 0; i < len(temp); i++) {
            if (temp[i]==oldSymbol) {
                data[i] = newSymbol;
            }
            else {
                data[i] = temp[i];
            }
        }
        data[len(temp)] = '\0';
        delete [] temp;
    }
    size_t Size() const {
        return len(data);
    }
    bool Empty() const {
        if (len(data)==0){return true;}
        return false;

    }
    char operator[](size_t index) const {
        if (index<len(data)) {
            return data[index];
        }
        else {
            std::cerr << "Index is out of range" << '\n';
            std::exit(-1);
        }
    }
    char& operator[](size_t index) {
        if (index<len(data)) {
            char& ch_link=data[index];
            return ch_link;
        }
        else {
            std::cerr << "Index is out of range" << '\n';
            std::exit(-1);
        }
    }
    void RTrim(char symbol) {
        size_t count=0;
        for (int i = len(data)-1; i>=0; i--) {
            if (data[i]==symbol) {
                count++;
            }
            else {break;}
        }
        if (!count) {
            std::cerr<<"Такого символа нет."<<'\n';
            std::exit(-1);
        }
        char* temp = new char[len(data)+1];
        copy(temp,data);
        data = new char[len(temp)-count+1];
        for (int j = 0; j < len(temp)-count; j++) {
            data[j] = temp[j];
        }
        data[len(temp)-count] = '\0';
        delete [] temp;
    }
    void LTrim(char symbol) {
        size_t count=0;
        for (int i = 0; i<len(data)-1; i++) {
            if (data[i]==symbol) {
                count++;
            }
            else {break;}
        }
        if (!count) {
            std::cerr<<"Такого символа нет."<<'\n';
            std::exit(-1);
        }
        char* temp = new char[len(data)+1];
        copy(temp,data);
        data = new char[len(temp)-count+1];
        for (int j = 0; j < len(temp)-count; j++) {
            data[j] = temp[j+count];
        }
        data[len(temp)-count] = '\0';
        delete [] temp;
    }
    void swap(String& oth) {
        String temp = *this;
        *this = oth;
        oth = temp;
    }
    friend std::ostream& operator<<(std::ostream&, const String&);
};

std::ostream& operator<<(std::ostream& os, const String& str) {
    os<<str.data;
    return os;
}
String operator+(const String& a, const String& b) {
    String New = a;
    New+=b;
    return New;
}
String operator*(const String& a, unsigned int b) {
    String New = a;
    New*=b;
    return New;
}
bool operator!=(const String& a, const String& b) {
    if (!(a==b)) {
        return true;
    }
    return false;
}
bool operator>(const String& a, const String& b) {
    if (!(a<b) && (a!=b)) {
        return true;
    }
    return false;
}
int main() {
    String str1 = "___string___";
    String str1_copy = str1;
    String str2 = "hello";
    str1_copy+=str2;
    std::cout<<"Строка 1:" << str1 << '\n';
    std::cout<<"Строка 2:" << str2 << '\n';
    std::cout<<"Конкатинация:"<<str1_copy<<'\n';
    str2*=2;
    std::cout<<"Строка 2 *= 2:" << str2 << '\n';
    bool cap = str1==str2;
    std::cout<<"Строка 2 == строка 1:"<<cap << '\n';
    cap = str2 < str1;
    std::cout<<"Строка 2 < строка 1:"<< cap << '\n';
    std::cout<<"Найти в str1 подстр. string:"<< str1.Find("string") << '\n';
    str2.Replace('l','9');
    std::cout<<"Заменить в строке 2 'l' на '9':" << str2 << '\n';
    std::cout << "Size of str1:" << str1.Size() << '\n';
    std::cout << "Is str1 empty:" << str1.Empty() << '\n';
    std::cout << "Str1[3]:" << str1[3] << '\n';
    str1.RTrim('_');
    std::cout << "Str1 Rtrim _:" << str1 << '\n';
    str1.LTrim('_');
    std::cout << "Str1 Ltrim _:" << str1 << '\n';
    str1.swap(str2);
    std::cout << "Str1 after swap:" << str1<<'\n';
    std::cout << "Str2 after swap:" << str2<<'\n';
}