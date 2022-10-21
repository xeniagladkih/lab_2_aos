#include <iostream>
#include <limits>
using namespace std;

void printBinary(int n, int i)
{

    // друкує двійкове представлення
    // числа n до i-біт

    int k;
    for (k = i - 1; k >= 0; k--) {

        if ((n >> k) & 1)
            cout << "1";
        else
            cout << "0";
    }
}

// друкує неявний біт
void printBit(int n)
{
    int k = 0;
    int implicit_bit;

    //якщо перший біт мантиси - 1, то неявний біт - 0
    //якщо перший біт мантиси - 0, то неявний біт - 1

    if ((n >> k) & 1)
        implicit_bit = 0;
    else
        implicit_bit = 1;
    cout << implicit_bit << " | ";
}

typedef union {

    float f;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} myfloat;

// функція для перетворення дійсного значення
// до представлення IEEE з плаваючою точкою
void printIEEE(myfloat var)
{

    // друкує представлення IEEE 754
    // значення з плаваючою точкою (32 біти)

    cout << var.raw.sign << " | ";
    printBinary(var.raw.exponent, 8);
    cout << " | ";
    printBit(var.raw.mantissa);
    printBinary(var.raw.mantissa, 23);
}

int main()
{
    float min, lowest, max, infinity, negative_infinity, nan;
    float x = +1.0e0;//число +1,0Е0
    float denormalized = 1.0285576971e-38;//варіант для ненормалізованого ЧПТ


    min = numeric_limits<float>::min();//мінімальне за абсолютною величиною ненульове представлення
    max = numeric_limits<float>::max();//максимальне додатнє представлення
    lowest = numeric_limits<float>::lowest();//мінімальне від’ємне преставлення
    infinity = numeric_limits<float>::infinity();//значення +∞
    negative_infinity = -numeric_limits<float>::infinity();//значення -∞
    nan = numeric_limits<double>::quiet_NaN();

    cout << "s" << " | " << "hhhhhhhh" << " | " "n" << " | " << "mmmmmmmmmmmmmmmmmmmmmmm " << "Comment" << endl << endl;

    myfloat var;

    var.f = min;
    printIEEE(var);
    cout << " Minimum non-zero representation in absolute value " << "<" << var.f << ">" << endl;

    var.f = max;
    printIEEE(var);
    cout << " Maximum positive representation " << "<" << var.f << ">" << endl;

    var.f = lowest;
    printIEEE(var);
    cout << " Minimum negative representation " << "<" << var.f << ">" << endl << endl;

    var.f = x;
    printIEEE(var);
    cout << " The value is +1.0E0 " << endl;

    var.f = infinity;
    printIEEE(var);
    cout << " The value is +inf " << endl;

    var.f = negative_infinity;
    printIEEE(var);
    cout << " The value is -inf " << endl << endl;//u8"\u221E"

    var.f = denormalized;
    printIEEE(var);
    cout << " Variant of a denormalized floating-point number " << "<" << var.f << ">" << endl;

    var.f = nan;
    printIEEE(var);
    cout << " Variant of a NaN floating-point number " << endl << endl;

    cout << "Enter a float: " << endl;
    float value;
    cin >> value;
    var.f = value;
    printIEEE(var);
    cout << " Representation of the entered number " << "<" << var.f << ">" << endl;
    return 0;
}
