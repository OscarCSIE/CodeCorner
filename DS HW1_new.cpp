#include<iostream>
#include<cstring>

using namespace std;

void bubbleSort(char **arr, int x, int y) {
    for (int i = 0; i < x - 1; i++) {
        for (int j = 0; j < x - i - 1; j++) {
            if (strncmp(*(arr + j), *(arr + (j + 1)), y) < 0) {// strcmp return 0 if equal and > 0 if left > right
                char* temp = *(arr + j);
                *(arr + j) = *(arr + (j + 1));
                *(arr + (j + 1)) = temp;
            }
        }
    }
}

int main() {
    int x, y;

    cout << "Enter the value of x(up down): ";
    cin >> x;

    cout << "Enter the value of y(left right): ";
    cin >> y;

    //first part of 2d array
    char **list_new = new char* [x];

    //finalizing array
    for (int i = 0; i < x; i++) {
        *(list_new + i) = new char[y + 1];
        cout << "Enter string " << i + 1 << ": \n";
        cin.ignore();
        cin.get(*(list_new + i), y + 1);
    }

    bubbleSort(list_new, x, y);
        
    cout << "Sorted Strings for list_new(descending order by ASCII code):" <<  endl;
    for (int i = 0; i < x; i++) {
        cout << *(list_new + i) <<  endl;
    }
    // Free allocated memory
    for (int i = 0; i < x; i++) {
        delete[] *(list_new + i);
    }
    delete[] list_new;
    return 0;
}