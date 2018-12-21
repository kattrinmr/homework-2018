#include <iostream>
#include <vector>

using namespace std;

	int n = 4, k = 5;
	vector < vector<int> > g = { { 0,1,2 }, { 0,2 }, { 0,1,2 }, { 3,4 } };
	vector<int> mt; //mt[i] - это вершины левой доли, i - это вершины правой доли
	vector<int> used;


bool try_kuhn (int v) {
	cout << "start "<< "v = "<< v << " used[v]="<<used[v] << endl;
	if (used[v]){	//Если уже посещённая
	  cout << "return false (used)" << endl;
	  return false;
	}
	used[v] = 1; //Если нет, отмечаем как посещённую
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i]; //В какую вершину 
		cout << "i="<< i << " to = " << to << "   mt[to]=" << mt[to] << endl;
	
		/*if(to == from){
			cout << "continue to == from"<< endl;
			continue;}*/
	
		if (mt[to] == -1 || try_kuhn( mt[to],to )) { //если не связаны или try_kuhn(mt[to], to)
			cout << " Change mt[to]: to = " << to << " v=" << v << endl;
			mt[to] = v;
			cout << "return true (change)" << endl;
			return true;
		}
	}
	cout << "return false (no edges)" << endl;
	return false;
}

int main(int argc, char** argv) {
	mt.resize(k,-1);
	mt[1] = 2;
	used.resize(n,0);
	//mt.assign (k, -1);
	for (int v=0; v<n; ++v) {
		cout << "------------v="<<v << endl;
		used.assign (n, 0);
		try_kuhn (v, -1);
	}
 
	for (int i=0; i<k; ++i)
		if (mt[i] != -1)
			printf ("%d %d\n", mt[i]+1, i+1);	

	
	system("pause");
	return 0;
}
