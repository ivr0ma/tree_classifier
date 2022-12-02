#include "Classifier_tree_1.h"

using namespace std;

Classifier_tree_1::Classifier_tree_1() {
    cout << "created" << endl;
    work_tag[0][0] = 3;
    work_tag[0][1] = 4;
    work_tag[1][0] = 3;
    work_tag[1][1] = 4;
    work_tag[2][0] = 0;
    work_tag[2][1] = 3;
//    work_tag[0][0] = 3;
//    work_tag[0][1] = 4;
//    work_tag[1][0] = 4;
//    work_tag[1][1] = 7;
//    work_tag[2][0] = 0;
//    work_tag[2][1] = 3;

    func_coef[0][0] = -88.41;
    func_coef[0][1] = -2.24;
    func_coef[1][0] = 275;
    func_coef[1][1] = 4.5;
    func_coef[2][0] = -86.26;
    func_coef[2][1] = -2.09;
//    func_coef[0][0] = -88.41;
//    func_coef[0][1] = -2.24;
//    func_coef[1][0] = 47.79;
//    func_coef[1][1] = -0.09;
//    func_coef[2][0] = -86.26;
//    func_coef[2][1] = -2.09;

    read_file("train.txt");
}

void Classifier_tree_1::print() {
    for (int i=0; i<3; i++) {
        cout << "node " << i << " features " << work_tag[i][0] << "," << work_tag[i][1] << ": c1=" << func_coef[i][0] << " c2=" << func_coef[i][1] << endl;
    }
    cout << "cl_A:" << endl;
    print_cl(cl_A);
    cout << "cl_B:" << endl;
    print_cl(cl_B);
    cout << "cl_C:" << endl;
    print_cl(cl_C);
    cout << "cl_D:" << endl;
    print_cl(cl_D);
}

void Classifier_tree_1::print_cl(int (*cl)[10]) {
    for (int i=0; i<15; i++) {
        for (int j=0; j<10; j++) {
            cout << cl[i][j] << " ";
        }
        cout << endl;
    }
}

void Classifier_tree_1::read_file(char *file_path) {
    FILE *f = fopen(file_path, "r");
    int a;

    if (f == NULL) {
        cerr << "no such file." << endl;
        return ;
    }
    //cerr << "111" << endl;
    for (int i=0; i<60; i++) {
        for (int j=0; j<10; j++) {
            //cerr << "222" << endl;
            if (fscanf(f, "%d", &a) == 1) {
                if (i < 15) {
                    cl_A[i][j] = a;
                    cl_ABC[i][j] = a;
                    cl_AB[i][j] = a;
                }
                else if (i < 30) {
                    cl_B[i - 15][j] = a;
                    cl_ABC[i][j] = a;
                    cl_AB[i][j] = a;
                }
                else if (i < 45) {
                    cl_C[i - 30][j] = a;
                    cl_ABC[i][j] = a;
                }
                else
                    cl_D[i-45][j] = a;
            }
            else
                cerr << "fscanf error" << endl;
        }
    }
}

double Classifier_tree_1::distance(int node_num, int *x, int *y) {
    int f1,f2;

    f1 = work_tag[node_num][0];
    f2 = work_tag[node_num][1];

    return sqrt((x[f1] - y[f1])*(x[f1] - y[f1]) + (x[f2] - y[f2])*(x[f2] - y[f2]));
}

int Classifier_tree_1::discr_func(int node_num, int *obj) {
    // F = c1 - c2*x2 - x1
    double c1, c2, x1, x2, F;
    c1 = func_coef[node_num][0];
    c2 = func_coef[node_num][1];
    x1 = obj[work_tag[node_num][0]];
    x2 = obj[work_tag[node_num][1]];

    //cout << endl << c1 << " " << c2  << " " << x1 << " " << x2 << endl;

    //F = x1 + c2*x2 - c1;
    F = c1 - c2*x2 - x1;
    //cout << F << endl;

    if (node_num == 0) {
        if (F > 0)
            return 0;
        else
            return 1;
    }
    else if (node_num == 1) {
        if (F > 0)
            return 1;
        else
            return 0;
    }
    else {
        if (F > 0)
            return 0;
        else
            return 1;
    }
}

int Classifier_tree_1::neighbour_1(int node_num, int *obj) {
    double min1, min2;
    double curr;
    int (*M1)[10];
    int (*M2)[10];
    int n1, n2;

    if (node_num == 0) {
        M1 = cl_D;
        M2 = cl_ABC;
        n1 = 15;
        n2 = 45;
    }
    else if (node_num == 1) {
        M1 = cl_C;
        M2 = cl_AB;
        n1 = 15;
        n2 = 30;
    }
    else {
        M1 = cl_A;
        M2 = cl_B;
        n1 = 15;
        n2 = 15;
    }

    min1 = distance(node_num, obj, M1[0]);

    for (int i=1; i<n1; i++) {
        curr = distance(node_num, obj, M1[i]);
        if (curr < min1)
            min1 = curr;
    }

    min2 = distance(node_num, obj, M2[0]);

    for (int i=1; i<n1; i++) {
        curr = distance(node_num, obj, M2[i]);
        if (curr < min2)
            min2 = curr;
    }

    //cout << min1 << " " << min2 << endl;

    if (min1 < min2)
        return 0;
    else
        return 1;
}

int Classifier_tree_1::neighbour_k(int k, int node_num, int *obj) {
    double *min1, *min2;
    double curr;
    int (*M1)[10];
    int (*M2)[10];
    int n1, n2;
    int count;

    if (node_num == 0) {
        M1 = cl_D;
        M2 = cl_ABC;
        n1 = 15;
        n2 = 45;
    }
    else if (node_num == 1) {
        M1 = cl_C;
        M2 = cl_AB;
        n1 = 15;
        n2 = 30;
    }
    else {
        M1 = cl_A;
        M2 = cl_B;
        n1 = 15;
        n2 = 15;
    }

    if (k > n1 || k > n2)
        return -1;

    min1 = new double[k];
    min2 = new double[k];

    for (int j=0; j<k; j++) {
        min1[j] = distance(node_num, obj, M1[j]);
    }

    for (int j=1; j<k; j++) {
        for (int i=0; i<k-1; i++) {
            if (min1[i] > min1[i+1]) {
                curr = min1[i];
                min1[i] = min1[i+1];
                min1[i+1] = curr;
            }
        }
    }

    //cout << "min1= ";
    for (int i=0; i<k; i++) {
        //cout << min1[i] << " ";
    }
    //cout << endl;

    for (int i=k; i<n1; i++) {
        curr = distance(node_num, obj, M1[i]);
        //curr = M1[i][6];
        for (int j=0; j<k; j++) {
            if (curr < min1[j]) {
                for (int r=j; r<k-1; r++) {
                    min1[r+1] = min1[r];
                    min1[r] = curr;
                }
            }
        }
    }

    for (int j=0; j<k; j++) {
        min2[j] = distance(node_num, obj, M2[j]);
    }

    for (int j=1; j<k; j++) {
        for (int i=0; i<k-1; i++) {
            if (min2[i] > min2[i+1]) {
                curr = min2[i];
                min2[i] = min2[i+1];
                min2[i+1] = curr;
            }
        }
    }

    //cout << "min2= ";
    for (int i=0; i<k; i++) {
        //cout << min2[i] << " ";
    }
    //cout << endl;

    for (int i=0; i<n2; i++) {
        curr = distance(node_num, obj, M2[i]);
        //curr = M1[i][6];
        for (int j=0; j<k; j++) {
            if (curr < min2[j]) {
                for (int r=j; r<k-1; r++) {
                    min2[r+1] = min2[r];
                    min2[r] = curr;
                }
            }
        }
    }

    count = 0;
    for (int i=0; i<k; i++) {
        if (min1[i] > min2[i])
            count++;
    }

    //cout << count << " " << k/2 << endl;

    delete[] min1;
    delete[] min2;

    if (count >= k/2)
        return 1;
    else
        return 0;
}

bool Classifier_tree_1::voting(int node_num, int * obj) {
    return discr_func(node_num, obj) + neighbour_1(node_num, obj) + neighbour_k(3, node_num, obj) >= 2;
    //return neighbour_1(node_num, obj) + neighbour_k(3, node_num, obj) >= 1;
    //return neighbour_k(3, node_num, obj) >= 1;
    //return neighbour_1(node_num, obj) >= 1;
    //return discr_func(node_num, obj) >= 1;
}

char Classifier_tree_1::recognize(int *obj) {
    if (not voting(0, obj))
        return 'D';
    else if (not voting(1, obj))
        return 'C';
    else if (not voting(2, obj))
        return 'A';
    else
        return 'B';
}