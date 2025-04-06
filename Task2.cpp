#include <iostream>
#include <vector>
#include <string>
#include <clocale>

using namespace std; 

#define M 11 // Измените это значение для тестов (11, 13, 17)

int hash_code(const string& key) {
    int code = 0;
    for (char c : key) {
        code += static_cast<int>(c);
    }
    return code;
}

int insert_key(vector<string>& table, const string& key) {
    int comparisons = 0;
    int h = hash_code(key) % M;
    
    for (int i = 0; i < M; ++i) {
        int j = (h + i) % M;
        comparisons++;
        if (table[j].empty()) {
            table[j] = key;
            break;
        }
    }
    return comparisons;
}

pair<bool, int> search_key(const vector<string>& table, const string& key) {
    int comparisons = 0;
    int h = hash_code(key) % M;
    
    for (int i = 0; i < M; ++i) {
        int j = (h + i) % M;
        comparisons++;
        if (table[j].empty()) {
            return {false, comparisons};
        } else if (table[j] == key) {
            return {true, comparisons};
        }
    }
    return {false, comparisons};
}

void print_table(const vector<string>& table) {
    for (int i = 0; i < M; ++i) {
        cout << "[" << i << "]: ";
        if (table[i].empty()) cout << "Пусто";
        else cout << table[i];
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    vector<string> table(M, "");
    vector<string> keys = {
        "Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov",
        "Popov", "Volkov", "Fedorov", "Alexeev", "Nikolaev"
    };

    // Добавление ключей
    int total_insert = 0;
    for (const auto& key : keys) {
        int cmp = insert_key(table, key);
        total_insert += cmp;
        cout << "Добавлено '" << key << "' (" << cmp << " сравнений)" << endl;
    }

    // Вывод таблицы
    cout << "\nХеш-таблица (размер " << M << "):\n";
    print_table(table);
    

    // Поиск ключей
    int total_search = 0;
    for (const auto& key : keys) {
        auto result = search_key(table, key);
        total_search += result.second;
        cout << "Поиск '" << key << "': " 
             << (result.first ? "Найдено" : "Не найдено")
             << " (" << result.second << " сравнений)" << endl;
    }

    cout << "\nОбщее количество сравнений при вставке: " << total_insert << endl;
    cout << "Общее количество сравнений при поиске: " << total_search << endl;

    return 0;
}