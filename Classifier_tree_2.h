#ifndef CLASSIFIER_TREE_2_H
#define CLASSIFIER_TREE_2_H


#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

class Classifier_tree_2 {
private:
    int work_tag[3][2];
    double func_coef[3][2];
    int cl_AC[30][10];
    int cl_BD[30][10];
public:
    int cl_A[15][10];
    int cl_B[15][10];
    int cl_C[15][10];
    int cl_D[15][10];

    Classifier_tree_2();

    void print();
    void print_cl(int (*cl)[10]);
    void read_file(char * file_path);
    double distance(int node_num, int *x, int *y);
    int discr_func(int node_num, int * obj);
    int neighbour_1(int node_num, int * obj);
    int neighbour_k(int k, int node_num, int *obj);
    char recognize(int *obj);
    bool voting(int node_num, int * obj);
};


#endif //CLASSIFIER_TREE_2_H
