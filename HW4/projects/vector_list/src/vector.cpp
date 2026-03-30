#include "vector.hpp"
#include <iostream>

namespace biv {


template<typename T>
Vector<T>::Vector() : arr(nullptr), size(0), capacity(0) {}


template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	arr = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
    if (position > size) {
        return false;
    }

    if (size >= capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_arr = new T[capacity];
        for (std::size_t i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }
    
	for (std::size_t i = size; i > position; --i) {
        arr[i] = arr[i - 1];
    }
    
    arr[position] = value;
    ++size;
    return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	std::cout << "[";
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << arr[i];
		if (i < size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	insert(size, value);
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            for (std::size_t j = i; j < size - 1; ++j) {
                arr[j] = arr[j + 1];
            }
            --size;
            
            if (size < capacity / 4 && capacity > 4) {
                std::size_t new_capacity = capacity / 2;
                
                if (new_capacity < 4) new_capacity = 4;
                if (new_capacity < size) new_capacity = size;
                
                T* new_arr = new T[new_capacity];
                
                for (std::size_t j = 0; j < size; ++j) {
                    new_arr[j] = arr[j];
                }
                
                delete[] arr;
                arr = new_arr;
                capacity = new_capacity;
            }
            
            return true;
        }
    }
    return false;
}

} // namespace biv