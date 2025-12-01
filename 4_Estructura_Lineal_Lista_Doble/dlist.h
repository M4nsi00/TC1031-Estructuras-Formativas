#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	void addFirst(T);
	void insertion(T);
    int search(T val) const;
    void update(int pos, const T& newVal); 
    T deleteAt(int pos);
	T    getFirst() const ;
	T    removeFirst() ;
	T	 getLast() const ;
	T    removeLast() const;
	int  length() const;
	T    get(int) const;
	bool contains(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
    std::string toStringForward() const;
    std::string toStringBackward() const;
	void operator= (const DList&);

private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;
};

template <class T>
DList<T>::DList(): head(0) , tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
	clear();
}

template <class T>
bool DList<T>::empty() const {
	return (size == 0);
}

template <class T>
int DList<T>::length() const {
	return size;
}

template <class T>
bool DList<T>::contains(T val) const {
	DLink<T> *ptr;

	ptr = head;
	while (ptr != 0) {
		if (ptr->value == val) {
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

template <class T>
void DList<T>::insertion(T val)  {
	DLink<T> *newLink;
	newLink = new DLink<T>(val);

	if (empty()){
		head = newLink;
		tail = newLink;
	} else{
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size ++;
}

// Funcion que encuentra un elemento en la lista y
// devuelve la posicion del nodo en el que se encuentra
// si no encuentra el valor regresa un -1
template <class T>
int DList<T>::search(T val) const {
    DLink<T>* ptr = head;
    int index = 0;

    while (ptr != 0) {
        if (ptr->value == val) {
            return index;
        }
        ptr = ptr->next;
        index++;
    }

    return -1; // no se encontró el valor
}

// Funcion que actualiza el valor de una lista buscando
// la posicion del elemento que se quiere cambiar y el 
// valor nuevo que tendra
template <class T>
void DList<T>::update(int pos, const T& newVal) {
    if (pos < 0 || pos >= size) {
        return;
    }

    DLink<T>* ptr = head;
    int index = 0;

    while (ptr != 0) {
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
T DList<T>::deleteAt(int pos) {
    if (pos < 0 || pos >= size) {
        throw std::out_of_range("Posición fuera de rango");
    }

    DLink<T>* ptr = head;
    int index = 0;

    while (index < pos) {
        ptr = ptr->next;
        index++;
    }

    T deletedValue = ptr->value;

    // caso 1: eliminar head
    if (ptr == head) {
        head = head->next;
        if (head != 0) {
            head->previous = 0;
        } else {
            tail = 0; // la lista queda vacía
        }
    }
    // caso 2: eliminar tail
    else if (ptr == tail) {
        tail = tail->previous;
        if (tail != 0) {
            tail->next = 0;
        } else {
            head = 0; // la lista queda vacía
        }
    }
    // caso 3: nodo en medio
    else {
        ptr->previous->next = ptr->next;
        ptr->next->previous = ptr->previous;
    }

    delete ptr;
    size--;
    return deletedValue;
}

template <class T>
std::string DList<T>::toString() const {
	std::stringstream aux;
	DLink<T> *p;

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
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T>* p = head;

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
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T>* p = tail;

    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

template <class T>
void DList<T>::clear() {
}

#endif