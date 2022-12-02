#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <iostream>
#include <math.h>
#include <stdio.h>

class Classifier {
private:
    int work_tag[3][2];     // массив признаков
    double func_coef[3][2]; // массив коэф-от для дискриминантной функции

    int cl_A[15][10];  // класс A
    int cl_B[15][10];  // класс B
    int cl_C[15][10];  // класс C
    int cl_D[15][10];  // класс D
    int cl_AC[30][10]; // класс AC
    int cl_BD[30][10]; // класс BD
public:
    Classifier(); // конструктор класса, осуществляет начальную инициализацию

    void read_file(); // считываем объекты классов A,B,C,D из файла
    double distance(int node_num, int* x, int* y); // считает расстояние между объектами класса
    int discr_func(int node_num, int* obj); // реализация дискриминантной функции
    int neighbour_1(int node_num, int* obj); // реализация метода 1-го ближайшего соседа
    int neighbour_k(int k, int node_num, int* obj); // реализация метода k ближайших соседей
    char recognize(int* obj); // классификация объекта
    bool voting(int node_num, int* obj); // функция голосования
};

#endif //CLASSIFIER_H
