// Лабораторная работа №2 
// Выполнили студенты группы м3о-219Бк-20 Бокарев, Катвалян

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<chrono> // подключение библиотеки для вычисления времени работы алгоритмов 

#define NotFound -1;

using namespace std;

void FillRand(int* arr, int n, double min, double max); // Функция, формирующая рандомную последовательность
void FillGrow(int* arr, int length, int min, int max); // Функция, формирующая возрастающую последовательность
void Writer(int* A, int length); // Функция, печатающая последовательность
int QSearch(int* A, int x, int n); // Функция быстрого последовательного поиска в лекциях Sentinel_Linear_Search 
int SSearch(int* A, int x, int n); // Функция последовательного поиска в лекциях Better_Linear_Search
int TSearch(int* A, int x, int n); // Функция последовательного поиска в упорядоченном массиве
int BSearch(int* A, int x, int n); // Функция бинарного поиска

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int n = 0;
    cout << "Введите размер последовательности: "; cin >> n;
    int length = n += 1;
    
    cout << "Рандомная последовательность" << endl;
    int* arrRand = new int[length]; // рандомная последовательность
    FillRand(arrRand, n, 0, 50);
    //int keyRand; cout << "Введите ключ поиска в рандомной последовательности: "; cin >> keyRand;

    int* arrGrow = new int[length];
    cout << "Возрастающая последовательность" << endl;
    FillGrow(arrGrow, length, 0, length); // заполняем массив возрастающей последовательностью 
    //int keyGrow; cout << "Введите ключ поиска в возрастающей последовательности: "; cin >> keyGrow;
    
    
    int (*SearchOperations[4])(int*, int, int) = { QSearch, SSearch, TSearch, BSearch }; // Указатель на массив функций
    
    int lengthLin = sizeof(SearchOperations) / sizeof(SearchOperations[0]);// получаем длину массива

    for (int i = 0; i < lengthLin - 2; i++) // цикл по рандомной последовательности
    {
        for (int j = 0; j < 3; j++) {
            int key = 0;
            if (j == 0) key = arrRand[0]; // ключ поиска
            else if (j == 1) key = arrRand[length / 2]; // ключ поиска
            else if (j == 2) key = arrRand[length - 1]; // ключ поиска*/
            auto begin = chrono::steady_clock::now(); // получаем время перед началом формирования последовательности
            cout << "Процедура " << i << " ключ поиска : " << key << endl;
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

    for (int i = 2; i < lengthLin; i++) // цикл по возрастающей последовательности
    {
        for (int j = 0; j < 3; j++) {
            int key = 0;
            if (j == 0) key = arrGrow[0]; // ключ поиска
            else if (j == 1) key = arrGrow[length / 2]; // ключ поиска
            else if (j == 2) key = arrGrow[length - 1]; // ключ поиска*/
            auto begin = chrono::steady_clock::now(); // получаем время перед началом формирования последовательности
            cout << "Процедура " << i << " ключ поиска : " << key << endl;
            int result = SearchOperations[i](&arrGrow[0], key, length);    // вызов функции по указателю
                
          
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
int SSearch(int* arr, int key, int size) {
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        count++;
        if (arr[i] == key) {
            cout << "Количество операций сравнения для SSearch " << count << endl;
            return i;
        }
        if (arr[i] == arr[size - 1]) {
            cout << "Количество операций сравнения для SSearch " << count << endl;
            return NotFound;
        }
    }

}
int QSearch(int* arr, int key, int size) {
    int i = 0;
    int count = 0;
    int last = arr[size];
    arr[size] = key;
    for (i; arr[i] != key; i++) {
        count++;
    }
    arr[size] = last;
    if (i < size) {
        cout << "Кол-во сравнений QSearch = " << count << endl;
        return i;
    }
    else if (arr[size] == key) { 
        count++;
        cout << "Кол-во сравнений QSearch = " << count << endl;
        return i; 
    }
    else { 
        cout << "Кол-во сравнений QSearch = " << count << endl; 
        return NotFound; 
    }
    
}
int TSearch(int* arr, int key, int size) {
    int i = 0;
    int count = 0;
    while (key > arr[i]) {
        i++;
        count++;
    }
    cout << "Кол-во сравнений TSearch = " << count << endl;
    if (key == arr[i]) return i;
    else return NotFound; 
}
int BSearch(int* arr, int key, int size) {
    int count = 0;
    int p = 0; //Первый элемент массива
    int r = size - 1;
    while (p <= r) {
        int q = (p + r) / 2;
        if (arr[q] == key) {
            count++;
            cout << "Кол-во сравнений BSearch = " << count << endl;
            return  q;
        }
        else if (arr[q] > key) {
            count++;
            r = q - 1;
        }
        else {
            count++;
            p = q + 1;
        }
    }

    return NotFound;
}

void FillGrow(int* arr, int length, int min, int max) {
    max--;
    int step = 1 + (max - min) / length;

    for (int i = 0; i < length - 1; i++) {
        arr[i] = min + step * i;
    }
    //arr[min + rand() % (max - min + 1)] = arr[min + rand() % (max - min + 1)]; // повторяющийся элемент
    arr[length - 1] = INT_MAX;
    Writer(arr, length);
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
