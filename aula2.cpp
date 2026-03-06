/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;

#define node_size 9
#define matrix_size node_size-1

int main()
{
    std::cout<<"Hello World";
    string input_graphs;
    
    int adj_matrix[matrix_size][matrix_size];
    
    cout << "Digite as conexões dos grafos:\n";
    cin >> input_graphs;
    
    for(int i=0; i<matrix_size; i++){
        for(int j=0; j<matrix_size; j++){
            adj_matrix[i][j] = 0;
        }
    }
    
    int first_index = -1;
    for(int i=0; i<input_graphs.length(); i++){
        if(input_graphs[i] == ',' || input_graphs[i] == '{' || input_graphs[i] == '}') continue;
        
        int current_number = input_graphs[i] - '0';
        if(first_index == -1){
            first_index = current_number;
        }
        else{
            adj_matrix[first_index][current_number] = 1;
            first_index = -1;
        }
    }
    
    for(int i=0; i<matrix_size; i++){
        for(int j=0; j<matrix_size; j++){
            cout << adj_matrix[i][j] << " ";
        }
        cout << "\n";
    }

    int stack[node_size];
    int stack_index = 0;
    
    

    return 0;
}
