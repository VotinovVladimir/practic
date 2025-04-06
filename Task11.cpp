#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    int count;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

// Поиск ключа (итеративный)
int search(Node* root, int key) {
    Node* current = root;
    while(current != nullptr) {
        if(key == current->key) {
            return current->count;
        } else if(key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0;
}

// Рекурсивное добавление
Node* insert(Node*& node, int key) {
    if(node == nullptr) {
        return new Node(key);
    }
    if(key == node->key) {
        node->count++;
    } else if(key < node->key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }
    return node;
}

// Обход в симметричном порядке
void inOrder(Node* node, int level = 0) {
    if(node != nullptr) {
        inOrder(node->left, level + 1);
        cout << string(5 * level, ' ') 
             << node->key << "(" << node->count << ")" << endl;
        inOrder(node->right, level + 1);
    }
}

// Обход в обратно-симметричном порядке
void postOrder(Node* node, int level = 0) {
    if(node != nullptr) {
        postOrder(node->left, level + 1);
        postOrder(node->right, level + 1);
        cout << string(5 * level, ' ') 
             << node->key << "(" << node->count << ")" << endl;
    }
}

int main() {
    Node* root = nullptr;
    
    // Создание дерева из примера
    int keys[] = {40, 30, 20, 65};
    for(int key : keys) {
        root = insert(root, key);
    }
    
    // Добавление новой вершины
    root = insert(root, 67);
    
    // Поиск ключа
    int searchKey = 30;
    cout << "Key " << searchKey << " appears " 
         << search(root, searchKey) << " times\n";
    
    // Вывод дерева
    cout << "\nIn-order traversal:\n";
    inOrder(root);
    
    cout << "\nPost-order traversal:\n";
    postOrder(root);

    return 0;
}