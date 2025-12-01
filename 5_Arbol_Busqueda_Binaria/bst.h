#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>

template <class T> class BST;
template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* predecesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);
	void remove(T);
    void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;
    int height() const;
    void printLevel(std::stringstream& aux, int level) const;
	bool ancestors(T val, std::string &res);
	int whatlevelamI(T val, int level);

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0){}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri){}

template <class T>
void TreeNode<T>::add(T val) {
	if(val < value){
		if(left != 0){
			left->add(val);
		} else {
			left = new TreeNode<T>(val);
		}
	} else {
		if (right != 0){
			right -> add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
    return false;
}

template <class T>
TreeNode<T>* TreeNode<T>::predecesor() { //Mas grande de los chicos
	TreeNode<T> * le;
	TreeNode<T> * ri;
	
	le = left;
	ri = right;

	//Caso 1
	if (left == 0){
		if(right!=0){
			right = 0;
		}
		return ri;
	}

	//Caso 2
	if (left->right == 0){
		left = left->left;
		le->left = 0;
		return le;
	}

	//Caso 3
	TreeNode<T> *parent, *child;
	parent = left;
	child = left->right;
	while(child->right != 0){
		parent = child;
		child = child->right;
	}
	parent->right = child->right;
	child->left=0;
	return child;
}

template <class T>
void TreeNode<T>::remove(T val) {
	TreeNode<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void TreeNode<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void TreeNode<T>::postorder(std::stringstream& aux) const {
	if (left != 0) {
		left->postorder(aux);
        aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
        aux << " ";
	}
	aux << value;
}

template <class T>
int TreeNode<T>::height() const {
	// Si no hay hijos, significa que este nodo es la raiz y unica hoja
	if (left == 0 && right == 0)
		return 1;

	int leftH = (left == 0 ? 0 : left->height());
	int rightH = (right == 0 ? 0 : right->height());

	return 1 + std::max(leftH, rightH);
}

template <class T>
void TreeNode<T>::printLevel(std::stringstream& aux, int level) const {
	if (level == 1) {
		aux << value << " ";
	} else if (level > 1) {
		if (left != 0)
			left->printLevel(aux, level - 1);
		if (right != 0)
			right->printLevel(aux, level - 1);
	}
}

template <class T>
bool TreeNode<T>::ancestors(T val, std::string &res) {
    if (val == value)
        return true;

    if (left && left->ancestors(val, res)) {
        res = std::to_string(value) + " " + res;
        return true;
    }

    if (right && right->ancestors(val, res)) {
        res = std::to_string(value) + " " + res;
        return true;
    }

    return false;
}

template <class T>
int TreeNode<T>::whatlevelamI(T val, int level) {
    if (value == val)
        return level;

    if (left) {
        int leftLevel = left->whatlevelamI(val, level + 1);
        if (leftLevel != 0) return leftLevel;
    }

    if (right) {
        int rightLevel = right->whatlevelamI(val, level + 1);
        if (rightLevel != 0) return rightLevel;
    }
    return 0;
}

template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
    std::string postorder() const;
    int height() const;
    std::string levelByLevel() const;
	std::string ancestors(T val);
    std::string visit();
	int whatlevelamI(T val);
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if(root != 0){
		if (!root-> find(val)){
			root->add(val);
		}
	}else {
		root = new TreeNode<T>(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
    if (root != 0) {
		if (val == root->value) {
			TreeNode<T> *succ = root->predecesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
    if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0){
		return root ->find(val);
	} else{
		return false;
	}
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
int BST<T>::height() const {
	if (empty()) return 0;
	return root->height();
}

template <class T>
std::string BST<T>::levelByLevel() const {
	std::stringstream aux;
	aux << "[";

	if (!empty()) {
		int h = root->height(); // se usa height() para saber hasta donde recorrer
		for (int i = 1; i <= h; i++) {
			root->printLevel(aux, i);
		}
	}

	std::string res = aux.str();

	if (!res.empty() && res[res.size() - 1] == ' ') {
        res.pop_back();
    }
	res += "]";
	return res;
}

template <class T>
std::string BST<T>::visit() {
    std::stringstream aux;
    aux << preorder() << "\n";
    aux << inorder() << "\n";
    aux << postorder() << "\n";
    aux << levelByLevel();
    return aux.str();
}

template <class T>
std::string BST<T>::ancestors(T val) {
    std::string res = "";
    if (root == nullptr) return "[]";
    bool found = root->ancestors(val, res);
    if (!found) return "[]";
    return "[" + res.substr(0, res.size() - 1) + "]";
}

template <class T>
int BST<T>::whatlevelamI(T val) {
    if (root == nullptr)
        return 0;
    return root->whatlevelamI(val, 1); // la raíz está en nivel 1
}

#endif