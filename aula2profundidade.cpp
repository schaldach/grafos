/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;

#define node_size 9

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

// {0,4}{4,0}{0,5}{5,0}{0,6}{6,0}{0,8}{8,0}{4,5}{5,4}{4,8}{8,4}{5,8}{8,5}{6,1}{1,6}{2,7}{7,2}{7,3}{3,7}

int adj_matrix[node_size][node_size];

void empilha(int* stack, int &stack_index, int value){
    stack_index = stack_index+1;
    stack[stack_index] = value;
}

int desempilha(int* stack, int &stack_index ){
    if(stack_index == -1) return -1;
    if(stack_index == 0){
        stack_index = stack_index-1;
        return -1;
    }
    stack_index = stack_index-1;
    return( stack[stack_index] );
}

bool todos_visitados(int* stack_visitada){
    for(int i=0; i<node_size; i++){
        if(stack_visitada[i] == 0) return false;
    }
    return true;
}

int get_primeiro_nao_visitado(int* stack_visitada){
    for(int i=0; i<node_size; i++){
        if(stack_visitada[i] == 0) return i;
    }
    return -1;
}

int get_primeiro_adjacente(int row_index, int* visited_values){
    for(int i=0; i<node_size; i++){
        if(adj_matrix[row_index][i] == 1 && visited_values[i] == 0) return i;
    }
    return -1;
}

void print_pilha(int* stack, int stack_index){
    for(int i=0; i<=stack_index; i++){
        cout << stack[i] << " - ";
    }
    cout << "\n";
}

int main()
{
    std::cout<<"Hello World";
    string input_graphs;
    
    cout << "Digite as conexões dos grafos:\n";
    cin >> input_graphs;
    
    for(int i=0; i<node_size; i++){
        for(int j=0; j<node_size; j++){
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
    
    cout << "\n";
    for(int i=0; i<node_size; i++){
        for(int j=0; j<node_size; j++){
            if(adj_matrix[i][j] == 0){
                cout << RED;
            }
            else{
                cout << GREEN;
            }
            cout << adj_matrix[i][j] << RESET << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    int stack[node_size];
    int visited_values[node_size];

    for(int i=0; i<node_size; i++){
        visited_values[i] = 0;
    }

    int stack_index = -1;
    int current_visited = get_primeiro_nao_visitado(visited_values);
    empilha(stack, stack_index, current_visited);
    
    while(!todos_visitados(visited_values)){
        int next_node = get_primeiro_adjacente(current_visited, visited_values);

        if(next_node != -1){
            if(visited_values[current_visited] == 0){
                cout << current_visited << "\t";
            }
            visited_values[current_visited] = 1;
            current_visited = next_node;
            empilha(stack, stack_index, current_visited);
        }
        else{
            if(visited_values[current_visited] == 0){
                cout << current_visited << "\t";
            }
            visited_values[current_visited] = 1;
            current_visited = desempilha(stack, stack_index);
            if(current_visited == -1){
                current_visited = get_primeiro_nao_visitado(visited_values);
            }
        }
    }

    return 0;
}
