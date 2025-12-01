#include <iostream>
#include <vector>
#include <string>
#include <cmath>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& value) : data(value), left(nullptr), right(nullptr), heif {}
    };

    Node* root;

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

private:
   
    void clear(Node* node);
    Node* insert(Node* node, const T& value);
    Node* remove(Node* node, const T& value);
    Node* findMin(Node* node);
    bool search(Node* node, const T& value) const;
    void inorder(Node* node) const;
    void preorder(Node* node) const;
    void postorder(Node* node) const;

    
    int getHeight(Node* node) const;
    void printLevel(Node* node, int level, int spaces, bool left) const;
    void collectLevelData(Node* node, int level, std::vector<std::vector<std::string>>& levels, int pos, int width) const;

public:
   
    void insert(const T& value);
    void remove(const T& value);
    bool search(const T& value) const;
    void displayInorder() const;
    void displayPreorder() const;
    void displayPostorder() const;

    
    void displayTree() const;
    
};


template <typename T>
typename BST<T>::Node* BST<T>::insert(Node* node, const T& value) {
    if (node == nullptr) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else if (value > node->data) {
        node->right = insert(node->right, value);
    }

    return node;
}

template <typename T>
void BST<T>::insert(const T& value) {
    root = insert(root, value);
}


template <typename T>
bool BST<T>::search(Node* node, const T& value) const {
    if (node == nullptr) {
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
bool BST<T>::search(const T& value) const {
    return search(root, value);
}

template <typename T>
typename BST<T>::Node* BST<T>::findMin(Node* node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


template <typename T>
typename BST<T>::Node* BST<T>::remove(Node* node, const T& value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = remove(node->left, value);
    }
    else if (value > node->data) {
        node->right = remove(node->right, value);
    }
    else {
       
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        
        Node* temp = findMin(node->right);
        if (temp != nullptr) {
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
    }

    return node;
}

template <typename T>
void BST<T>::remove(const T& value) {
    root = remove(root, value);
}


template <typename T>
void BST<T>::inorder(Node* node) const {
    if (node != nullptr) {
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
}

template <typename T>
void BST<T>::preorder(Node* node) const {
    if (node != nullptr) {
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

template <typename T>
void BST<T>::postorder(Node* node) const {
    if (node != nullptr) {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
void BST<T>::displayInorder() const {
    std::cout << "Inorder traversal: ";
    inorder(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::displayPreorder() const {
    std::cout << "Preorder traversal: ";
    preorder(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::displayPostorder() const {
    std::cout << "Postorder traversal: ";
    postorder(root);
    std::cout << std::endl;
}


template <typename T>
void BST<T>::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}


template <typename T>
int BST<T>::getHeight(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}


template <typename T>
void BST<T>::displayTree() const {
    std::cout << "\nДерево (вертикальный вид):\n";
    std::cout << "==========================\n";
    printLevel(root, 0, 0, true);
    std::cout << "==========================\n";
}

template <typename T>
void BST<T>::printLevel(Node* node, int level, int spaces, bool left) const {
    if (node == nullptr) {
        return;
    }

    
    printLevel(node->right, level + 1, spaces + 4, false);

   
    std::cout << std::string(spaces, ' ');
    if (level > 0) {
        std::cout << (left ? "└── " : "┌── ");
    }
    std::cout << node->data << std::endl;

    
    printLevel(node->left, level + 1, spaces + 4, true);
}


template <typename T>
void BST<T>::collectLevelData(Node* node, int level,
    std::vector<std::vector<std::string>>& levels,
    int pos, int width) const {
    if (node == nullptr || level >= levels.size()) {
        return;
    }

    
    std::string value = std::to_string(node->data);
    if (value.length() == 1) value = " " + value;
    levels[level][pos] = value;

    
    if (node->left != nullptr) {
        collectLevelData(node->left, level + 1, levels, pos - width / 2 - 1, width / 2);
    }
    if (node->right != nullptr) {
        collectLevelData(node->right, level + 1, levels, pos + width / 2 + 1, width / 2);
    }
}


int main() {
    BST<int> tree;

    std::cout << "=== БИНАРНОЕ ДЕРЕВО ПОИСКА (BST) ===\n";

    
    std::cout << "\n1. СОЗДАНИЕ ИСХОДНОГО ДЕРЕВА\n";
    std::cout << "Вставляем элементы: 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45\n";

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(45);

    
    tree.displayTree();
    
    std::cout << "\n2. ОБХОДЫ ДЕРЕВА:\n";
    tree.displayInorder();
    tree.displayPreorder();
    tree.displayPostorder();

    std::cout << "\n3. ПОИСК ЭЛЕМЕНТОВ:\n";
    std::cout << "Поиск 40: " << (tree.search(40) ? "найден ✓" : "не найден ✗") << std::endl;
    std::cout << "Поиск 90: " << (tree.search(90) ? "найден ✓" : "не найден ✗") << std::endl;

    std::cout << "\n4. УДАЛЕНИЕ ЭЛЕМЕНТОВ:\n";

  

    std::cout << "\nв) Удаление элемента 30 (с двумя потомками):\n";
    tree.remove(30);
    tree.displayTree();
    

   

  
    // 

    return 0;
}