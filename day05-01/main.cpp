#include <iostream>
#include <cstring>

class Complex {
public:
    Complex(int r = 0, int i = 0) : _real(r), _imaginary(i) {}

    void print() const {
        std::cout << _real << "+" << _imaginary << "i" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& lhs, const Complex& rhs) {
        return lhs << rhs._real << '+' << rhs._imaginary << 'i';
    }

    friend std::istream& operator >> (std::istream& lhs, Complex& rhs) {
        return lhs >> rhs._real >> rhs._imaginary;
    }

private:
    int _real;
    int _imaginary;
};

int main() {
    Complex c1, c2;
    // ::operator>>(::operator>>(cin, c1), c2)
    std::cin >> c1 >> c2;
    // ::operator<<(::operator<<(::operator<<(cout, c1), ','), c2);
    std::cout << c1 << ',' << c2;
    std::cout << std::endl;

    return 0;
}
