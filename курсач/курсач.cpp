//  main.cpp
//  RSA
//
//  Created by Sergiy on 06.06.17.

#include <iostream>
#include <climits>
#include <cmath>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <ctime>
using namespace std;

bool isPrime(long long prime);
long long calculateE(long long t);
long long greatestCommonDivisor(long long e, long long t);
long long calculateD(long long e, long long t);
long long encrypt(long long i, long long e, long long n);
long long decrypt(long long i, long long d, long long n);

int main()
{
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
      long long p, q, n, t, e, d;
      bool test;
      long long encryptedText[100];
    memset(encryptedText, 0, sizeof(encryptedText));

     long long decryptedText[100];
    memset(decryptedText, 0, sizeof(decryptedText));

    bool flag;
    cout << "Введите сообщение" << endl;
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    int i, len; //Определяем необходимые переменные
    char oStr[1000];
    cin.getline(oStr, 1000, '\n');
    len = strlen(oStr);

      int* key = new int[len]; //точно такой же массив объявляем для ключа

      char* shStr = new char[len]; //массив-приемник для зашифрованного текста
      // определяем ключ случайным образом
    cout << "Случаный ключ сессии: ";
    for (i = 0; i < len; i++) {

        key[i] = 1+rand()%98 ;
        cout << key[i]<<' ';

    }

    //собственно само шифрование

    for (i = 0; i < len; i++)

        shStr[i] = oStr[i] ^ key[i];

    //для наглядности выведем на экран результат работы

    cout << "\nИсходный текст: ";
    for (int i = 0; i < len; i++)
        cout << oStr[i];
    cout << "\nЗашифрованный текст: ";
    for (int i = 0; i < len; i++)
        cout << shStr[i];
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Cоздание открытого и секретного ключей

    // 1. Выбираются два различных случайных простых числа p и q заданного размера

    do
    {
        cout << "\nВведите первое простое число (больше 10): " << endl;
        cin >> p;
        flag = isPrime(p);

        if (flag == false || p < 10)
        {
            cout << "\nОшибка ввода - число не является простым или меньше десяти\n" << endl;
        }
    } while (flag == false || p <10);

    do
    {
        cout << "Введите второе простое число (больше 10): " << endl;
        cin >> q;
        flag = isPrime(q);

        if (flag == false || q<10 ||p==q)
        {
            cout << "\nОшибка ввода - число или не является простым, или меньше десяти, или равно первому простому числу\n" << endl;
        }
    } while (flag == false || q < 10 ||p==q);

    // 2. Вычисляется их произведение n = p ⋅ q, которое называется модулем.
    n = p * q;
    cout << "\nМодуль простых чисел равен: " << n << endl;

    // 3. Вычисляется значение функции Эйлера от числа n: φ(n) = (p−1)⋅(q−1)
    t = (p - 1) * (q - 1);
    cout << "Результат функции Эйлера: " << t << endl;

    // 4. Выбирается целое число e ( 1 < e < φ(n) ), взаимно простое со значением функции Эйлера (t)
    //	  Число e называется открытой экспонентой
    e = calculateE(t);

    // 5. Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))
    d = calculateD(e, t);

    // 6. Пара {e, n} публикуется в качестве открытого ключа RSA
    cout << "\nОткрытый ключ ассиметричного шифрования " << n << "\t" << e << endl;

    // 7. Пара {d, n} играет роль закрытого ключа RSA и держится в секрете
    cout << "Закрытый ключ ассиметричного шифрования: " << n << "\t" << d << endl;

    // encryption
    //-----------------------------------------------------------------------------------

    for (long long i = 0; i < len; i++)
    {
        encryptedText[i] = encrypt(key[i], e, n);
    }

    cout << "\nЗашифрованный ключ сессии:" << endl;

    for (long long i = 0; i < len; i++)
    {
        cout << encryptedText[i] << ' ';
    }


    //decryption

    for (long long i = 0; i < len; i++)
    {
        decryptedText[i] = decrypt(encryptedText[i], d, n);
    }

    cout << "\n\nДешифрованный ключ сессии:" << endl;

    for (long long i = 0; i < len; i++)
    {
        cout<<decryptedText[i]<<' ';
    }
    //----------------------------------------------------------------------------------------
    cout << endl;
    for (i = 0; i < len; i++) {
        shStr[i] = shStr[i] ^ decryptedText[i];
        cout << shStr[i];
    }
    cout << endl << endl;

    system("PAUSE");

    return 0;
}

bool isPrime(long long prime)
{
    long long i, j;

    j = (long long)sqrt((long double)prime);

    for (i = 2; i <= j; i++)
    {
        if (prime % i == 0)
        {
            return false;
        }
    }

    return true;
}

long long calculateE(long long t)
{
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

    long long e;

    for (e = 2; e < t; e++)
    {
        if (greatestCommonDivisor(e, t) == 1)
        {
            return e;
        }
    }

    return -1;
}

long long greatestCommonDivisor(long long e, long long t)
{
    while (e > 0)
    {
        long long myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long long calculateD(long long e, long long t)
{
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    long long d;
    long long k = 1;

    while (1)
    {
        k = k + t;

        if (k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}

long long encrypt(long long i, long long e, long long n)
{
    long long current, result;

    current = i-97;
    result = 1;

    for (long long j = 0; j < e; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result;
}

long long decrypt(long long i, long long d, long long n)
{
    long long current, result;

    current = i;
    result = 1;

    for (long long j = 0; j < d; j++)
    {
        result = result * current;
        result = result % n;
    }

    return result+97;
}


