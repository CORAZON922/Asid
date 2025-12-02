#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

template <typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

private:
   
    void clear(Node* node);
    int getHeight(Node* node) const;
    int getBalanceFactor(Node* node) const;
    void updateHeight(Node* node);

   
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

    
    Node* insert(Node* node, const T& value);
    Node* remove(Node* node, const T& value);
    Node* findMin(Node* node) const;
    bool search(Node* node, const T& value) const;

    void inorder(Node* node) const;
    void preorder(Node* node) const;
    void postorder(Node* node) const;

    void printLevel(Node* node, int level, int spaces, bool left) const;

public:
    void insert(const T& value);
    void remove(const T& value);
    bool search(const T& value) const;
    bool isEmpty() const { return root == nullptr; }

    void displayInorder() const;
    void displayPreorder() const;
    void displayPostorder() const;
    void displayTree() const;

    int getTreeHeight() const { return getHeight(root); }
    void displayBalanceInfo() const;
};


template <typename T>
int AVLTree<T>::getHeight(Node* node) const {
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::getBalanceFactor(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename T>
void AVLTree<T>::updateHeight(Node* node) {
    if (node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;


    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::balance(Node* node) {
    if (!node) return node;

    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        std::cout << "  -> Right rotation at node " << node->data << std::endl;
        return rotateRight(node);
    }

  
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        std::cout << "  -> Left-Right rotation at node " << node->data << std::endl;
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }


    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        std::cout << "  -> Left rotation at node " << node->data << std::endl;
        return rotateLeft(node);
    }

  
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        std::cout << "  -> Right-Left rotation at node " << node->data << std::endl;
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(Node* node, const T& value) {
    if (!node) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    else {
       
        return node;
    }


    return balance(node);
}

template <typename T>
void AVLTree<T>::insert(const T& value) {
    std::cout << "Вставка " << value << ":" << std::endl;
    root = insert(root, value);
    displayBalanceInfo();
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}


template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::remove(Node* node, const T& value) {
    if (!node) {
        return node;
    }

    if (value < node->data) {
        node->left = remove(node->left, value);
    }
    else if (value > node->data) {
        node->right = remove(node->right, value);
    }
    else {
        
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            if (!temp) {
                
                temp = node;
                node = nullptr;
            }
            else {
               
                *node = *temp; 
            }
            delete temp;
        }
        else {
            
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
    }

   
    if (!node) {
        return node;
    }

    
    return balance(node);
}

template <typename T>
void AVLTree<T>::remove(const T& value) {
    std::cout << "\nУдаление " << value << ":" << std::endl;
    root = remove(root, value);
    displayBalanceInfo();
}

template <typename T>
bool AVLTree<T>::search(Node* node, const T& value) const {
    if (!node) {
        return false;
    }

    if (value == node->data) {
        return true;
    }
    else if (value < node->data) {
        return search(node->left, value);
    }
    else {
        return search(node->right, value);
    }
}

template <typename T>
bool AVLTree<T>::search(const T& value) const {
    return search(root, value);
}


template <typename T>
void AVLTree<T>::inorder(Node* node) const {
    if (node) {
        inorder(node->left);
        std::cout << node->data << "(" << getBalanceFactor(node) << ") ";
        inorder(node->right);
    }
}

template <typename T>
void AVLTree<T>::preorder(Node* node) const {
    if (node) {
        std::cout << node->data << "(" << getBalanceFactor(node) << ") ";
        preorder(node->left);
        preorder(node->right);
    }
}

template <typename T>
void AVLTree<T>::postorder(Node* node) const {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << "(" << getBalanceFactor(node) << ") ";
    }
}

template <typename T>
void AVLTree<T>::displayInorder() const {
    std::cout << "Inorder (с баланс-факторами): ";
    inorder(root);
    std::cout << std::endl;
}

template <typename T>
void AVLTree<T>::displayPreorder() const {
    std::cout << "Preorder (с баланс-факторами): ";
    preorder(root);
    std::cout << std::endl;
}

template <typename T>
void AVLTree<T>::displayPostorder() const {
    std::cout << "Postorder (с баланс-факторами): ";
    postorder(root);
    std::cout << std::endl;
}



template <typename T>
void AVLTree<T>::displayTree() const {
    std::cout << "\nAVL Дерево (вертикальный вид):\n";
    std::cout << "===============================\n";
    printLevel(root, 0, 0, true);
    std::cout << "===============================\n";
}

template <typename T>
void AVLTree<T>::printLevel(Node* node, int level, int spaces, bool left) const {
    if (!node) {
        return;
    }

    printLevel(node->right, level + 1, spaces + 6, false);


    std::cout << std::string(spaces, ' ');
    if (level > 0) {
        std::cout << (left ? "└── " : "┌── ");
    }
    std::cout << node->data << "[h=" << node->height
  
    printLevel(node->left, level + 1, spaces + 6, true);
}


template <typename T>
void AVLTree<T>::displayBalanceInfo() const {
    std::cout << "Высота дерева: " << getTreeHeight() << std::endl;
}


template <typename T>
void AVLTree<T>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}


int main() {
    AVLTree<int> avl;

    std::cout << "=== AVL ДЕРЕВО (СБАЛАНСИРОВАННОЕ БИНАРНОЕ ДЕРЕВО ПОИСКА) ===\n";


    std::cout << "\n1. ДЕМОНСТРАЦИЯ БАЛАНСИРОВКИ ПРИ ВСТАВКЕ:\n";

    std::cout << "\na) Вставляем 10, 20, 30 (Right Right case -> Left rotation):\n";
    avl.insert(10);
    avl.displayTree();
    avl.insert(20);
    avl.displayTree();
    avl.insert(30);
    avl.displayTree();

    std::cout << "\nb) Вставляем 5, 4 (Left Left case -> Right rotation):\n";
    avl.insert(5);
    avl.displayTree();
    avl.insert(4);
    avl.displayTree();

    std::cout << "\nc) Вставляем 15, 25 (создаем Right Left case):\n";
    avl.insert(15);
    avl.displayTree();
    avl.insert(25);
    avl.displayTree();

    std::cout << "\nd) Вставляем 35, 40, 45 (Right Right case):\n";
    avl.insert(35);
    avl.displayTree();
    avl.insert(40);
    avl.displayTree();
    avl.insert(45);
    avl.displayTree();

   
