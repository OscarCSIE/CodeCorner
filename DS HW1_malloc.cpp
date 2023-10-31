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
    
    char **list_malloc = (char **) malloc(x * sizeof(char *));

    for(int i = 0; i < x; i++) {
        *(list_malloc + i) = (char *) malloc((y + 1) * sizeof(char));
        cout << "Enter string " << i + 1 << ": ";
        cin.ignore();
        cin.get(*(list_malloc + i), y + 1);
    }

    bubbleSort(list_malloc, x, y);

    cout << "Sorted Strings for list_malloc(descending order by ASCII code):" << endl;
    for (int i = 0; i < x; i++) {
        cout << *(list_malloc + i) << endl;
    }

    for (int i = 0; i < x; i++) {
        free(*(list_malloc + i));
    }
    free(list_malloc);
    return 0;
}