#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Генерация массива случайных чисел
vector<int> generateArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // числа от 0 до 999
    }
    return arr;
}

// Вывод массива (для размеров <= 100)
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Сортировка пузырьком
vector<int> bubbleSort(vector<int> arr, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break; // оптимизация для раннего выхода
    }
    return arr;
}

// Сортировка выбором
vector<int> selectionSort(vector<int> arr, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            swaps++;
        }
    }
    return arr;
}

int main() {
    srand(time(0));
    int size, choice;

    cout << "Введите размер массива (10, 100, 1000, 10000): ";
    cin >> size;
    if (size <= 0 || size > 10000) {
        cout << "Некорректный размер!" << endl;
        return 1;
    }

    vector<int> original = generateArray(size);

    cout << "\nИсходный массив (" << size << " элементов):" << endl;
    if (size <= 100) printArray(original);
    else cout << "Массив слишком большой для вывода." << endl;

    cout << "\nВыберите метод сортировки:\n1. Пузырьковая\n2. Выбором\n> ";
    cin >> choice;

    int comparisons = 0, swaps = 0;
    vector<int> sorted;

    switch (choice) {
        case 1:
            sorted = bubbleSort(original, comparisons, swaps);
            break;
        case 2:
            sorted = selectionSort(original, comparisons, swaps);
            break;
        default:
            cout << "Некорректный выбор!" << endl;
            return 1;
    }

    cout << "\nРезультаты сортировки:" << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Пересылок: " << swaps << endl;

    if (size <= 100) {
        cout << "\nОтсортированный массив:" << endl;
        printArray(sorted);
    }

    return 0;
}