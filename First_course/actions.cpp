#include <iostream>
#include "decl.h"
 
using namespace std;
int main()
{
    /*int x = 1, y = 1, a = 35, b = 15;
    cout << MySpace::gcdExtended(a, b, &x, &y) << ' ' << x  << ' ' << y << endl;
    cout << MySpace::My_gcd__ex(a, b, x, y) << ' ' << x  << ' ' << y << endl;
	cout << MySpace::lcm(4, 6) << endl;
    vector<int> pr{ 7,11,13 }, rem{ 5,3,10 };
    cout << MySpace::chinese_reminder_a(rem, pr) << endl;
    cout << MySpace::chinese_reminder_b(rem, pr) << endl;*/
    cout << MySpace::legendre_sympol_a(7, 3)<<endl;
    return 0;
}