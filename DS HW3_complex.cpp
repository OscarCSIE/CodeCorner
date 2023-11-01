#include <iostream>

/*
https://www.programiz.com/cpp-programming/operator-overloading
https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/
*/

class Complex {
private:
    double m_real;
    double m_imag;
    // (a + bi) + (c + di) = (a + c) + (c + d)i
    // (a + bi) * (c + di) = ([a * c] - [b * d] ) + ([b * c] + [a * d])i

public:
    Complex(double real = 0, double imag = 0){
        m_real = real;
        m_imag = imag;
    }

    //overloading +
    Complex operator + (const Complex& other) {
        return Complex(m_real + other.m_real, m_imag + other.m_imag);
    }

    //overloading *
    Complex operator * (const Complex& other) {
        return Complex(m_real * other.m_real - m_imag * other.m_imag, m_imag * other.m_real + m_real * other.m_imag);
    }

    //overloading cin>>
    friend std::istream& operator>>(std::istream& in, Complex& complex) {
        in >> complex.m_real >> complex.m_imag;
        return in;
    }

    //overloading cout<< c1 ==> ab
    friend std::ostream& operator<<(std::ostream& out, const Complex& complex) {
        out <<" ( "<< complex.m_real << " + " << complex.m_imag << "i ) ";
        return out;
    }
};

int main() {
    
    Complex c1(3, 2);
    Complex c2;

    Complex c3, c4;

    std::cout << "Enter a complex number: \n";
    std::cin >> c3;

    std::cout << "Enter another complex number \n";
    std::cin >> c4;

    // Output the results using cout
    std::cout << "c1 is " <<c1<< std::endl;
    std::cout << "c2 is " <<c2<< std::endl;
    std::cout << "c3 is " <<c3<< std::endl;
    std::cout << "c4 is " <<c4<< std::endl;
    
    std::cout << "Sum of the results" << std::endl;
    std::cout << "c1 + c2: " << c1 << " + " << c2 << " = " << c1 + c2 << std::endl;
    std::cout << "c1 + c3: " << c1 << " + " << c3 << " = " << c1 + c3 << std::endl;
    std::cout << "c1 + c4: " << c1 << " + " << c4 << " = " << c1 + c4 << std::endl;
    std::cout << "c2 + c3: " << c2 << " + " << c3 << " = " << c2 + c3 << std::endl;
    std::cout << "c2 + c4: " << c2 << " + " << c4 << " = " << c2 + c4 << std::endl;
    std::cout << "c3 + c4: " << c3 << " + " << c4 << " = " << c3 + c4 << std::endl;

    std::cout << "Product of the results" << std::endl;
    std::cout << "c1 * c2: " << c1 << " * " << c2 << " = " << c1 * c2 << std::endl;
    std::cout << "c1 * c3: " << c1 << " * " << c3 << " = " << c1 * c3 << std::endl;
    std::cout << "c1 * c4: " << c1 << " * " << c4 << " = " << c1 * c4 << std::endl;
    std::cout << "c2 * c3: " << c2 << " * " << c3 << " = " << c2 * c3 << std::endl;
    std::cout << "c2 * c4: " << c2 << " * " << c4 << " = " << c2 * c4 << std::endl;
    std::cout << "c3 * c4: " << c3 << " * " << c4 << " = " << c3 * c4 << std::endl;

    return 0;
}
