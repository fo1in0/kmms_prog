#include <iostream>

const int ARRAY_SIZE = 10

int main(){
    int  i, b;
    double a[10];
    for (i = 0; i < 10; i++)
    {
        std::cout << "Введите " << i << " элемент:" << endl;
        std::cin >> a[i];
    }
    b = 1;
    i = 1;
    while ((b = 1) && (i <= 10))
    {
        if (a[i] <= a[i + 1])
            b = 1;
        else if (a[i] > a[i + 1])
            b = 0;
        i++;
    }
    if (b == 1) {
        std::cout << "Последовательность возрастающая";
        std::cout << endl;
    }
    else if (b != 1) {
        std::cout << "Последовательность не возрастающая";
        std::cout << endl;
    }

    return 0;
}
