#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct Node {
    int key;
    int count;
    Node* left;
    Node* right;
    Node(int k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

void insert(Node*& node, int key) {
    if (node == nullptr) {
        node = new Node(key);
    } else if (key == node->key) {
        node->count++;
    } else if (key < node->key) {
        insert(node->left, key);
    } else {
        insert(node->right, key);
    }
}

void search(Node* root, int key) {
    Node* current = root;
    while (current != nullptr) {
        if (current->key == key) {
            cout << "Количество: " << current->count << endl;
            return;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << "Ключ не найден." << endl;
}

void printInOrder(Node* node, int level) {
    if (node == nullptr) return;
    printInOrder(node->left, level + 1);
    cout << string(level * 5, ' ') << node->key << " (" << node->count << ")" << endl;
    printInOrder(node->right, level + 1);
}

void printReverseInOrder(Node* node, int level) {
    if (node == nullptr) return;
    printReverseInOrder(node->right, level + 1);
    cout << string(level * 5, ' ') << node->key << " (" << node->count << ")" << endl;
    printReverseInOrder(node->left, level + 1);
}

void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    Node* root = nullptr;
    int choice;
    do {
        cout << "1. Создать дерево с N случайными ключами\n";
        cout << "2. Добавить узел с определенным ключом\n";
        cout << "3. Поиск ключа\n";
        cout << "4. Вывести дерево в порядке in-order\n";
        cout << "5. Вывести дерево в обратном порядке in-order\n";
        cout << "0. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int N;
                cout << "Ввод N: ";
                cin >> N;
                for (int i = 0; i < N; ++i) {
                    int key = rand() % 100;
                    insert(root, key);
                }
                break;
            }
            case 2: {
                int key;
                cout << "Введите ключ для добавления: ";
                cin >> key;
                insert(root, key);
                break;
            }
            case 3: {
                int key;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                search(root, key);
                break;
            }
            case 4: {
                cout << "Обход в порядке in-order: \n";
                printInOrder(root, 0);
                break;
            }
            case 5: {
                cout << "Обратный обход в порядке in-order: \n";
                printReverseInOrder(root, 0);
                break;
            }
            case 0: {
                break;
            }
            default: {
                cout << "Неверный выбор.";
            }
        }
    } while (choice != 0);

    deleteTree(root);
    root = nullptr;

    return 0;
}
