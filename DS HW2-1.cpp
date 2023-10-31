#include<iostream>
#include<string>

using namespace std;

int find_max(int* array, int x){
    int max = -1;
    for(int i = 0 ; i < x ; i++){
        if(*(array + i) > max){
            max = *(array + i);
        }
    }
    return max;
}


int main() {
    int x, y;
    cout<<"Enter value of x(how many names?): ";
    cin>>x;
    cout<<"Enter value of y(max length of names): ";
    cin>>y;

    //initializing
    char **names = new char* [x];
    
    int* space_position = new int; 

    //finalizing
    for (int i = 0; i < x; i++) {
        *(names + i) = new char[y + 1];
        cout<<"Enter name "<<i + 1<<":\n";

        cin.ignore();
        cin.get(*(names + i), y + 1);
        
        for(int j = 0 ; j < y - 1 ; j++){
            if(*(*(names + i) + j) == ' '){
                *(space_position + i) = j;
            }
        }
    }
    
    int max_space = find_max(space_position, x);

    cout<<"\nNames:"<<endl;
    for (int i = 0; i < x; i++) {
        for(int j = 0 ; j < max_space - space_position[i] ; j++){
            cout<<' ';
        }
        cout<<*(names + i)<<endl;
    }
    
    // Free allocated memory
    for (int i = 0; i < x; i++) {
        delete[] names[i];
    }
    delete[] names;
    return 0;
}