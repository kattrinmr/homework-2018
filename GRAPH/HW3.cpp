/* Реализовать программу существования пути между двумя точками */
#include<iostream>
#include<vector>

using namespace std;

int v; //Количество вершин
int** g = new int*[v];

//ПОИСК В ГЛУБИНУ
void dfs(int n, int* used){
    used[n] = 1;
    for( int i = 0; i < v; i++){
        if((used[i] == 0) && (g[n][i] == 1)){
            dfs(i, used);
    }
 }
}
//ПЕРЕВЕСТИ В МАТРИЦУ СМЕЖНОСТИ
void MakeMatrixAdj(vector<pair<int,int> > gr, int** matrix){
        for( int i = 0; i < gr.size(); i++){
            matrix[gr[i].first - 1][gr[i].second - 1] = 1;
            matrix[gr[i].second - 1][gr[i].first - 1] = 1;
        }
  }

//ВЫЧИСЛЕНИЕ КОЛИЧЕСТВА КОМПОНЕНТ СВЯЗНОСТИ
int number_of_con_com(int* used){
    int temp = 1;
    for(int j = 0; j < v; j++){
        if(used[j] == 0){
            dfs(j, used);
            temp++;
        }
    }
    return temp;
}
//ПРОВЕРКА СУЩЕСТВОВАНИЯ ПУТИ
bool way(int x, int y, int* used){
    used[x-1] = 1;
    for(int i = 0; i < v; i++){
        if((used[i] == 0) && (g[x-1][i] == 1)){
            if(i + 1 == y) return 1;
            else{ return way(i + 1, y, used);}
        }
     }
    return 0;
}

int main(int argc, char** argv){
    int E; //Количество рёбер
    cout << "Enter the number of vertexes: ";
    cin >> v;
    cout << "Enter the number of edges: ";
    cin >> E;

    int* used = new int[v];
    for(int j = 0; j < v; j++){
        used[j] = 0;
    }
    //СПИСОК РЁБЕР И ЕГО ЗАПОЛНЕНИЕ
    vector<pair<int,int> > h;
    int f, s;
    for(int i = 0; i < E; i++){
        cout << "Enter the information for the " << i+1 << "'th edge: ";
        cin >> f >> s;
        h.push_back(make_pair(f,s));
    }

    //СОЗДАНИЕ МАТРИЦЫ СМЕЖНОСТИ
    for(int i = 0; i < v; i++){
        g[i] = new int[v];
    }
    for(int i = 0; i < v; i++){
            for(int j = 0; j < v; j++){
                g[i][j] = 0;
            }
        }
    MakeMatrixAdj(h, g);

    cout << "Does the way exist?: " << way(1,2,used);

    //УДАЛЕНИЕ ПАМЯТИ
    delete[] used;
    for(int i = v-1; i >= 0; i--){
        delete[] g[i];
    }
    return 0;
}
