#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;

	Key *keys;
	Key initialValue;
	Value *values;

	long indexOf(const Key) const;

public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ; //*f es la funcion con la que corres el hash 
	~Quadratic();
	bool full() const;
	bool put(Key, Value);
	bool contains(const Key) const;
	Value get(const Key) ;
	void clear();
	std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
	size = sze;
	keys = new Key[size];
	initialValue = init;
	for(int i = 0; i < size;i++){
		keys[i] = init;
	}
	values = new Value[size];
	for(int i = 0; i < size; i++){
		values[i] = 0;
	}
	func = f;
	count = 0;

}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;

}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	unsigned int step = 1;

	start = i = func(k) % size;
	do{
		if (keys[i] == k){
			return i;
		}
		i = (start + step*step) % size;
		step++;
		if (step==size){
			return -1;
		}
	} while (start != i);
	return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i,start;
	unsigned int step = 1;

	long pos;
	if(full()){
		return false;
	}
	pos = indexOf(k);
	if(pos != -1){
		values[pos] = v;
		return true;
	}
	start = i = func(k) % size;
	do{
		if(keys[i] == initialValue){
			keys[i] = k;
			values[i] = v;
			count ++;
			if(step==size){
				return false;
			}
			return true;
		}
		i = (start + step*step) % size;
		step ++;
		if(step==size){
			return false;
		}
	} while(start != i);
	return false;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	long pos;

	pos = indexOf (k);
	return(pos != -1);
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	Value v;
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if(pos != -1){
		v = values[pos];
		return v;
	}
	return -1;
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for(int i = 0; i < size; i++){
		keys[i] = initialValue;
	}
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}
#endif
