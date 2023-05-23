#include <iostream>

using namespace std;

typedef struct big_int
{
    unsigned int length;
    //int sign;
    unsigned char* number;

} big_int;

void big_int_free(big_int* n)
{
    free(n->number);
    free(n);
}

big_int* get_big_int(const char* num_bi)
{
    int i, length;
    big_int* a = (big_int*)malloc(sizeof(big_int));
    if (a)
    {
        length = strlen(num_bi);         
        if (!(length & 7))
            a->length = (length >> 3);
        else  a->length = (length >> 3) + 1;
        a->number = (unsigned char*)calloc(a->length, sizeof(a->number));
        if (a->number == NULL)
            return NULL;
        for (i = 0; i < length; i++)
            a->number[i >> 3] += (num_bi[length - i - 1] - '0') << (i & 7);   // 11100000 00111100 01000100 10000001   1&000 = 0 111&001=001  
    }
    return a;
}

void big_int_print(big_int* n)
{
    if (!n)
    {
        cout << 0;
        return;
    }
    int len = n->length;
    unsigned char flag_bit = 0x80; // 10000000
    cout << "Bin ";

    while (!(n->number[len - 1] & flag_bit) && flag_bit > 1) // 00001000                      
        flag_bit >>= 1;                                      // 10000000

    for (; flag_bit; flag_bit >>= 1)
        cout << ((n->number[len - 1] & flag_bit) > 0);

    for (len = len - 2; len >= 0; len--)
    {
        for (flag_bit = 0x80; flag_bit; flag_bit >>= 1)
        {
            cout << !!(n->number[len] & flag_bit);
        }
    }
    cout << endl;
}

big_int* big_int_add(big_int* n1, big_int* n2)
{
    big_int* a;
    unsigned int i, len;
    unsigned int result;
    unsigned char l, m, carry = 0;
   
    if ((a = (big_int*)malloc(sizeof(big_int))) == NULL)
        return NULL;

    if (n1->length > n2->length)
        len = n1->length + 1;
    else
        len = n2->length + 1;
    a->length = len;

    if ((a->number = (unsigned char*)malloc(len)) == NULL)
        return NULL;

    for (i = 0; i < len - 1; i++)
    {
        l = 0;
        m = 0;
        if (i < n1->length)
            l = n1->number[i];

        if (i < n2->length)
            m = n2->number[i];

        result = l + m + carry;
        a->number[i] = result;
        carry = (result > 0xFF);
    }

    if (carry == 0)
    {
        a->length--;// = len - 1;
        a->number = (unsigned char*)realloc(a->number, a->length);
        if (a->number == NULL)
            return NULL;
    }
    else
        a->number[len - 1] = 1;
    return a;
}

/// <summary>
/// Comparison of two big_ints
/// </summary>
/// <param name="n1"></param>
/// <param name="n2"></param>
/// <returns>true if n1 >= n2 and false otherwise</returns>
bool big_int_compare(big_int* n1, big_int* n2) {
    bool check = true;
    if (n1->length < n2->length)
        check = false;
    else if (n1->length > n2->length)
        check = true;
    else
    {
        // провера уменьшаемого и вычитаемого 
        for (int i = 0; i < n1->length; i++)
        {
            if (n1->number[i] > n2->number[i])
            {
                check = true;
            }
            if (n1->number[n1->length - 1 - i] < n2->number[n1->length - 1 - i])
            {
                return false;
            }
        }
    }
    return check;
}

big_int* big_int_dif (big_int* n1, big_int* n2)
{
    big_int* a;
    int  len, len_2, result;
    unsigned char l, m, borrow = 0;
    //unsigned char flag_bit = 0x80;
    int k;

    if ((a = (big_int*)malloc(sizeof(big_int))) == NULL)
        return NULL;
    len = n1->length;
    len_2 = n2->length;
    a->length = len;

    if ((a->number = (unsigned char*)malloc(len)) == NULL)
        return NULL;
    if (big_int_compare(n1, n2)) {
        for (int i = 0; i < len; i++)
        {
            l = n1->number[i];
            if (len_2 > i)
            {
                m = n2->number[i];
            }
            else m = 0;
            k = m + borrow; // тк m+borrow может быть больше 256 и тогда значение обнулиться 
            if (l >= k)
            {
                result = l - m - borrow;
            }
            else
            {
                result = 0x100 + l;
                result = result - m - borrow;
            }
            borrow = (l < k);
            a->number[i] = result;
        }
        int p = 0;
        for (; a->number[a->length - 1 - p] == 0; p++);
        if (p)
        {
            a->length -= p;
            a->number = (unsigned char*)realloc(a->number, a->length);
            if (a->number == NULL)
                return NULL;
        }
    }
    else {
        big_int_free(a);
        //cout << "ERR: n2>n1" << endl;
        return NULL;
    }
    return a;
}

big_int* big_int_mull_one(big_int* n1, int l)
{
    big_int* res;

    if (l == 0) return res = get_big_int("0");

    int len = n1->length, len_res = len + 1;
    int x, a;
    char carry = 0;

    if ((res = (big_int*)malloc(sizeof(big_int))) == NULL)
        return NULL;
    if ((res->number = (unsigned char*)malloc(len_res)) == NULL)
        return NULL;       

    for (int i = 0; i < len; i++)
    {
        x = n1->number[i];
        a = carry + x * l;
        res->number[i] = (char)(a % 256);
        if (a > 256)
            carry = (char)(a >> 8);
        else carry = 0;
    }

    if (carry == 0)
    {
        len_res--;// = len - 1;
        res->number = (unsigned char*)realloc(res->number, res->length);
        if (res->number == NULL)
            return NULL;
    }
    else
        res->number[len_res - 1] = carry;
    return res;
}

//if (l & 255 == 0)
//{
//    res = n1;
//    res->length += (l >> 8);
//    for (int i = 0; i < res->length - len; i++)
//    {
//        res->number[res->length - 1 - i] = 0;
//    }
//    return res;
//}
big_int* big_int_mull(big_int* n1, big_int* n2)
{
    big_int* res,* a;
    int len1 = n1->length, len2 = n2->length;
    res = big_int_mull_one(n1, (int)n2->number[0]);
    for (int i = 1; i < len2; i++)
    {
        a = big_int_mull_one(n1, ((int)n2->number[i] ) * pow(256,i+1));
        res = big_int_add(res, a);
    }
    return res;
}
void test_big_int_mull() {
    big_int* a, * b, * c;
    a = get_big_int("1010011110101010");//00000101 00000100 00001000 11111111 00001001
    b = get_big_int("100100101010010101010100");//10010010 10100101 01010101
    c = big_int_mull_one(b, 4);             //00000100 00000001 11000000 00000000 00000000
    big_int_print(c);//11111101000011100100100101110011000001000
    big_int_free(a); //111111011111110111101110001111000001011001101000
    big_int_free(b);
}

void test_big_int_dif(int i) 
{
    big_int* a, * b, *c;
    a = get_big_int("1111111111111110"); //00000101 00000100 00001000 11111111 00001001
    b = get_big_int("10000000000000000");//00000001 00000010 01001000 11111111 00001001
    c = big_int_dif(b, a);
    big_int_print(a);
    big_int_print(b);
    big_int_print(c);
    int u;
    scanf_s("%d", &u);
    //big_int_free(a);    
    //big_int_free(b);
    //big_int_free(c);
}
int main() 
{
        test_big_int_mull();
   return 0;
}
