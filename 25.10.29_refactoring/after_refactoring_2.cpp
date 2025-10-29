#include <iostream>

int main() {
	const int array_size = 10;
    double numbers[array_size];
	
	for (int i = 0; i < array_size; i++) {
		std::cout << "Введите" << i + 1 << " элемент массива:";
		std::cin >> numbers[i];
	}
    bool isIncreasing = true;
    
    for (int i = 0; i < array_size - 1; i++) {
        if (numbers[i] >= numbers[i + 1]) {
            isIncreasing = false;
            break;
        }
    }

    if (isIncreasing){
        std::cout << "Последовательность является возрастающей" << std::endl;
    }
    else{
        std::cout << "Последовательность не является возрастающей" << std::endl;
    }

    return 0;
}