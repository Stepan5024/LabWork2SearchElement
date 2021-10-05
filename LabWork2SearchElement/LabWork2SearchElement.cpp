// Лабораторная работа №2 
// Выполнили студенты группы м3о-219Бк-20 Бокарев, Катвалян

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<chrono> // подключение библиотеки для вычисления времени работы алгоритмов 

#define NotFound -1;

using namespace std;

void FillRand(int* arr, int n, double min, double max); // Функция, формирующая рандомную последовательность
void Sort(int* arr, int length); // Функция, сортирующая последовательность
void Writer(int* A, int length); // Функция, печатающая последовательность
int QSearch(int* A, int x, int n); // Функция быстрого последовательного поиска в лекциях Sentinel_Linear_Search 
int SSearch(int* A, int x, int n); // Функция последовательного поиска в лекциях Better_Linear_Search
int TSearch(int* A, int x, int n); // Функция последовательного поиска в упорядоченном массиве
int BSearch(int* A, int x, int n); // Функция бинарного поиска

int main()
{
    setlocale(LC_ALL, "Russian");
    system("color F0");
    srand(time(NULL));
    int n = 0;
    cout << "Введите размер последовательности: "; cin >> n;
    int length = n += 1;
    
    cout << "Рандомная последовательность" << endl;

    int* arrRand = new int[length]; // рандомная последовательность
    FillRand(arrRand, n, 0, 600000);
    
    int (*SearchOperations[4])(int*, int, int) = { QSearch, SSearch, TSearch, BSearch }; // Указатель на массив функций
    
    int lengthLin = sizeof(SearchOperations) / sizeof(SearchOperations[0]);// получаем длину массива
    //int keyRand; cout << "Введите ключ поиска в рандомной последовательности: "; cin >> keyRand;
    //int keyGrow; cout << "Введите ключ поиска в возрастающей последовательности: "; cin >> keyGrow;
    for (int i = 0; i < lengthLin - 2; i++) // цикл по рандомной последовательности
    {
        for (int j = 0; j < 3; j++) {
            int key = 0;

            if (j == 0) key = arrRand[0]; // ключ поиска
            else if (j == 1) key = arrRand[length / 2]; // ключ поиска
            else if (j == 2) key = arrRand[length - 1]; // ключ поиска*/
            auto begin = chrono::steady_clock::now(); // получаем время перед началом формирования последовательности
            
            int result = SearchOperations[i](&arrRand[0], key, length);    // вызов функции по указателю

            auto end = chrono::steady_clock::now();// получаем время по окончанию формирования последовательности

            auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);// получаем время работы в микросекундах
            if (result >= 0) {
                cout << "Процедура " << i << " индекс равен : " << result << endl;
            }
            else {
                cout << "Процедура " << i << " элемент не найден" << endl;
            }
            //cout << elapsed_ms.count() << endl; // вывод времени
        }
    }
    Sort(arrRand, length);
    for (int i = 2; i < lengthLin; i++) // цикл по возрастающей последовательности
    {
        for (int j = 0; j < 3; j++) {
            int key = 0;
            if (j == 0) key = arrRand[0]; // ключ поиска
            else if (j == 1) key = arrRand[length / 2]; // ключ поиска
            else if (j == 2) key = arrRand[length - 1]; // ключ поиска*/
            auto begin = chrono::steady_clock::now(); // получаем время перед началом формирования последовательности
            //cout << "Процедура " << i << " ключ поиска : " << key << endl;
            //key = keyGrow;
            int result = SearchOperations[i](&arrRand[0], key, length);    // вызов функции по указателю
                
          
            auto end = chrono::steady_clock::now();// получаем время по окончанию формирования последовательности

            auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);// получаем время работы в микросекундах
            if (result >= 0) {
                cout << "Процедура " << i << " индекс равен : " << result << endl;
            }
            else {
                cout << "Процедура " << i << " элемент не найден" << endl;
            }
            //cout << elapsed_ms.count() << endl; // вывод времени
        }
    }

    

}
int SSearch(int* arr, int key, int size) { // реализован по блоксхеме ✔️
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        count += 2; // две операции сравнения, первая не вышли ли за размер массива, вторая на равенство ключу
        if (arr[i] == key) {
            cout << "Количество операций сравнения для SSearch " << count << endl;
            return i;
        }
    }
    cout << "Количество операций сравнения для SSearch " << count << endl;
    return NotFound;

}
int QSearch(int* arr, int key, int size) { // реализован по блоксхеме ✔️
    int i = 0;
    int count = 0;
    int last = arr[size];
    arr[size] = key;
    for (i; arr[i] != key; i++) {
        count++; // одно сравнение, чтобы найти ключ поиска
    }
    arr[size] = last;
    if (i < size || arr[size] == key) {
        cout << "Кол-во сравнений QSearch = " << count << endl;        
        return i;
    }
    else { 
        cout << "Кол-во сравнений QSearch = " << count << endl; 
        return NotFound; 
    }
    
}
int TSearch(int* arr, int key, int size) {// реализован по блоксхеме ✔️
    int i = 0; // текущий индекс
    int count = 0; // счетчик сравнений
    while (key > arr[i]) { // увеличиваем текущий индекс до тех пор, пока ключ будет 
        i++; //меньше или равен i-ому элементу в возраст. массиве
        count++; // прибавляем один, тк выполняется одна операция сравнения
    }
    cout << "Кол-во сравнений TSearch = " << count << endl;
    if (key == arr[i]) { 
        return i;
    }
    else {
        return NotFound;
    }
}
int BSearch(int* arr, int key, int size) {// реализован по блоксхеме ✔️ 
    int count = 0; // счетчик сравнений
    int p = 0; // Первый элемент массива
    int r = size - 1; // последний элемент массива
    while (p <= r) { // до тех пор пока начальная граница меньше конечной границы
        int q = (p + r) / 2; // серединный элемент
        if (arr[q] == key) {
            count += 2;
            cout << "Кол-во сравнений BSearch = " << count << endl;
            return  q;
        }
        else if (arr[q] > key) { // ключ поиска меньше, значения серединного элемента, уменьшаем правую границу
            count +=2;
            r = q - 1;
        }
        else { // ключ поиска больше или равен значения серединного элемента, увеличиваем левую границу
            count += 2;
            p = q + 1;
        }
    }
    cout << "Кол-во сравнений BSearch = " << count << endl;
    return NotFound;
}


void FillRand(int* arr, int length, double min, double max) {
    for (int i = 0; i < length - 1; i++) {
        arr[i] = 10 + ((double)rand() / RAND_MAX) * (max - min);
    }
    arr[length - 1] = INT_MAX;
    Writer(arr, length);
}
void Writer(int* A, int length) {
    for (int i = 0; i < length; i++) {
        cout << "arr[" << i << "] = " << A[i] << endl;
    }
}
void Sort(int* A, int n)
{
    int* B = A;
    for (int i = 0; i < n - 1; ++i)
    {
        int smallest = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (A[j] < A[smallest])
                smallest = j;
        }
        swap(A[i], A[smallest]);
    }
}