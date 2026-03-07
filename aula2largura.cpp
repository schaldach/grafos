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

void enfila(int* queue, int &queue_index, int value){
    queue_index = queue_index+1;
    queue[queue_index] = value;
}

int desenfila(int* queue, int &queue_index ){
    if(queue_index == -1) return -1;
    if(queue_index == 0){
        queue_index = queue_index-1;
        return -1;
    }
    queue_index = queue_index-1;
    
    for(int i=1;i<=queue_index; i++){
        queue[i-1] = queue[i];
    }
    
    return( queue[0] );
}

bool todos_visitados(int* queue_visitada){
    for(int i=0; i<node_size; i++){
        if(queue_visitada[i] == 0) return false;
    }
    return true;
}

int get_primeiro_nao_visitado(int* queue_visitada){
    for(int i=0; i<node_size; i++){
        if(queue_visitada[i] == 0) return i;
    }
    return -1;
}

void pegar_todos_adjacentes(int current_visited, int* visited_values, int* queue, int& queue_index){
    for(int i=0; i<node_size; i++){
        if(adj_matrix[current_visited][i] == 1 && visited_values[i] == 0) enfila(queue, queue_index, i);
    }
}

void print_pilha(int* queue, int queue_index){
    for(int i=0; i<=queue_index; i++){
        cout << queue[i] << " - ";
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

    int queue[node_size];
    int visited_values[node_size];

    for(int i=0; i<node_size; i++){
        visited_values[i] = 0;
    }

    int queue_index = -1;
    int current_visited = get_primeiro_nao_visitado(visited_values);
    enfila(queue, queue_index, current_visited);
    
    while(!todos_visitados(visited_values)){
        cout << current_visited << "\t";
        visited_values[current_visited] = 1;
        
        pegar_todos_adjacentes(current_visited, visited_values, queue, queue_index);
        int proximo_fila = desenfila(queue, queue_index);
        if(proximo_fila == -1){
            current_visited = get_primeiro_nao_visitado(visited_values);
        }
        else{
            current_visited = proximo_fila;
        }
    }

    return 0;
}
