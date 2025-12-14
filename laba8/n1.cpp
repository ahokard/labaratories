//
// Created by Антон Деев
//
#include <iostream>
#include <cstring>

int StrLen(const char* s) {
    if (!s) return 0;
    int n = 0;
    while (s[n] != '\0') {
        ++n;
    }
    return n;
}

char* CopyCStr(const char* s) {
    if (!s) return nullptr;

    const int n = StrLen(s);
    char* out = new char[n + 1];

    for (int i = 0; i < n + 1; ++i) {
        out[i] = s[i];
    }
    return out;
}

char* ConcatManual(const char* a, const char* b) {
    if (!a && !b) return nullptr;
    if (!a) return CopyCStr(b);
    if (!b) return CopyCStr(a);

    const int na = StrLen(a);
    const int nb = StrLen(b);

    char* out = new char[na + nb + 1];

    int k = 0;
    for (int i = 0; i < na; ++i) out[k++] = a[i];
    for (int i = 0; i < nb; ++i) out[k++] = b[i];
    out[k] = '\0';

    return out;
}

char* ConcatMemcpy(const char* a, const char* b) {
    if (!a && !b) return nullptr;
    if (!a) return CopyCStr(b);
    if (!b) return CopyCStr(a);

    const int na = StrLen(a);
    const int nb = StrLen(b);

    char* out = new char[na + nb + 1];

    std::memcpy(out, a, na);
    std::memcpy(out + na, b, nb);
    out[na + nb] = '\0';

    return out;
}

void Release(char* p) {
    delete[] p;
}

void PrintCStr(const char* s, const char* name) {
    std::cout << name << ": ";
    if (!s) {
        std::cout << "nullptr\n";
        return;
    }
    std::cout << "\"" << s << "\" (size: " << StrLen(s) << ")\n";
}

int main() {
    const char* src = "Data Structures";
    char* cpy = CopyCStr(src);

    PrintCStr(src, "Source");
    PrintCStr(cpy, "Copy");
    Release(cpy);

    std::cout << "\n";

    const char* left  = "Computer ";
    const char* right = "Science";
    char* joined1 = ConcatMemcpy(left, right);

    PrintCStr(left, "Left");
    PrintCStr(right, "Right");
    PrintCStr(joined1, "Joined (memcpy)");
    Release(joined1);

    std::cout << "\n";

    char* joined2 = ConcatManual("Hello ", "World!");
    PrintCStr(joined2, "Joined (manual)");
    Release(joined2);

    return 0;
}
