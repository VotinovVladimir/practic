#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

int* generateArray(int size) {
    int* arr = new int[size];
    srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

void printArray(int* arr, int size) {
    if (size > 100) {
        cout << "Первые 100 элементов: ";
        for (int i = 0; i < 100; i++) {
            cout << arr[i] << " ";
        }
    } else {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << endl << endl;
}

int* bubbleSort(int* originalArr, int size, int& comparisons, int& swaps) {
    int* arr = new int[size];
    memcpy(arr, originalArr, size * sizeof(int));
    comparisons = 0;
    swaps = 0;
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return arr;
}

int* selectionSort(int* originalArr, int size, int& comparisons, int& swaps) {
    int* arr = new int[size];
    memcpy(arr, originalArr, size * sizeof(int));
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
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

void runTests() {
    int sizes[] = {10, 100, 1000, 10000};
    cout << "Размер | Метод          | Сравнения | Перестановки" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int size : sizes) {
        int* arr = generateArray(size);
        
        int compBubble, swapsBubble;
        int* sortedBubble = bubbleSort(arr, size, compBubble, swapsBubble);
        delete[] sortedBubble;
        
        int compSelection, swapsSelection;
        int* sortedSelection = selectionSort(arr, size, compSelection, swapsSelection);
        delete[] sortedSelection;
        
        delete[] arr;
        
        printf("%-6d | Bubble Sort    | %-9d | %-12d\n", size, compBubble, swapsBubble);
        printf("%-6d | Selection Sort | %-9d | %-12d\n", size, compSelection, swapsSelection);
        cout << "---------------------------------------------------" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int* originalArray = nullptr;
    int size = 0;
    int choice;
    
    do {
        cout << "Меню:" << endl;
        cout << "1. Сгенерировать новый массив" << endl;
        cout << "2. Выполнить сортировки текущего массива" << endl;
        cout << "3. Провести тесты на стандартных размерах" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите опцию: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                if (originalArray != nullptr) {
                    delete[] originalArray;
                }
                cout << "Введите размер массива (до 10000): ";
                cin >> size;
                if (size < 1 || size > 10000) {
                    cout << "Некорректный размер. Установлено значение 10." << endl;
                    size = 10;
                }
                originalArray = generateArray(size);
                cout << "Массив создан. ";
                if (size <= 100) {
                    cout << "Содержимое:" << endl;
                    printArray(originalArray, size); 
                } else {
                    cout << "Вывод содержимого пропущен из-за большого размера." << endl;
                }
                break;
            }
            case 2: {
                if (originalArray == nullptr) {
                    cout << "Сначала сгенерируйте массив." << endl;
                    break;
                }
                int compBubble, swapsBubble;
                int* sortedBubble = bubbleSort(originalArray, size, compBubble, swapsBubble);
                cout << "Пузырьковая сортировка:" << endl;
                cout << "Сравнений: " << compBubble << ", Перестановок: " << swapsBubble << endl;
                if (size <= 100) {
                    cout << "Отсортированный массив:" << endl;
                    printArray(sortedBubble, size);
                }
                delete[] sortedBubble;
                
                int compSelection, swapsSelection;
                int* sortedSelection = selectionSort(originalArray, size, compSelection, swapsSelection);
                cout << "Сортировка выбором:" << endl;
                cout << "Сравнений: " << compSelection << ", Перестановок: " << swapsSelection << endl;
                if (size <= 100) {
                    cout << "Отсортированный массив:" << endl;
                    printArray(sortedSelection, size);
                }
                delete[] sortedSelection;
                break;
            }
            case 3: {
                runTests();
                break;
            }
            case 4: {
                cout << "Завершение программы..." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор." << endl;
            }
        }
    } while (choice != 4);
    
    if (originalArray != nullptr) {
        delete[] originalArray;
    }
    return 0;
}