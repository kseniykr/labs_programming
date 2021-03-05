#include <iostream>
#include <malloc.h>
#include <fstream>

using namespace std;

void insertion(double*, int&, int&);
void adding(double*&, int&, int&, int);
void plus_memory(double*&, int&, int&);
void minus_memory(double*&, int&, int&, int);
int deleting(double*&, int&, int&, int);
void clearing(double*&, int&, int&);
void printing(double*, int&, int&);
void n7(double*&, int&, int&, int);
void n8(double*&, int&, int&, int);
int getN(int left, int right);
void menu();

int main()
{
    int n = 3;

    double* arr = (double*)malloc(n * sizeof(double));

    bool first = 0, exit = 0;
    int k;

    do {
        int ch; //choice
        system("cls");

        cout << "\n---Array---\n";

        if (first != 0) {
            printing(arr, n, k);
            cout << endl;
        }
        cout << endl;

        menu();
        cin >> ch;

        switch (ch) {
        case 1: {
            while (k >= n) {
                plus_memory(arr, n, k);
            }
            first = 1;
            adding(arr, n, k, k);

            break;
        }
        case 2: {
            while (k >= n) {
                plus_memory(arr, n, k);
            }
            first = 1;
            adding(arr, n, k, 0);

            break;
        }
        case 3: {
            int pos;
            cout << "Which position?\n";
            pos = getN(0, k);
            first = 1;

            adding(arr, n, k, pos);
            cout << endl;
            break;
        }
        case 4: {
            first = 1;
            deleting(arr, n, k, k);

            break;
        }
        case 5: {
            first = 1;
            deleting(arr, n, k, 0);

            break;
        }
        case 6: {
            cout << "Which element to delete?\n";
            int el;
            el = getN(0, k - 1);
            first = 1;
            deleting(arr, n, k, el);
            cout << endl;
            break;
        }
        case 7: {

            cout << "After which element?";
            int el;
            cin >> el;
            n7(arr, n, k, el);
            first = 1;
            cout << endl;
            break;
        }
        case 8: {
            cout << "Which elements should be deleted? ";
            int el;
            cin >> el;
            n8(arr, n, k, el);

            first = 1;
            cout << endl;
            break;
        }
        case 9: {
            clearing(arr, n, k);

            ifstream fin("input.txt");

            fin >> k;

            fin.close();

            while (k >= n) {
                plus_memory(arr, n, k);
            }

            insertion(arr, n, k);
            cout << endl;
            first = 1;
            break;
        }
        case 10: {
            clearing(arr, n, k);
            first=1;
            break;
        }
        case 0: {
            exit = 1;
            break;
        }

        }

    } while (exit == 0);

    free(arr);
    return 0;
}

int getN(int left, int right) {
    float n;

    do {
        cout << "Insert number from " << left << " to " << right << ":";
        cin >> n;
    } while (n < left || (n - (int)n) != 0 || n > right);
    return n;
}

void insertion(double* arr, int& n, int& k) {
    ifstream fin("input.txt");
    fin >> k;
    while (k >= n) {
        plus_memory(arr, n, k);
    }
    for (int i = 0; i < k; i++) fin >> arr[i];
    fin.close();
}

void adding(double*& arr, int& n, int& k, int pos) {

    k += 1;

    while (k >= n) plus_memory(arr, n, k);

    for (int i = k; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    cout << "Insert new element: ";
    cin >> arr[pos];
}

void plus_memory(double*& arr, int& n, int& k) {
    if (n >= 3) n += n / 3;
    else n += 1;
    double* tmp = NULL;
    tmp = (double*)realloc(arr, n * sizeof(double));
    if (tmp != NULL) {
        arr = tmp;
    }
}

void minus_memory(double*& arr, int& n, int& k, int del) {
    n = n - del;
    double* tmp = NULL;
    tmp = (double*)realloc(arr, n * sizeof(double));
    if (tmp != NULL) {
        arr = tmp;
    }
}

int deleting(double*& arr, int& n, int& k, int element) {
    if (k == NULL || k == 0) return 0;
    for (int i = element; i <= k; i++) {
        arr[i] = arr[i + 1];
    }
    k -= 1;
    minus_memory(arr, n, k, 1);
}

void clearing(double*& arr, int& n, int& k) {
    for (int i = 0; i < n; i++) arr[i] = NULL;
    k = NULL;
    minus_memory(arr, n, k, n - 1);
}

void printing(double* arr, int& n, int& k) {

    for (int i = 0; i < k; i++) cout << arr[i] << " ";

};


void n7(double*& arr, int& n, int& k, int element) {
    int i = 0;
    bool check = 0;
    while (i < k && check == 0) {
        if (arr[i] == element) {
            int pos = i + 1;
            adding(arr, n, k, pos);

            check = 1;
        }

        i++;

    }
    if (check == 0) {
        cout << "Element not found!";
        system("pause");
    }
}

void n8(double*& arr, int& n, int& k, int element) {
    bool check = 0;
    for (int i = 0; i < k; i++) {

        if (arr[i] == element) {
            for (int j = i; i <= k; i++) {
                arr[i] = arr[i + 1];
            }
            k -= 1;
            check = 1;
            minus_memory(arr, n, k, 1);
            i = 0;
        }
    }

    if (check == 0) {
        cout << "Elements not found!";
        system("pause");
    }
}

void menu() {
    cout << "    MENU\n";
    cout << "1. Add element to the end\n";
    cout << "2. Add element to the beginning\n";
    cout << "3. Add element on k position\n";
    cout << "4. Delete last element\n";
    cout << "5. Delete first element\n";
    cout << "6. Delete element on k position\n";
    cout << "7. Number 7\n";
    cout << "8. Number 8\n";
    cout << "9. Insert\n";
    cout << "10. Clear array\n";
    cout << "0. Close\n";
}
