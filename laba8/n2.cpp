//
// Created by Антон Деев
//
#include <iostream>
using namespace std;

struct Matrix {
    int** data = nullptr;
    int*  buffer = nullptr;
    size_t rows = 0, cols = 0;
};

bool IsValid(const Matrix& m) {
    return m.data && m.buffer && m.rows > 0 && m.cols > 0;
}

void Create(Matrix& m, size_t r, size_t c) {
    m.rows = r;
    m.cols = c;

    m.data = new int*[r];
    m.buffer = new int[r * c];

    for (size_t i = 0; i < r * c; ++i) m.buffer[i] = 0;

    for (size_t i = 0; i < r; ++i)
        m.data[i] = m.buffer + i * c;
}

void Destroy(Matrix& m) {
    delete[] m.buffer;
    delete[] m.data;

    m.buffer = nullptr;
    m.data = nullptr;
    m.rows = 0;
    m.cols = 0;
}

Matrix Clone(const Matrix& src) {
    Matrix res;
    if (!IsValid(src)) return res;

    Create(res, src.rows, src.cols);
    for (size_t i = 0; i < src.rows * src.cols; ++i)
        res.buffer[i] = src.buffer[i];

    return res;
}

bool SameSize(const Matrix& a, const Matrix& b) {
    return a.rows == b.rows && a.cols == b.cols;
}

Matrix Sum(const Matrix& a, const Matrix& b) {
    if (!IsValid(a) || !IsValid(b)) return Matrix{};
    if (!SameSize(a, b)) return Matrix{};

    Matrix res;
    Create(res, a.rows, a.cols);

    for (size_t i = 0; i < a.rows * a.cols; ++i)
        res.buffer[i] = a.buffer[i] + b.buffer[i];

    return res;
}

Matrix Diff(const Matrix& a, const Matrix& b) {
    if (!IsValid(a) || !IsValid(b)) return Matrix{};
    if (!SameSize(a, b)) return Matrix{};

    Matrix res;
    Create(res, a.rows, a.cols);

    for (size_t i = 0; i < a.rows * a.cols; ++i)
        res.buffer[i] = a.buffer[i] - b.buffer[i];

    return res;
}

Matrix Product(const Matrix& a, const Matrix& b) {
    if (!IsValid(a) || !IsValid(b)) return Matrix{};
    if (a.cols != b.rows) return Matrix{};

    Matrix res;
    Create(res, a.rows, b.cols);

    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < b.cols; ++j) {
            int s = 0;
            for (size_t k = 0; k < a.cols; ++k)
                s += a.data[i][k] * b.data[k][j];
            res.data[i][j] = s;
        }
    }
    return res;
}

void Transpose(Matrix& m) {
    if (!IsValid(m)) return;

    Matrix t;
    Create(t, m.cols, m.rows);

    for (size_t i = 0; i < m.rows; ++i)
        for (size_t j = 0; j < m.cols; ++j)
            t.data[j][i] = m.data[i][j];

    Destroy(m);
    m = t;
}

bool operator==(const Matrix& a, const Matrix& b) {
    if (!IsValid(a) && !IsValid(b)) return true;
    if (!IsValid(a) || !IsValid(b)) return false;
    if (!SameSize(a, b)) return false;

    for (size_t i = 0; i < a.rows * a.cols; ++i)
        if (a.buffer[i] != b.buffer[i]) return false;

    return true;
}

void Print(const Matrix& m, const char* name = "") {
    if (name && name[0]) cout << name << " (" << m.rows << "x" << m.cols << "):\n";
    if (!IsValid(m)) {
        cout << "Empty\n\n";
        return;
    }

    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j)
            cout << m.data[i][j] << "\t";
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    Matrix a, b;
    Create(a, 2, 3);
    Create(b, 2, 3);

    int v1[2][3] = { {1,2,3}, {4,5,6} };
    int v2[2][3] = { {7,8,9}, {10,11,12} };

    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 3; ++j) {
            a.data[i][j] = v1[i][j];
            b.data[i][j] = v2[i][j];
        }

    Print(a, "A");
    Print(b, "B");

    Matrix c = Clone(a);
    Print(c, "Clone(A)");

    Matrix s = Sum(a, b);
    Print(s, "A + B");

    Matrix d = Diff(b, a);
    Print(d, "B - A");

    Destroy(s);
    Destroy(d);

    Matrix x, y;
    Create(x, 3, 2); // 3x2
    Create(y, 2, 3); // 2x3

    int vx[3][2] = { {1,2}, {3,4}, {5,6} };
    int vy[2][3] = { {7,8,9}, {10,11,12} };

    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 2; ++j)
            x.data[i][j] = vx[i][j];

    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 3; ++j)
            y.data[i][j] = vy[i][j];

    Print(x, "X");
    Print(y, "Y");

    Matrix p = Product(x, y);
    Print(p, "X * Y");
    Destroy(p);

    Matrix t = Clone(a);
    Print(t, "T");
    Transpose(t);
    Print(t, "Transpose(T)");

    Matrix a2 = Clone(a);
    cout << "A == Clone(A): " << (a == a2) << "\n";
    cout << "A == B: " << (a == b) << "\n\n";

    Destroy(a);
    Destroy(b);
    Destroy(c);
    Destroy(x);
    Destroy(y);
    Destroy(t);
    Destroy(a2);

    return 0;
}
