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

struct queue{
    int top_index;
    int queue_elements[node_size];

    int get_first(){
        if(top_index == 0) return -1;
        return queue_elements[0];
    }

    void enfila(int value){
        queue_elements[top_index] = value;
        top_index = top_index + 1;
    }

    void desenfila(){
        if(top_index>0){
            for(int i=0;i<top_index-1; i++){
                queue_elements[i] = queue_elements[i+1];
            }
            top_index = top_index - 1;
        }
    }

    void print_queue(){
        cout << "\n";
        for(int i=0;i<top_index;i++){
            cout << queue_elements[i] << " ";
        }
        cout << "\n";
    }

    void init(){
        top_index = 0;
    }
};

bool todos_visitados(int* lista_visitada){
    for(int i=0; i<node_size; i++){
        if(lista_visitada[i] == 0) return false;
    }
    return true;
}

int get_primeiro_nao_visitado(int* lista_visitada){
    for(int i=0; i<node_size; i++){
        if(lista_visitada[i] == 0) return i;
    }
    return -1;
}

void pegar_todos_adjacentes(int current_visited, int* visited_values, queue& queue){
    for(int i=0; i<node_size; i++){
        if(adj_matrix[current_visited][i] == 1 && visited_values[i] == 0){
            queue.enfila(i);
            visited_values[i] = 1;
            cout << i << "\t";
        }
    }
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

    queue queue;
    queue.init();
    int visited_values[node_size];

    for(int i=0; i<node_size; i++){
        visited_values[i] = 0;
    }

    int current_visited = get_primeiro_nao_visitado(visited_values);
    
    while(!todos_visitados(visited_values)){
        if(visited_values[current_visited] == 0){
            cout << current_visited << "\t";
            visited_values[current_visited] = 1;
        }    
        
        pegar_todos_adjacentes(current_visited, visited_values, queue);
        int proximo_fila = queue.get_first();
        queue.desenfila();
        if(proximo_fila == -1){
            current_visited = get_primeiro_nao_visitado(visited_values);
        }
        else{
            current_visited = proximo_fila;
        }
    }

    return 0;
}
