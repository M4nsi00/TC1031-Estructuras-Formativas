#ifndef SORTS_H
#define SORTS_H
#include <iostream>
using namespace std;

#include <vector>
#include <list>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
public:
	std::vector<T> ordenaBurbuja(std::vector<T>&);
	std::vector<T> ordenaSeleccion(std::vector<T>&);
	std::vector<T> ordenaMerge(std::vector<T>&);
    int busqSecuencial(std::vector<T>&, int num);
    int busqBinaria(std::vector<T>&, int num);
};

//Funcion para realizar los swaps dentro de los algoritmos de ordenamiento
template <class T> //Polimorfismo
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

//Ejercicio 1
//Ordenar de forma ascendente los datos utilizando el algoritmo de seleccion
template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T> &source) {
    std::vector<T>& v = source;
int pos;

	for (int i = v.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (v[j] > v[pos]) {
				pos = j;
			}
		}
		if (pos != i) {
			swap(v, i, pos);
		}
	}
	return v;
}

//Ejercicio 2
//Ordenar de forma ascendente los datos utilizando el algoritmo de burbuja
template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector<T> &source) {
    std::vector<T>& v = source;
    for (int i = v.size()-1; i > 0; i--){
        for(int j= 0; j < i; j++){
            if(v[j]>v[j+1]){
                swap(v, j, j+1);
            }
        }
    }
    return v;
}

//Ejercicio 3
//Ordenar de forma ascendente los datos utilizando el algoritmo de Merge
template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for(int i = low; i <= high; i++){
		A[i] = B[i];
	}
}

//Función que ayuda a unir de regreso el arreglo despues de separar el vector
//Mientras los une otra vez concatena los valores para acomodarlos de menor a mayor
template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid && j <= high){
		if (A[i] < A[j]){
			B[k] = A[i];
			i++;
		} else{
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid){
		for(; j <= high; j++){
			B[k++] = A[j];
		}
	} else{
		for(; i <= mid; i++){
			B[k++] = A[i];
		}
	}
}

//Función que divide el vector en dos vectores
template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ((high - low) < 1){
		return;
	}
	mid = (high + low)/2;
	mergeSplit(A , B, low, mid);
	mergeSplit(A, B , mid + 1, high);
	mergeArray(A , B , low, mid, high);
	copyArray(A , B ,low, high);
}
template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T> &source) {
    std::vector<T>& v = source;
	std::vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0, v.size() - 1);
    return v;
}


//Ejercicio 4
//Utilizando un buscador Secuencial se identifica la localización de un numero
//En caso que el numero no se encuentre la función regresa el valor de -1
template <class T>
int Sorts<T>::busqSecuencial( std::vector<T>& v, int num){
	int mid;
	int low = 0;
	int high = v.size()-1;

	while (low <= high) {
		mid = (high + low) / 2;
		if (num == v[mid]) {
			return mid;
		} else if (num < v[mid]) {
			high = mid - 1;
		} else  {
			low = mid + 1;
		}
	}
	return -1;
}

//Ejercicio 4
//Utilizando un buscador Binario se identifica la localización de un numero
//En caso que el numero no se encuentre la función regresa el valor de -1

//Se usa una función que ayuda a trabajar la recursion, para poder utilizar
//Valores temporales en vez de modificar siempre los valores low y high iniciales
//Creando asi un bucle
template <class T>
int bs_aux(std::vector<T>& v, int low, int high, int val){
	int mid;

	if (low <= high) {
		mid = (high + low) / 2;
		if (val == v[mid]) {
			return mid;
		} else if (val < v[mid]) {
			return bs_aux(v, low, mid - 1, val);
		} else{
			return bs_aux(v, mid + 1, high, val);
		}
	}
	return -1;
}

template <class T> //Poliformismo
int Sorts<T>::busqBinaria(std::vector<T>& v, int num){
	return bs_aux(v, 0, v.size() - 1, num);
}

#endif