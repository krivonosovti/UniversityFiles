#include <vector>
#pragma once

using namespace std;

namespace MySpace
{
	int gcdExtended(int a, int b, int* x, int* y);
	long long lr_mod_pow1(long long x, long long y, long long m);
	long long lr_mod_pow(long long x, long long y, long long m);
	int V2mod(int x, int m);
	int gcd(int a, int b);
	int euclid_binary(int a, int b);
	int lcm(int n1, int n2);
	int euclid_recursive_1(int a, int b);
	int euclid_recursive_2(int a, int b);
	int Matrix_multiplication(vector <int> Matrix_elements, int first, int second, int& k, int& l);
	int My_gcd__ex(int x, int y, int& k, int& l);
	int mul_inv(int a, int m);
	int linear_diophantine_two(const int a, const int b, const int c, int& x0, int& y0, int& d);
	int linear_diophantine(int* a, int* x, int n, int b);
	int chinese_reminder_a(vector <int>& rem, vector <int>& pr);
	int chinese_reminder_b(vector <int>& rem, vector <int>& pr); 
	int legendre_sympol_a(const int a, const int p);

}