#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
namespace MySpace
{
    int gcdExtended(int a, int b, int* x, int* y)
    {
        // Base Case
        if (a == 0)
        {
            *x = 0;
            *y = 1;
            return b;
        }

        int x1, y1; // To store results of recursive call
        int gcd = gcdExtended(b % a, a, &x1, &y1);

        // Update x and y using results of
        // recursive call
        *x = y1 - (b / a) * x1;
        *y = x1;

        return gcd;
    }

    long long lr_mod_pow1(long long x, long long y, long long m)
    {
        long long res = x;
        vector <int> Binoryindex(0);

        while (y > 0)
        {
            Binoryindex.push_back(y & 1);
            y >>= 1;
        }

        reverse(Binoryindex.begin(), Binoryindex.end());

        for (int i = 0; i < Binoryindex.size(); i++)
        {
            if (Binoryindex[i] == 1) res = (res * res * x) % m;
            else res = (res * res) % m;
        }
        return res;
    }

    long long lr_mod_pow(long long x, long long y, long long m)
    {
        long long res = x;
        vector <long long> Binoryindex(0);

        while (y > 0)
        {
            Binoryindex.push_back(y & 1);
            y >>= 1;
        }

        reverse(Binoryindex.begin(), Binoryindex.end());

        for (int i = 0; i < Binoryindex.size(); i++)
        {
            if (Binoryindex[i] == 1) res = (res * res * x) % m;
            else res = (res * res) % m;
        }
        return res;
    }

    int V2mod(int x, int m)
    {
        int res;
        int index = 1;
        if (x == 1) return 1;
        else
        {
            while (x)
                index += (x >>= 1);
            res = lr_mod_pow(2, index, m);
            return res;
        }
    }

    int gcd(int a, int b)
    {
        int remember;
        while (b != 0)
        {
            remember = b;
            b = a % b;
            a = remember;
        }
        return abs(a);
    }

    int euclid_binary(int a, int b)
    {
        if (a == 0) return b; // НОД от 0 и люого иного числа
        if (b == 0) return a;

        if (a == b) return a; // чтобы не проделывать весь цыкл (для ускорения)
        int pow2;
        for (pow2 = 0; !((a | b) & 1); pow2++) // выносим высшую степень двойки
        {
            a >>= 1;
            b >>= 1;
        }

        while (!(a & 1))	a >>= 1; // выносим высшую степень двойки почленно  
        // начиая отсюда а - нечетное

        while (!(b & 1))
        {
            b >>= 1;
        }

        while (b != 0)
        {
            if (a > b)
                swap(a, b); // Swap u and v.
            b -= a;
            while (!(b & 1))
            {
                b >>= 1;
            }
        }
        return a << pow2; // выводим мод, не забывая про степень 2
    }

    int lcm(int n1, int n2)
    {                                              //caculating lcm using the formula: lcm x gcd = n1 x n2
        int res, g;
        g = gcd(n1, n2);
        res = n1 * n2 / g;
        return res;
    }

    int euclid_recursive_1(int a, int b)
    {
        if (a == 0) return abs(b);
        if (a == b || b == 0) return abs(a);
        if (a > b) euclid_recursive_1(a - b, b);
        else euclid_recursive_1(a, b - a);
    }

    int euclid_recursive_2(int a, int b)
    {
        return b ? euclid_recursive_2(b, a % b) : abs(a);
    }

    int Matrix_multiplication(vector <int> Matrix_elements, int first, int second, int& l, int& k)
    {
        int gsd;
        int next_a, c = 1, b = 1, d = 0, t = 0;
        int remember_a, remember_c, remember_b;
        remember_a = Matrix_elements[0];
        for (int i = 1; i < Matrix_elements.size(); i++)
        {
            if (c == second) break;
            remember_c = c;
            remember_b = remember_a;
            next_a = Matrix_elements[i];
            remember_a = next_a * remember_a + b;
            c = next_a * c + d;
            b = remember_b;
            d = remember_c;
            t++;
        }
        if (t & 1)
        {
            gsd = first * d - second * b;
            k = -b;
            l = d;
        }
        else
        {
            gsd = -first * d + second * b;
            k = b;
            l = -d;
        }//d  = x b = y
        return gsd;
    }

    int My_gcd__ex(int x, int y, int& l, int& k)
    {
        vector <int> Matrix_elements;
        if (x == 0) return y; // НОД от 0 и люого иного числа
        if (y == 0) return x;

        int b, d, t = 0;
        int incomplete;
        int remain = y;

        if (x < y) swap(x, y);
        int first = x, second = y;
        while (remain != 0)
        {
            incomplete = x / y;
            Matrix_elements.push_back(incomplete);
            remain = x % y;
            x = y;
            y = remain;
        }
        // for (int i = 0; i < Matrix_elements.size(); i++) cout << Matrix_elements[i] << ' ';
        return Matrix_multiplication(Matrix_elements, first, second, l, k);
    } 
    // не праавильно выдает y;

    int mul_inv(int a, int m)
    {
        int x, y;
        int g = My_gcd__ex(a, m, x, y); // ax + my = 1  // ax = 1 - my // (1-my) % m=1 // ax % m = 1 // a%m * x%m =1 // a%m = 1/x%m // a%m = (1/x)%m
        if (g != 1)
            return 0;
        else
        {
            // res = x % m; // (a*x)%m=1-def a%m * x%m=1   x%m = 1/a%m
            return (x % m + m) % m; // 0 < res < m
        }
    }

    int linear_diophantine_two(const int a, const int b, const int c, int& x0, int& y0, int& d)
    {
        d = My_gcd__ex(abs(a), abs(b), x0, y0);
        if (c % d != 0) // ax0+by0=1
            return 0;	// 
        x0 *= c / d;
        y0 *= c / d;
        if (a < 0)
            x0 *= -1;
        if (b < 0)
            y0 *= -1;
        return d;
    }

    int linear_diophantine(int* a, int* x, int n, int b)
    {
        int gcd = *a, gcd_x, i, j, q;

        *x = 1;
        for (i = 1; i < n; i++)
        {
            gcd = My_gcd__ex(gcd, a[i], gcd_x, x[i]);
            for (j = 0; j < i; j++)
                x[j] *= gcd_x;
        }

        if (b % gcd)
            return 0;
        q = b / gcd;
        for (j = 0; j < n; j++)
        {
            x[j] *= q;
            cout << x[j] << ' ';
        }
        return gcd;
    }

    int chinese_reminder_a(vector <int>& rem, vector <int>& pr)
    {
        int x, cd, i, p, r;
        bool check;                                  // we use this to count the max checks, we can keep it as much as we want
        x = rem[0];                                   // let us say the first number will be the starting and 
        cd = pr[0];                               // the first remainder will be the common difference like we saw in the example
        for (i = 1; i < rem.size(); i++)
        {
            check = false;
            while (true)                      // Here we have taken a max value for 10^5 because we are dealing with large numbers
            {
                if (x % pr[i] == rem[i])                // condition for finding the next start value
                {
                    check = true;
                    break;
                }
                x += cd;
            }
            if (!check)                           // This means that no number until cnt range has matched the condition.
            {
                cout << "No solution.";            // Hence no solution is possible
                return 0;
            }
            cd = lcm(pr[i], cd);                      // updating the cd
        }
        // cout << x << " " << cd << endl;
        return x;
    }

    int chinese_reminder_b(vector <int>& rem, vector <int>& pr)
    {
        int M = 1, m, y, res = 0;
        for (int i = 0; i < rem.size(); i++)
        {
            M *= pr[i];
        }
        for (int i = 0; i < rem.size(); i++)
        {
            m = M / pr[i];
            y = mul_inv(m, pr[i]);
            res += m * y * rem[i];
        }
        res = res % M;
        return res;
    }

    int legendre_sympol_a(const int a, const int p) 
    {
        if (a % p == 0) return 0;
        else if (lr_mod_pow(a, (p - 1) / 2, p) == 1) return 1;
        else return -1;
    }
}