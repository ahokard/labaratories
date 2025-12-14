//
// Created by Антон Деев
//
#include <cstddef>
#include <cstring>

// Zadanie 1
char* CopyString(const char* str) {
    if (!str) return nullptr;

    size_t len = 0;
    while (str[len] != '\0') ++len;

    char* out = new char[len + 1];
    std::memcpy(out, str, len);
    out[len] = '\0';
    return out;
}

char* ConcatinateStrings(const char* a, const char* b) {
    if (!a && !b) return nullptr;
    if (!a) return CopyString(b);
    if (!b) return CopyString(a);

    size_t la = 0, lb = 0;
    while (a[la] != '\0') ++la;
    while (b[lb] != '\0') ++lb;

    char* out = new char[la + lb + 1];
    std::memcpy(out, a, la);
    std::memcpy(out + la, b, lb);
    out[la + lb] = '\0';
    return out;
}
// Zadanie 2
struct Matrix {
    int** data_ = nullptr;
    size_t n_ = 0u;
    size_t m_ = 0u;
};

static Matrix EmptyMatrix() {
    return Matrix{};
}

void Construct(Matrix& out, size_t n, size_t m) {
    out.data_ = nullptr;
    out.n_ = n;
    out.m_ = m;

    if (n == 0 || m == 0) {
        out.n_ = out.m_ = 0;
        return;
    }

    out.data_ = new int*[m];
    for (size_t i = 0; i < m; ++i) {
        out.data_[i] = new int[n];
        for (size_t j = 0; j < n; ++j) {
            out.data_[i][j] = 0;
        }
    }
}

void Destruct(Matrix& in) {
    if (!in.data_) {
        in.n_ = in.m_ = 0;
        return;
    }

    for (size_t i = 0; i < in.m_; ++i) {
        delete[] in.data_[i];
    }
    delete[] in.data_;
    in = EmptyMatrix();
}

Matrix Copy(const Matrix& matrix) {
    if (!matrix.data_ || matrix.n_ == 0 || matrix.m_ == 0) {
        return EmptyMatrix();
    }

    Matrix out;
    Construct(out, matrix.n_, matrix.m_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        std::memcpy(out.data_[i], matrix.data_[i],
                    matrix.n_ * sizeof(int));
    }
    return out;
}

Matrix Add(const Matrix& a, const Matrix& b) {
    if (!a.data_ || !b.data_) return EmptyMatrix();
    if (a.n_ != b.n_ || a.m_ != b.m_) return EmptyMatrix();

    Matrix out;
    Construct(out, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            out.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return out;
}

Matrix Sub(const Matrix& a, const Matrix& b) {
    if (!a.data_ || !b.data_) return EmptyMatrix();
    if (a.n_ != b.n_ || a.m_ != b.m_) return EmptyMatrix();

    Matrix out;
    Construct(out, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            out.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return out;
}

Matrix Mult(const Matrix& a, const Matrix& b) {
    if (!a.data_ || !b.data_) return EmptyMatrix();
    if (a.n_ != b.m_) return EmptyMatrix();

    Matrix out;
    Construct(out, b.n_, a.m_);

    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t k = 0; k < b.n_; ++k) {
            long long sum = 0;
            for (size_t j = 0; j < a.n_; ++j) {
                sum += static_cast<long long>(a.data_[i][j]) *
                       b.data_[j][k];
            }
            out.data_[i][k] = static_cast<int>(sum);
        }
    }
    return out;
}

void Transposition(Matrix& matrix) {
    if (!matrix.data_ || matrix.n_ == 0 || matrix.m_ == 0) return;

    Matrix t;
    Construct(t, matrix.m_, matrix.n_);

    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            t.data_[j][i] = matrix.data_[i][j];
        }
    }

    Destruct(matrix);
    matrix = t;
    t = EmptyMatrix();
}

bool operator==(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) return false;
    if (a.n_ == 0 && a.m_ == 0) return true;
    if (!a.data_ || !b.data_) return false;

    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            if (a.data_[i][j] != b.data_[i][j]) return false;
        }
    }
    return true;
}