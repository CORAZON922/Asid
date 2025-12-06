#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

enum Color { RED, BLACK };

template <typename T>
class RBTree {
private:
    struct Node {
        T data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& value)
            : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
        }
    };

    Node* root;
    Node* TNULL;  

private:
    void clear(Node* node);
    void initializeNULLNode();

    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixInsert(Node* k);
    void fixDelete(Node* x);
    void transplant(Node* u, Node* v);

    Node* insert(Node* node, const T& value);
    Node* remove(Node* node, const T& value);
    Node* minimum(Node* node);
    Node* searchTreeHelper(Node* node, const T& value) const;

    void inorder(Node* node) const;
    void preorder(Node* node) const;
    void postorder(Node* node) const;

    
    void printTreeHelper(Node* node, int space, bool last) const;
    int getBlackHeight(Node* node) const;

public:
    RBTree();
    ~RBTree();

    void insert(const T& value);
    void remove(const T& value);
    bool search(const T& value) const;

    void displayInorder() const;
    void displayPreorder() const;
    void displayPostorder() const;
    void displayTree() const;

    bool isEmpty() const { return root == TNULL; }
    void displayRBProperties() const;
   
};


template <typename T>
RBTree<T>::RBTree() {
    TNULL = new Node(T());  
    TNULL->color = BLACK;   
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;  
}

template <typename T>
RBTree<T>::~RBTree() {
    clear(root);
    delete TNULL;
}



template <typename T>
void RBTree<T>::clear(Node* node) {
    if (node != TNULL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}


template <typename T>
void RBTree<T>::leftRotate(Node* x) {
    Node* y = x->right;  

    x->right = y->left;

    if (y->left != TNULL) {
        y->left->parent = x;
    }

    y->parent = x->parent;  

    if (x->parent == nullptr) {  
        root = y;
    }
    else if (x == x->parent->left) {  
        x->parent->left = y;
    }
    else { 
        x->parent->right = y;
    }

    y->left = x; 
    x->parent = y;
}

template <typename T>
void RBTree<T>::rightRotate(Node* x) {
    Node* y = x->left; 

    x->left = y->right;  

    if (y->right != TNULL) {
        y->right->parent = x;
    }

    y->parent = x->parent;  

    if (x->parent == nullptr) {  
        root = y;
    }
    else if (x == x->parent->right) { 
        x->parent->right = y;
    }
    else {  
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}


template <typename T>
void RBTree<T>::fixInsert(Node* k) {
    Node* u; 

    while (k->parent != nullptr && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
           
            u = k->parent->parent->left;  

            if (u->color == RED) {
                
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                   
                    k = k->parent;
                    rightRotate(k);
                }

                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        else {
          
            u = k->parent->parent->right;  

            if (u->color == RED) {
                
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    
                    k = k->parent;
                    leftRotate(k);
                }
               
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }

        if (k == root) {
            break;
        }
    }

    root->color = BLACK;  
}


template <typename T>
void RBTree<T>::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


template <typename T>
typename RBTree<T>::Node* RBTree<T>::minimum(Node* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

template <typename T>
void RBTree<T>::fixDelete(Node* x) {
    Node* s;  

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;

            if (s->color == RED) {
                
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
              
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->right->color == BLACK) {
                   
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }
                
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else {
         
            s = x->parent->left;

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}


template <typename T>
typename RBTree<T>::Node* RBTree<T>::insert(Node* node, const T& value) {
    Node* parent = nullptr;
    Node* current = root;

    while (current != TNULL) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        }
        else if (value > current->data) {
            current = current->right;
        }
        else {
            return node;
        }
    }

    Node* newNode = new Node(value);
    newNode->left = TNULL;
    newNode->right = TNULL;
    newNode->parent = parent;

    if (parent == nullptr) {
        root = newNode;
    }
    else if (value < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    if (newNode->parent == nullptr) {
        newNode->color = BLACK;
        return newNode;
    }

    if (newNode->parent->parent == nullptr) {
        return newNode;
    }

    fixInsert(newNode);
    return newNode;
}

template <typename T>
void RBTree<T>::insert(const T& value) {
    std::cout << "Вставка " << value << std::endl;
    insert(root, value);
}


template <typename T>
typename RBTree<T>::Node* RBTree<T>::searchTreeHelper(Node* node, const T& value) const {
    if (node == TNULL || value == node->data) {
        return node;
    }

    if (value < node->data) {
        return searchTreeHelper(node->left, value);
    }
    return searchTreeHelper(node->right, value);
}

template <typename T>
bool RBTree<T>::search(const T& value) const {
    Node* result = searchTreeHelper(root, value);
    return result != TNULL;
}

template <typename T>
typename RBTree<T>::Node* RBTree<T>::remove(Node* node, const T& value) {
    Node* z = TNULL;
    Node* x, * y;

    while (node != TNULL) {
        if (node->data == value) {
            z = node;
        }

        if (node->data <= value) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        std::cout << "Элемент " << value << " не найден" << std::endl;
        return root;
    }

    y = z;
    Color yOriginalColor = y->color;

    if (z->left == TNULL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK) {
        fixDelete(x);
    }

    return root;
}

template <typename T>
void RBTree<T>::remove(const T& value) {
    std::cout << "Удаление " << value << std::endl;
    root = remove(root, value);
}


template <typename T>
void RBTree<T>::inorder(Node* node) const {
    if (node != TNULL) {
        inorder(node->left);
        std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorder(node->right);
    }
}

template <typename T>
void RBTree<T>::preorder(Node* node) const {
    if (node != TNULL) {
        std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        preorder(node->left);
        preorder(node->right);
    }
}

template <typename T>
void RBTree<T>::postorder(Node* node) const {
    if (node != TNULL) {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
    }
}

template <typename T>
void RBTree<T>::displayInorder() const {
    std::cout << "Inorder (R-красный, B-черный): ";
    inorder(root);
    std::cout << std::endl;
}

template <typename T>
void RBTree<T>::displayPreorder() const {
    std::cout << "Preorder (R-красный, B-черный): ";
    preorder(root);
    std::cout << std::endl;
}

template <typename T>
void RBTree<T>::displayPostorder() const {
    std::cout << "Postorder (R-красный, B-черный): ";
    postorder(root);
    std::cout << std::endl;
}


template <typename T>
void RBTree<T>::printTreeHelper(Node* node, int space, bool last) const {
    if (node != TNULL) {
        space += 10;

        printTreeHelper(node->right, space, false);

        std::cout << std::endl;
        for (int i = 10; i < space; i++) {
            std::cout << " ";
        }

        std::cout << node->data;
        if (node->color == RED) {
            std::cout << "[R]";
        }
        else {
            std::cout << "[B]";
        }

        if (last) {
            std::cout << " ──┐";
        }
        else {
            std::cout << " ──┤";
        }
        std::cout << std::endl;

        printTreeHelper(node->left, space, true);
    }
}

template <typename T>
void RBTree<T>::displayTree() const {
    std::cout << "\nКрасно-черное дерево:\n";
    std::cout << "=====================\n";
    if (root == TNULL) {
        std::cout << "Дерево пустое\n";
    }
    else {
        printTreeHelper(root, 0, true);
    }
    std::cout << "=====================\n";
}


template <typename T>
int RBTree<T>::getBlackHeight(Node* node) const {
    int blackHeight = 0;
    while (node != TNULL) {
        if (node->color == BLACK) {
            blackHeight++;
        }
        node = node->left;
    }
    return blackHeight;
}


template <typename T>
void RBTree<T>::displayRBProperties() const {
    std::cout << "\nСвойства RB-дерева:\n";
    std::cout << "1. Корень: " << (root == TNULL ? "пустой" : std::to_string(root->data))
        << ", цвет: " << (root->color == RED ? "КРАСНЫЙ (нарушение!)" : "ЧЕРНЫЙ") << std::endl;

    if (root != TNULL) {
        std::cout << "2. Черная высота: " << getBlackHeight(root) << std::endl;
    }
}



