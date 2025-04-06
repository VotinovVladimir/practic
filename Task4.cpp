#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std; 

// Функция разделения массива
int partition(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
    int pivot = arr[high]; // Опорный элемент (последний)
    int i = low - 1;       // Индекс для элементов меньше опорного

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swaps++;
        }
    }

    swap(arr[i + 1], arr[high]);
    swaps++;
    return i + 1;
}

// Рекурсивная быстрая сортировка
void quickSort(vector<int>& arr, int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

// Генерация массива случайных чисел
vector<int> generateArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // Числа от 0 до 999
    }
    return arr;
}

// Вывод результатов
void printStats(const vector<int>& arr, int comparisons, int swaps) {
    cout << "Размер массива: " << arr.size() << endl;
    cout << "Сравнений: " << comparisons << endl;
    cout << "Пересылок: " << swaps << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    vector<int> sizes = {10, 100, 1000, 10000};

    for (int size : sizes) {
        vector<int> arr = generateArray(size);
        vector<int> arrCopy = arr; // Копия для сортировки

        int comparisons = 0, swaps = 0;
        quickSort(arrCopy, 0, arrCopy.size() - 1, comparisons, swaps);

        printStats(arrCopy, comparisons, swaps);
    }

    return 0;
}