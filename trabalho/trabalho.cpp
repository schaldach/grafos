#include <iostream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

// {0,1,2,3,4,5,6,7,8}{0,4}{4,0}{0,5}{5,0}{0,6}{6,0}{0,8}{8,0}{4,5}{5,4}{4,8}{8,4}{5,8}{8,5}{6,1}{1,6}{2,7}{7,2}{7,3}{3,7}

struct queue{
    int top_index;
    int* queue_elements;

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

    void init(int node_size){
        top_index = 0;
        queue_elements = new int[node_size];
    }

    void delete_ptr(){
        delete[] queue_elements;
    }
};

struct stack{
    int top_index;
    int* stack_elements;

    int get_top(){
        if(top_index == 0) return -1;
        return stack_elements[top_index-1];
    }

    void empilha(int value){
        stack_elements[top_index] = value;
        top_index = top_index + 1;
    }

    void desempilha(){
        if(top_index>0) top_index = top_index - 1;
    }

    void init(int node_size){
        top_index = 0;
        stack_elements = new int[node_size];
    }

    void delete_ptr(){
        delete[] stack_elements;
    }
};

int get_primeiro_adjacente(int row_index, int* visited_values, int** adj_matrix, int node_size){
    for(int i=0; i<node_size; i++){
        if(adj_matrix[row_index][i] == 1 && visited_values[i] == 0) return i;
    }
    return -1;
}

bool todos_visitados(int* lista_visitada, int node_size){
    for(int i=0; i<node_size; i++){
        if(lista_visitada[i] == 0) return false;
    }
    return true;
}

int get_primeiro_nao_visitado(int* lista_visitada, int node_size){
    for(int i=0; i<node_size; i++){
        if(lista_visitada[i] == 0) return i;
    }
    return -1;
}

void pegar_todos_adjacentes(int current_visited, int* visited_values, queue& queue, int** adj_matrix, int node_size){
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
    string input_graphs;
    int orientado = 0;

    cout << "Digite 1 para um grafo orientado (arcos), e 0 para um grafo não orientado (arestas): ";
    cin >> orientado;
    
    // exemplo: 
    cout << "Digite as conexões dos grafos: (primeiro todos os vértices presentes, depois as conexões)\nExemplo: {0,1,2,3,4}{0,4}{4,0}{4,3}{3,4}{2,1}{1,2}{0,3}{3,0}\n";
    cin >> input_graphs;

    int node_size = 1;
    int first_string_adj_position = 0;
    for(int i=0; i<input_graphs.length(); i++){
        if(input_graphs[i] == '}'){
            first_string_adj_position = i;
            break;
        }
        if(input_graphs[i] == ',') node_size = node_size + 1;
    }

    int** adj_matrix = new int*[node_size];
    
    for(int i=0; i<node_size; i++){
        adj_matrix[i] = new int[node_size];
        for(int j=0; j<node_size; j++){
            adj_matrix[i][j] = 0;
        }
    }
    
    int first_index = -1;
    for(int i=first_string_adj_position; i<input_graphs.length(); i++){
        if(input_graphs[i] == ',' || input_graphs[i] == '{' || input_graphs[i] == '}') continue;
        
        int current_number = input_graphs[i] - '0';
        if(first_index == -1){
            first_index = current_number;
        }
        else{
            adj_matrix[first_index][current_number] = 1;
            if(orientado == 0){
                adj_matrix[current_number][first_index] = 1;
            }
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

    int input = 1;
    while(input != 0){
        cout << "\nDigite 1 para percorrer por profundidade;\nDigite 2 para percorrer por largura;\nDigite 3 para procurar um vértice;\nDigite 4 para adicionar um vértice;\nDigite 5 para remover um vértice;\nDigite 6 para adicionar um arco/aresta;\nDigite 7 para remover um arco/aresta;\nDigite 0 para sair do programa: \n";
        cin >> input;

        // DFS
        if(input == 1){
            stack stack_alg;
            stack_alg.init(node_size);
            int visited_values[node_size];

            for(int i=0; i<node_size; i++){
                visited_values[i] = 0;
            }

            int current_visited = get_primeiro_nao_visitado(visited_values, node_size);
            stack_alg.empilha(current_visited);
            
            while(!todos_visitados(visited_values, node_size)){
                int next_node = get_primeiro_adjacente(current_visited, visited_values, adj_matrix, node_size);

                if(next_node != -1){
                    if(visited_values[current_visited] == 0){
                        cout << current_visited << "\t";
                    }
                    visited_values[current_visited] = 1;
                    current_visited = next_node;
                    stack_alg.empilha(current_visited);
                }
                else{
                    if(visited_values[current_visited] == 0){
                        cout << current_visited << "\t";
                    }
                    visited_values[current_visited] = 1;
                    stack_alg.desempilha();
                    current_visited = stack_alg.get_top();
                    if(current_visited == -1){
                        current_visited = get_primeiro_nao_visitado(visited_values, node_size);
                    }
                }
            }

            stack_alg.delete_ptr();
        }

        // BFS 
        else if(input == 2){
            queue queue;
            queue.init(node_size);
            int visited_values[node_size];

            for(int i=0; i<node_size; i++){
                visited_values[i] = 0;
            }

            int current_visited = get_primeiro_nao_visitado(visited_values, node_size);
            
            while(!todos_visitados(visited_values, node_size)){
                if(visited_values[current_visited] == 0){
                    cout << current_visited << "\t";
                    visited_values[current_visited] = 1;
                }    
                
                pegar_todos_adjacentes(current_visited, visited_values, queue, adj_matrix, node_size);
                int proximo_fila = queue.get_first();
                queue.desenfila();
                if(proximo_fila == -1){
                    current_visited = get_primeiro_nao_visitado(visited_values, node_size);
                }
                else{
                    current_visited = proximo_fila;
                }
            }

            queue.delete_ptr();
        }

        // Busca por vértice
        else if(input == 3){
            int target_input;
            cout << "Digite o vértice a ser encontrado: ";
            cin >> target_input;

            stack stack_alg;
            stack_alg.init(node_size);
            int visited_values[node_size];

            for(int i=0; i<node_size; i++){
                visited_values[i] = 0;
            }

            int current_visited = get_primeiro_nao_visitado(visited_values, node_size);
            stack_alg.empilha(current_visited);
            
            while(!todos_visitados(visited_values, node_size)){
                int next_node = get_primeiro_adjacente(current_visited, visited_values, adj_matrix, node_size);

                if(next_node != -1){
                    // if(visited_values[current_visited] == 0){
                    //     cout << current_visited << "\t";
                    // }
                    visited_values[current_visited] = 1;
                    current_visited = next_node;
                    stack_alg.empilha(current_visited);
                }
                else{
                    // if(visited_values[current_visited] == 0){
                    //     cout << current_visited << "\t";
                    // }
                    visited_values[current_visited] = 1;
                    stack_alg.desempilha();
                    current_visited = stack_alg.get_top();
                    if(current_visited == -1){
                        current_visited = get_primeiro_nao_visitado(visited_values, node_size);
                    }
                }
            }

            if(target_input >= 0 && (target_input < node_size && visited_values[target_input])){
                cout << "\nO vértice foi encontrado\n";
            }
            else{
                cout << "\nO vértice não foi encontrado\n";
            }

            stack_alg.delete_ptr();
        }

        // Adicionar vértice
        else if(input == 4){
            int new_node_size = node_size + 1;
            int** new_adj_matrix = new int*[new_node_size];
    
            for(int i=0; i<new_node_size; i++){
                new_adj_matrix[i] = new int[new_node_size];
                for(int j=0; j<new_node_size; j++){
                    new_adj_matrix[i][j] = 0;
                }
            }
            // Copiando matriz antiga
            for(int i=0; i<node_size; i++){
                for(int j=0; j<node_size; j++){
                    new_adj_matrix[i][j] = adj_matrix[i][j];
                }
            }

            // Deletando matriz antiga
            for(int i=0; i<node_size; i++){
                delete[] adj_matrix[i];
            }
            delete[] adj_matrix;

            node_size = new_node_size;
            adj_matrix = new_adj_matrix;

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
        }

        // Remover vértice
        else if(input == 5 && node_size - 1 > 0){
            int new_node_size = node_size - 1;
            int** new_adj_matrix = new int*[new_node_size];
    
            for(int i=0; i<new_node_size; i++){
                new_adj_matrix[i] = new int[new_node_size];
                for(int j=0; j<new_node_size; j++){
                    new_adj_matrix[i][j] = 0;
                }
            }
            // Copiando matriz antiga
            for(int i=0; i<new_node_size; i++){
                for(int j=0; j<new_node_size; j++){
                    new_adj_matrix[i][j] = adj_matrix[i][j];
                }
            }

            // Deletando matriz antiga
            for(int i=0; i<node_size; i++){
                delete[] adj_matrix[i];
            }
            delete[] adj_matrix;

            node_size = new_node_size;
            adj_matrix = new_adj_matrix;

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
        }

        // Adicionar arco/aresta
        else if(input == 6){

        }

        // Remover arco/aresta
        else if(input == 7){

        }
    }
}
