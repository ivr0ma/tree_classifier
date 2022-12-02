#include <iostream>
#include <processenv.h>
#include "string"
#include "windows.h"
using namespace std;

#include "classifier.h"
#include "Classifier_tree_2.h"
#include "Classifier_tree_1.h"

void read_file(int (*test)[10], const char *file_path) {
    FILE *f = fopen(file_path, "r");
    int a;

    if (f == NULL) {
        cerr << "___no such file." << endl;
        return ;
    }
    //cerr << "111" << endl;
    for (int i=0; i<60; i++) {
        for (int j=0; j<10; j++) {
            //cerr << "222" << endl;
            if (fscanf(f, "%d", &a) == 1) {
                test[i][j] = a;
            }
            else
                cerr << "fscanf error" << endl;
        }
    }
}

int x[2]={0,0};
int y[2]={3,4};

int obj_1[10] = {18, 13, 26, 57, 35, 17, 13, 11, 23, 22}; // A
int obj_2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // D
int obj_3[10] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100}; // D

int main(int argc, char *argv[]) {
    Classifier cl;
    Classifier_tree_2 cl_2;
    Classifier_tree_1 cl_1;

    //cout << cl.recognize(obj_2) << endl;
    int test[60][10];

    read_file(test, "train.txt");

//    for (int i=0; i<60; i++) {
//        for (int j=0; j<10; j++) {
//            cout << test[i][j] << " ";
//        }
//        cout << endl;
//    }

    for (int i=0; i<60; i++) {
        for (int j=0; j<10; j++) {
            cout << test[i][j] << " ";
        }
        cout << cl.recognize(test[i]) << endl;
    }

    return 0;
}