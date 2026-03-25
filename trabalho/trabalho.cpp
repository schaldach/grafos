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

void print_matrix(int node_size, int** adj_matrix){
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

int get_next_of_level(bool* are_visited_values, int* visited_levels, int level, int node_size){
    for(int i=0; i<node_size; i++){
        if(!are_visited_values[i] && visited_levels[i] == level){
            return i;
        }
    }
    return -1;
}

int get_next_explorar(bool* vertices_explorados, int node_size){
    for(int i=0; i<node_size; i++){
        if(!vertices_explorados[i]) return i;
    }
    return -1;
}

int get_valid_values(int* levels, int node_size){
    int i=0;
    for(int y=0;y<node_size; y++){
        if(levels[y] != -1) i = i+1;
    }
    return i;
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
    
    print_matrix(node_size, adj_matrix);

    int input = 1;
    while(input != 0){
        string orientado_str = orientado ? "Grafo Orientado" : "Grafo Não Orientado";
        cout << "\nDigite 1 para percorrer por profundidade;\nDigite 2 para percorrer por largura;\nDigite 3 para procurar um vértice;\nDigite 4 para adicionar um vértice;\nDigite 5 para remover um vértice;\nDigite 6 para adicionar um arco/aresta;\nDigite 7 para remover um arco/aresta;\nDigite 8 para mudar a orientação (atual: " + orientado_str + ");\nDigite 9 para visualizar a matriz;\nDigite 10 para visualizar o fecho transitivo direto de um vértice;\nDigite 11 para visualizar o fecho transitivo inverso de um vértice;\nDigite 12 para saber se o grafo é conexo ou não, e ver os subgrafos conexos máximos\nDigite 0 para sair do programa: \n";
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

            print_matrix(node_size, adj_matrix);
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

            print_matrix(node_size, adj_matrix);
        }

        // Adicionar arco/aresta
        else if(input == 6){
            string target_input;
            cout << "Digite os arcos/arestas a serem adicionados (mesmo formato de inserção):\nExemplo: {0,4}{1,2}\n";
            cin >> target_input;

            int first_index = -1;
            for(int i=0; i<target_input.length(); i++){
                if(target_input[i] == ',' || target_input[i] == '{' || target_input[i] == '}') continue;
                
                int current_number = target_input[i] - '0';
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

            print_matrix(node_size, adj_matrix);
        }

        // Remover arco/aresta
        else if(input == 7){
            string target_input;
            cout << "Digite os arcos/arestas a serem removidos (mesmo formato de inserção):\nExemplo: {0,4}{1,2}\n";
            cin >> target_input;

            int first_index = -1;
            for(int i=0; i<target_input.length(); i++){
                if(target_input[i] == ',' || target_input[i] == '{' || target_input[i] == '}') continue;
                
                int current_number = target_input[i] - '0';
                if(first_index == -1){
                    first_index = current_number;
                }
                else{
                    adj_matrix[first_index][current_number] = 0;
                    if(orientado == 0){
                        adj_matrix[current_number][first_index] = 0;
                    }
                    first_index = -1;
                }
            }

            print_matrix(node_size, adj_matrix);
        }

        // Mudar simetria
        else if(input == 8){
            if(orientado == 0) orientado = 1;
            else orientado = 0;
        }

        // Visualizar matriz
        else if(input == 9){
            print_matrix(node_size, adj_matrix);
        }

        // Fecho transitivo direto
        else if(input == 10){
            int target_input;
            cout << "Digite o vértice a ser mostrado o fecho transitivo direto: ";
            cin >> target_input;

            if(target_input>=node_size || target_input < 0){
                cout << "\nVértice não existente;\n";
            }
            else{
                int visited_levels[node_size];
                bool are_visited_values[node_size];
                for(int i=0; i<node_size; i++){
                    visited_levels[i] = -1;
                    are_visited_values[i] = false;
                }
                visited_levels[target_input] = 0;

                int current_level = 0;
                int current_target = target_input;

                while(current_target>=0){
                    are_visited_values[current_target] = true;

                    for(int i=0; i<node_size; i++){
                        // o are_visited_values é apenas para achar o próximo a ser procurado,
                        // mas para marcar o nível, temos que ver antes, se o valor dele já está marcado no levels ou não
                        // (senão ele iria aumentar o nível precipitadamente, sem ter "visitado" os nodos)
                        if(adj_matrix[current_target][i] == 1 && visited_levels[i] == -1){
                            visited_levels[i] = current_level+1;
                        }
                    }

                    current_target = get_next_of_level(are_visited_values, visited_levels, current_level, node_size);
                    if(current_target == -1){
                        current_level = current_level+1;
                        current_target = get_next_of_level(are_visited_values, visited_levels, current_level, node_size);
                    }
                }

                for(int i=0; i<node_size; i++){
                    cout << i << "\t";
                }
                cout << "\n";
                for(int i=0; i<node_size; i++){
                    cout << visited_levels[i] << "\t";
                }
            }
        }

        // Fecho transitivo inverso
        else if(input == 11){
            int target_input;
            cout << "Digite o vértice a ser mostrado o fecho transitivo inverso: ";
            cin >> target_input;

            if(target_input>=node_size || target_input < 0){
                cout << "\nVértice não existente;\n";
            }
            else{
                int visited_levels[node_size];
                bool are_visited_values[node_size];
                for(int i=0; i<node_size; i++){
                    visited_levels[i] = -1;
                    are_visited_values[i] = false;
                }
                visited_levels[target_input] = 0;

                int current_level = 0;
                int current_target = target_input;

                while(current_target>=0){
                    are_visited_values[current_target] = true;

                    for(int i=0; i<node_size; i++){
                        // o are_visited_values é apenas para achar o próximo a ser procurado,
                        // mas para marcar o nível, temos que ver antes, se o valor dele já está marcado no levels ou não
                        // (senão ele iria aumentar o nível precipitadamente, sem ter "visitado" os nodos)
                        if(adj_matrix[i][current_target] == 1 && visited_levels[i] == -1){
                            visited_levels[i] = current_level+1;
                        }
                    }

                    current_target = get_next_of_level(are_visited_values, visited_levels, current_level, node_size);
                    if(current_target == -1){
                        current_level = current_level+1;
                        current_target = get_next_of_level(are_visited_values, visited_levels, current_level, node_size);
                    }
                }

                for(int i=0; i<node_size; i++){
                    cout << i << "\t";
                }
                cout << "\n";
                for(int i=0; i<node_size; i++){
                    cout << visited_levels[i] << "\t";
                }
            }
        }

        // Conexo, ou subgrafos fortemente conexos máximos
        else if(input == 12){
            bool vertices_explorados[node_size];
             for(int i=0; i<node_size; i++){
                vertices_explorados[i] = false;
            }

            int vertice_origem = get_next_explorar(vertices_explorados, node_size);
            bool first_iteration = true;
            bool is_conexo = false;

            while(vertice_origem != -1){

                // fecho transitivo inverso
                int visited_levels_inverso[node_size];
                bool are_visited_values[node_size];
                for(int i=0; i<node_size; i++){
                    visited_levels_inverso[i] = -1;
                    are_visited_values[i] = false;
                }
                visited_levels_inverso[vertice_origem] = 0;

                int current_level = 0;
                int current_target = vertice_origem;

                while(current_target>=0){
                    are_visited_values[current_target] = true;

                    for(int i=0; i<node_size; i++){
                        if(adj_matrix[i][current_target] == 1 && visited_levels_inverso[i] == -1){
                            visited_levels_inverso[i] = current_level+1;
                        }
                    }

                    current_target = get_next_of_level(are_visited_values, visited_levels_inverso, current_level, node_size);
                    if(current_target == -1){
                        current_level = current_level+1;
                        current_target = get_next_of_level(are_visited_values, visited_levels_inverso, current_level, node_size);
                    }
                }

                // fecho transitivo direto
                int visited_levels[node_size];
                for(int i=0; i<node_size; i++){
                    visited_levels[i] = -1;
                    are_visited_values[i] = false;
                }
                visited_levels[vertice_origem] = 0;

                current_level = 0;
                current_target = vertice_origem;

                while(current_target>=0){
                    are_visited_values[current_target] = true;

                    for(int i=0; i<node_size; i++){
                        if(adj_matrix[current_target][i] == 1 && visited_levels[i] == -1){
                            visited_levels[i] = current_level+1;
                        }
                    }

                    current_target = get_next_of_level(are_visited_values, visited_levels, current_level, node_size);
                    if(current_target == -1){
                        current_level = current_level+1;
                        current_target = get_next_of_level(are_visited_values, visited_levels, current_level, node_size);
                    }
                }

                if(first_iteration){
                    if(get_valid_values(visited_levels, node_size) == get_valid_values(visited_levels_inverso, node_size) && get_valid_values(visited_levels, node_size) == node_size){
                        cout << "É conexo\n";
                        is_conexo = true;
                    }
                    else{
                        cout << "Não é conexo\n";
                    }
                    first_iteration = false;
                }

                // fazer intersecção (no array visited_levels)
                for(int i=0; i<node_size; i++){
                    if(visited_levels[i] != -1 && visited_levels_inverso[i] != -1){
                        visited_levels[i] = 1;
                        vertices_explorados[i] = true;
                    }
                    else{
                        visited_levels[i] = 0;
                    }
                }

                if(is_conexo) cout << "Grafo fortemente conexo: ";
                else cout << "Subgrafo fortemente conexo máximo: ";
                for(int i=0; i<node_size; i++){
                    if(visited_levels[i] == 1) cout << i << "\t";
                }
                cout << "\n";

                vertice_origem = get_next_explorar(vertices_explorados, node_size);
            }
        }
    }

    // máximo: retorna o máximo (todos incluídos) de vértices naquele subgrafo fortemente conexo do grafo
}
