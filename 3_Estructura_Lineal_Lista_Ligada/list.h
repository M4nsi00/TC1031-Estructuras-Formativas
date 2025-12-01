#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>

template <class T> class List;
template <class T> class ListIterator;

//Clase de Link
template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {

}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}


template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

    void addFirst(T) ;
    bool empty() const;
	void insertion(T) ;
	void update(int pos, const T& newVal) ;
	int search(T val) const;
    T    deleteAt(int pos);
	void clear();
	std::string toString() const;


private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List() : head(0), size(0){}

template <class T>
List<T>::~List() {
	clear();
}

// Funcion que checa si la lista esta vacía
template <class T>
bool List<T>::empty() const {
	if(size == 0){
	return true;
	} else{
        return false;
    }
}

// Funcion que agrega un nodo al inicio de la lista
template <class T>
void List<T>::addFirst(T val)  {
	Link<T> *elem;
	elem = new Link<T>(val);
	elem-> next = head;
	head = elem;
	size++;
}

// Funcion que encuentra un elemento en la lista y
// devuelve la posicion del nodo en el que se encuentra
// si no encuentra el valor regresa un -1
template <class T>
int List<T>::search(T val) const {
    Link<T>* ptr = head;
    int index = 0;
    while (ptr != nullptr) {
        if (ptr->value == val) return index;
        ptr = ptr->next;
        index++;
    }
    return -1;
}

//Funcion que inserta un valor en la lista
template <class T>
void List<T>::insertion(T val) {
    Link<T>* elem = new Link<T>(val);
    if (empty()) {
        head = elem;
    } else {
        Link<T>* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = elem;
    }
    size++;
}

// Funcion que actualiza el valor de una lista buscando
// la posicion del elemento que se quiere cambiar y el 
// valor nuevo que tendra
template <class T>
void List<T>::update(int pos, const T& newVal) {
	if (pos < 0 || pos >= size) {
        return;
    }

    Link<T>* ptr = head;
    int index = 0;
    while (ptr != nullptr) {
        if (index == pos) {
            ptr->value = newVal;
            return;
        }
        ptr = ptr->next;
        index++;
    }
}

// Funcion que recibe la posicion de un elemento que se
// desea borrar y elimina el valor
template <class T>
T List<T>::deleteAt(int pos) {
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posición fuera de rango");
    }

    Link<T>* ptr = head;
    T deletedValue;

    if (pos == 0) { // borrar el primer nodo (caso especial)
        head = head->next;
        deletedValue = ptr->value;
        delete ptr;
    } else {
        Link<T>* prev = nullptr;
        int index = 0;
        while (index < pos) {
            prev = ptr;
            ptr = ptr->next;
            index++;
        }
        // ahora ptr apunta al nodo a borrar
        prev->next = ptr->next;
        deletedValue = ptr->value;
        delete ptr;
    }

    size--; // actualizar tamaño
    return deletedValue;
}

template <class T>
void List<T>::clear() {
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}


template <class T>
List<T>::List(const List<T> &source)  {
}

#endif