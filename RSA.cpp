#include <iostream>
#include <cmath>
#include <gmpxx.h> // для длинной арифметики

using namespace std;

bool isPrime(unsigned long int n) // проверка числа на простоту
{
    bool prime = true;
    for (unsigned long int i = 2; i <= round(sqrt(n)); i++)
    {
        if (n % i == 0)
        {
            prime = false;
            break;
        }
    }
    return prime;
}

unsigned long int gcd(unsigned long int a, unsigned long int b) // НОД
{
    if (a < b) swap(a, b);
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

unsigned long int pow_mod(int base, int exp, int mod) // rop = base^exp % mod
{
    mpz_t r, b, e, m;
    mpz_inits(r, b, e, m, NULL);
    mpz_set_ui(b, base);
    mpz_set_ui(e, exp);
    mpz_set_ui(m, mod);
    mpz_powm(r, b, e, m);
    return mpz_get_ui(r);
    mpz_clears(r, b, e, m);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int p, q, m, n, f, e, d, c;

    cout << " 1) Генерация ключей" << endl;
    cout << "     p = ";
    cin >> p;
    cout << "     q = ";
    cin >> q;
    n = p * q;
    cout << "     n = " << n << endl;
    f = (p - 1) * (q - 1);
    cout << "     f(n) = " << f << endl;
    for (unsigned long int i = 2; i < f; i++)
    {
        if (isPrime(i) && gcd(i, f) == 1)
        {
            e = i;
            break;
        }
    }
    cout << "     e = " << e << endl;
    cout << "     {" << e << ", " << n << "} - открытый ключ" << endl;
    int k = 2;
    d = (k * (f + 1)) / e; // d * e ≡ 1 (mod f) 
    cout << "     d = " << d << endl;
    cout << "     {" << d << ", " << n << "} - закрытый ключ" << endl;

    cout << " 2) Шифрование" << endl;
    cout << "     m = ";
    cin >> m;
    c = pow_mod(m, e, n); // c = m^e mod n
    cout << "     c = " << c << endl;

    cout << " 3) Расшифрование" << endl;
    if (m <= n)
    {
        m = pow_mod(c, d, n); // m = c^d mod n
        cout << "     m = " << m << endl;
    }
    else cout << "     m > n -> не получится" << endl;

    return 0;
}

