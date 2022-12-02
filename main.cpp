#include <iostream>
#include "string"
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

int obj[10];
int a;

int main(int argc, char *argv[]) {
    Classifier cl;
    Classifier_tree_2 cl_2;
    Classifier_tree_1 cl_1;

    int test[20][10];

    //read_file(test, "test.txt");
    //
    //for (int i=0; i<20; i++) {
    //    for (int j=0; j<10; j++) {
    //        cout << test[i][j] << " ";
    //    }
    //    cout << cl_1.recognize(test[i]) << endl;
    //}

    cout << "Enter the characteristics of the object" << endl;

    for (int i=0; i<10; i++) {
        a = 0;
        cout << "feature " << i+1 << ": ";
        try {
            cin >> a;
        }
        catch(...) {
            cerr << "incorrect format" << endl;
        }
        obj[i] = a;
    }

    cout << endl << "Your object: ";
    for (int i=0; i<10; i++) {
        cout << obj[i] << " ";
    }
    cout << endl;

    cout << "object class by tree 1: " << cl_1.recognize(obj) << endl;
    cout << "object class by tree 2: " << cl.recognize(obj) << endl;

    return 0;
}