#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;

class Funciones{
    public:
    int sumaIterativa(int);
    int sumaRecursiva(int);
    int sumaDirecta(int);
};

// Suma Iterativa, la funcion calcula una suma de 1 a n 
// utilizando un metodo iterativo. Recibe un numero entero 
// positivo (n) y regresa la suma de 1 a n.

int Funciones::sumaIterativa(int n){
    int total = 0;
    for (int i = 0; i <= n; i++){
        total += i;
    }
    return total;
}

// Suma Recursiva, la funcion calcula una suma de 1 a n 
// utilizando un metodo iterativo. Recibe un numero entero 
// positivo (n) y regresa la suma de 1 a n.

int Funciones::sumaRecursiva(int n){
    if (n == 1){
        return 1;
    }
    if (n<=0){
        return 0;
    }
    else{
        return sumaRecursiva(n-1) + n;
    }
}

// Suma Recursiva, la funcion calcula una suma de 1 a n 
// utilizando un metodo iterativo. Recibe un numero entero 
// positivo (n) y regresa la suma de 1 a n.

int Funciones::sumaDirecta(int n){
    // Se usa una formula matematica para el calculo
    //Siendo esta (n * (n+1)) / 2
    return ((n * (n + 1)) / 2);
}





#endif