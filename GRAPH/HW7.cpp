
/*
Реализация алгоритмов поиска кратчайших расстояний до всех вершин от заданной.
Алгоритмы Форда-Беллмана и Дейкстры.

Разработаны следующие функции:
1. Создание случайного графа. Сначала создается двоичное дерево
из N вершин (чтобы граф был связным) - genBinGraf, а потом addRand() - в этот граф добавляются
N*N/4 случайных рёбер. Создается список смежности для Дейкстры
и матрица смежности и список рёбер для Форда-Беллмана.
2. Deikstra1- Алгоритм Дейкстры с использованием функций Rekax() и FindMin().
3. Deikstra2- Алгоритм Дейкстры с использованием множества STL set.
4. Ford1- Алгоритм Форда-Беллмана с использованием матрицы смежности (M[i][j]- вес ребра, иначе 0).
5. Ford2- Алгоритм Форда-Беллмана с использованием списка рёбер.

Проведено сравнение алгоритмов. Алгоритм Форда-Беллмана работает на порядок медленнее алгоритма Дейкстры,
поэтому на графиках приведены результаты сравнения Deikstra1 и Deikstra2 (dijkstra1_2.png) и
Ford1 и Ford2 (ford1_2.png).
*/

#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Edge{ 
	long v;     //v - с какой вершиной связана;
	int w;      //w - вес; 
	long v1;  //  первая вершина ребра (для списка рёбер в Форде);
};

const int INF = 30000; //INF - максимально большое число для веса;
char prn = 0; //для отладки;

long N; //количество вершин;

vector < vector <Edge> > G; //список смежности;
vector < vector <int> > M; //матрица смежности;
vector <Edge> V; //список рёбер;
vector <int> D; //вектор весов путей;
vector <int> used;

//СЛУЧАЙНЫЕ ЧИСЛА В ЗАДАННОМ ДИАПАЗОНЕ.
int random (int min, int max){
    max++;
    return abs(rand()%(max-min)) + min;
}

//ГЕНЕРАЦИЯ БИНАРНОГО ДЕРЕВА.
void genBinGraf(){
	Edge e;
	for( int  i=1; i <= N; i++){
		//ПЕЧАТЬ ГРАФА
		unsigned long t = i;
		if( prn) {if( (t & ( t - 1) )== 0) cout << endl;}; //endl, когда i - степень двойки;
		if( prn) { cout << i << " "; };
		
		int w = random(2,N); //вес ребра;
		
		int ii = i;
		if( i==1 || (ii & ( ii - 1) )== 0) w = 1; // для отладки вес всех левых рёбер дерева = 1;
		e.w = w;
		//
		long v = i << 1; //номер левого потомка;
		if( v <= N) {

			e.v = v-1;	G[i-1].push_back(e); //в список смежности для i;
			
			e.v1 = i-1; V.push_back(e);  //в список ребер;
			
			e.v = i-1;	G[v-1].push_back(e);//в список смежности для v;
			M[i-1][v-1] = w; //в матрицу смежности для i;
			M[v-1][i-1] = w; //в матрицу смежности для v;
			
			v++; //номер правого потомка, далее аналогично левому потомку;
		   if(v <= N){	
			w = random(2,N);
			e.w = w;
			M[i-1][v-1] = w;
			M[v-1][i-1] = w;
			e.v = v-1;	G[i-1].push_back(e);
			e.v1 = i-1; V.push_back(e);  //в список рёбер;

			e.v = i-1;	G[v-1].push_back(e);
		   }
		} 
	}
}
//ДОБАВЛЕНИЕ СЛУЧАЙНЫХ РЁБЕР.
void addRand(){
	Edge e;
	int m = N*N/8; //количество рёбер;
	
	int i=0; int j=0;
	while(m > 0){                   //пока не добавим m рёбер;
		i = random(0,N-1);  
		j = random(0,N-1);
		if( (i==j) || (M[i][j] !=0) ) continue;
		long w = random(2,N);
		
		M[i][j] = w;
		M[j][i] = w;
		
		e.w = w;
		e.v = j;	G[i].push_back(e);
		
		e.v1 = i;   V.push_back(e);  //в список рёбер;

		e.v = i;	G[j].push_back(e);
		m--;
	}	
}

//ПОИСК ВЕРШИН С МИНИМАЛЬНЫМ ВЕСОМ.
long FindMin(){
	int v;
	int min = INF;
	for( long i = 0; i < N; i++){
			//if(D[i] == INF) continue;
			if(!used[i] && (D[i] <= min )){
				min = D[i]; 
				v = i;			
			}
	}
	used[v] = 1;
	return v;
}
//РЕЛАКСАЦИЯ.
void Relax(int v){
	for( int i = 0; i < G[v].size(); i++){
		int v2 = G[v][i].v;
		if( (D[v] + G[v][i].w) < D[v2] ){
			D[v2] = D[v] + G[v][i].w;
		}		
	}
}

//АЛГОРИТМ ДЕЙКСТРЫ.
void Deikstra1(int s){
	D[s] = 0;
	for( long i = 0; i < N; i++){
		int v = FindMin();
		Relax(v);		
	}
}
//АЛГОРИТМ ДЕЙКСТРЫ С ИСПОЛЬЗОВАНИЕМ МНОЖЕСТВА STL SET.
void Deikstra2(int s){
	set < pair<int,int> > q;
	D[s] = 0;
	q.insert (make_pair (D[s], s));
	while (!q.empty()) {
		int v = q.begin()->second; //достаем из set с самым маленьким w;
		q.erase (q.begin());  //и удаляем его из set;
		for( long j = 0; j < G[v].size(); j++){
			int to = G[v][j].v;
			int len = G[v][j].w;
			if (D[v] + len < D[to]) {
				if (D[j] != INF) q.erase (make_pair (D[to], to));
				D[to] = D[v] + len;
				q.insert (make_pair(D[to], to));
			}
		}
	}
}

/*АЛГОРИТМ ФОРДА-БЕЛЛМАНА С ИСПОЛЬЗОВАНИЕМ МАТРИЦЫ СМЕЖНОСТИ
(M[i][j]- вес ребра, иначе 0) ЗА O(n^3). */
void Ford1(int s){
	D[s] = 0;
	for( int k = 1; k < N; k++){  //повторяем релаксацию N-1 раз для всех рёбер;
		for(long i = 0; i < N; i++){
			for(long j = 0; j < N; j++){
				//cout << i << " " << j << " " << D[i] << "=+=+=+" << D[j] << " " << M[j][i]<< endl;
				if( M[i][j] == 0) continue;  //нет ребра i <-> j;
				if (D[i] + M[i][j] < D[j]){
					D[j] = D[i] + M[i][j];
				}
			}
		}
	}
}

//АЛГОРИТМ ФОРДА-БЕЛЛМАНА С ИСПОЛЬЗОВАНИЕМ СПИСКА РЁБЕР ЗА O(N*V).
void Ford2(int s){
	D[s] = 0;
	/*
		for( int j=0; j < N; j++)
			cout << D[j] << " ";
		cout << endl;
	*/	
	for( int i = 1; i < N; i++){
		for(long j = 0; j < V.size(); j++){
			int a = V[j].v1;
			int b = V[j].v;
			int w = V[j].w;
		//cout << a << " "<< b << " " << D[a] << " " << D[b] << " "<< w << endl;
			if( D[a] < INF) 
				D[b] = min(D[b], D[a] + w);
			swap(a,b);
			if( D[a] < INF) 
				D[b] = min(D[b], D[a] + w);
			
		}
		/*
		for( int j=0; j < N; j++)
			cout << D[j] << " ";
		cout << endl;
		*/

	}
}

//ПЕЧАТЬ РАССТОЯНИЙ.
void printD(){
	return;
	for(int i=1; i <= N; i++){
		cout << i << " " << D[i-1] << endl;
		if(i > 20) break;
	}
	cout << "---------------------------------" << endl;
}

void ClearData(){
	D.assign(D.size(), INF);
	used.assign(used.size(), 0);
}
int main(int argc, char** argv) {
	clock_t t1; //стартовое время;
	double t2; //результирующее время;
	
	N = 1000;
	
	D.resize(N,INF); 
	used.resize(N,0);
	M.resize(N+1,vector <int>(N+1,0));
	G.resize(N+1, vector <Edge>());
	
	genBinGraf(); cout << endl;
	addRand();
/*	
	for( int i=0; i <V.size(); i++) {
		cout << V[i].v1<< " "<< V[i].v << " " << V[i].w << endl;
	}
*/
//	system("pause");
//	return 0;

	t1 = clock(); //начало времени;
	Deikstra1(0);
	t2 = double(clock() - t1) / CLOCKS_PER_SEC; //сколько времени заняли заданные процессы;
	std::cout << "Deikstra1 " << t2 << " sec.=============" << std::endl;
	printD();
	
	ClearData();
	t1 = clock(); //начало времени;
	Deikstra2(0);
	t2 = double(clock() - t1) / CLOCKS_PER_SEC; //сколько времени заняли заданные процессы;
	std::cout << "Deikstra2 " << t2 << " sec.=============" << std::endl;
	printD();

	ClearData();
	t1 = clock(); //начало времени;
	Ford1(0);
	t2 = double(clock() - t1) / CLOCKS_PER_SEC; //сколько времени заняли заданные процессы;
	std::cout << "Ford1 " << t2 << " sec.=============" << std::endl;
	printD();

	ClearData();
	t1 = clock(); //начало времени;
	Ford2(0);
	t2 = double(clock() - t1) / CLOCKS_PER_SEC; //сколько времени заняли заданные процессы;
	std::cout << "Ford2 " << t2 << " sec.=============" << std::endl;
	printD();

	system("pause");
	return 0;
}
