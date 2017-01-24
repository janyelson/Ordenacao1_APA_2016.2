#include <iostream>
#include <stdlib.h>


using namespace std;

class Sorts {
public:
   int *input;
	int siz;
   Sorts(int *input, int s);
   void selection();
   void insertion();
   void merge1(int ini, int fim);
   void merge2(int ini, int meio, int fim);
   void quick(int esq, int dir);
   int partitionTest(int esq, int dir);
   int lastElemento(int dir);
   void buildheap(int n);
   void maxheap(int i, int n);
   void swap1(int i, int j);
   void heap();

};

Sorts::Sorts(int *in, int s) {
   input = new int[s];
   siz = s;
   for(int i = 0;i < siz; i++) {
      input[i] = in[i];
   }
}

void Sorts::selection() {

	int i, j, m, x;
	for(i = 0; i < siz -1; i++) {
		m = i;
		for(j = i + 1; j < siz; j++) {
			if(input[j] < input[m]) {
				m = j;
			}
		}
		x = input[m];
		input[m] = input[i];
		input[i] = x;
	}
}

void Sorts::insertion() {
   int i, j, x;

	for(j = 0; j < siz; ++j) {
		x = input[j];
		for(i = j-1; i>=0 && input[i] > x; i--) {
			input[i+1] = input[i];
		}
		input[i+1] = x;
	}
}

void Sorts::merge1(int ini, int fim) {

	if (ini < fim) {
		int meio = ini + (fim - ini) / 2;
		merge1(ini, meio);
		merge1(meio + 1, fim);
		merge2(ini, meio, fim);
	}
}

void Sorts::merge2(int ini, int meio, int fim) {

	int *helper = new int[siz];
		for (int i = ini; i <= fim; i++) {
		helper[i] = input[i];
	}
	int i = ini; int j = meio + 1; int k = ini;
	while (i <= meio && j <= fim) {
		if (helper[i] <= helper[j]) {
			input[k] = helper[i];
			i++;
		} else {
			input[k] = helper[j];
			j++;
		}
		k++;
	}

	while (i <= meio) {
		input[k] = helper[i];
		k++;
		i++;
	}
	while (j <= fim) {
		input[k] = helper[j];
		k++;
		j++;
	}

	free(helper);
}

void Sorts::quick(int esq, int dir) {
	int p;
	if(esq < dir) {
		p = partitionTest(esq, dir);
		quick(esq, p - 1);
		quick(p+1, dir);
	}

}

int Sorts::partitionTest(int esq, int dir) {
	int pivo, aux, indicePivo;
	indicePivo = lastElemento(dir);
	pivo = input[indicePivo];
	dir--;
	while(esq <= dir) {
		for(;input[esq] < pivo; ++esq) {}
		for(;dir >= 0 && (input[dir] >= pivo); --dir) {}
		if(esq >= dir) {
			break;
		}
		else {
			aux = input[esq];
			input[esq] = input[dir];
			input[dir] = aux;
		}
	}
	aux = input[esq];
	input[esq] = input[indicePivo];
	input[indicePivo] = aux;
	return esq;

}

int Sorts::lastElemento(int dir) {
	int indice = dir;
	return dir;
}

void Sorts::heap(){

	int n = siz - 1;
	buildheap(n);
	for(int i = n; i>0; i--){
		swap1(0, i);
		n = n-1;
		maxheap(0, n);
	}
}

void Sorts::buildheap(int n){

	for(int i = n/2; i >= 0; i--){
		maxheap(i, n);
	}
}

void Sorts::maxheap(int i, int n){
	int left = 2*i;
	int right = 2*i+1;
	int largest = 0;
	if(left <= n && input[left] > input[i]){
		largest = left;
	}
	else{
		largest = i;
	}
	if(right <= n && input[right] > input[largest]){
		largest = right;
	}
	if(largest != i){
		swap1(i,largest);
		maxheap(largest, n);
	}
}

void Sorts::swap1(int i, int j){
	int t = input[i];
	input[i] = input[j];
	input[j] = t;
}


int main(int argc, char* argv[]) {

   int chooseSort = atoi(argv[1]);
   int siz;
   cin >> siz;
   int *input = new int[siz];

   for(int i = 0; i < siz; i++) {
      cin >> input[i];
   }

	Sorts *sorts = new Sorts(input, siz);

	switch(chooseSort) {
		case 1:
			sorts->selection();
			break;

		case 2:
			sorts->insertion();
			break;

		case 3:
			sorts->merge1(0, siz - 1);
			break;

		case 4:
			sorts->quick(0, siz - 1);
			break;

		case 5:
			sorts->heap();
			break;
	}

	for(int i = 0; i < siz; i++) {
      cout << sorts->input[i] << endl;
	}
	free(input);
   free(sorts->input);
	free(sorts);
}
