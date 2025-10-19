#include <iostream>

const int ARRAY_SIZE = 10;
const int RANDOM_RANGE = 10;

void printArray(const float array[], int size, const char* arrayName) {
    std::cout << arrayName << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

float calculateAverage(const float array[], int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

void fillArrayWithRandomValues(float array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % RANDOM_RANGE;
    }
}

void Execution(const char* sequenceName) {
    float array[ARRAY_SIZE];
    
    fillArrayWithRandomValues(array, ARRAY_SIZE);
    printArray(array, ARRAY_SIZE, sequenceName);
    
    const float average = calculateAverage(array, ARRAY_SIZE);
    std::cout << sequenceName <<" Cреднее значение = " << average << std::endl;
    std::cout << std::endl;
}

int main() {
    Execution("Первая последовательность:");
    Execution("Вторая последовательность:");
    Execution("Третья последовательность:");

    return 0;
}


/*Я вынес всё, что было в main, в отдельную функцию 
 и передаю ей только название нужной последовательности.
*/