#include "long_number.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using bvs::LongNumber;
using namespace std;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 0;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) {
	this->length = length;
	this->sign = sign;
	numbers = new int[length];	
	for(int i = 0; i < length; i++){
		this->numbers[i] = 0;
	}
}

LongNumber::LongNumber(const char* const str) {
	numbers = nullptr;
	length = 0;
	sign = 0;
	create_from_str(str);
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];

	for(int i = 0; i < length; i++){
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	this->length = x.length;
	this->sign = x.sign;
	this->numbers = x.numbers;

	x.length = 0;
	x.sign = 0;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
	delete[] numbers;
	numbers = nullptr;
	create_from_str(str);
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) return *this;
	delete[] numbers;

	length = x.length;
	sign = x.sign;
	numbers = new int[length];

	for(int i = 0; i < length; i++){
		numbers[i] = x.numbers[i];
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if(this == &x) return *this;
	delete[] numbers;

	this->length = x.length;
	this->sign = x.sign;
	this->numbers = x.numbers;

	x.length = 0;
	x.sign = 0;
	x.numbers = nullptr;

	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if(this == &x) return true;
	if(this->sign != x.sign) return false;
	if(this->length != x.length) return false;

	for(int i = 0; i < this->length; i++){
		if(this->numbers[i] != x.numbers[i]){
			return false;
		}
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
    if (this->sign != x.sign) {
        return this->sign > x.sign;
    }
    
    if (this->sign == 0) return false;
    
    if (this->length != x.length) {
        if (this->sign > 0) {
            return this->length > x.length;
        } else {
            return this->length < x.length;
        }
    }
    
    for (int i = 0; i < this->length; i++) {
        if (this->numbers[i] != x.numbers[i]) {
            if (this->sign > 0) {
                return this->numbers[i] > x.numbers[i];
            } else {
                return this->numbers[i] < x.numbers[i];
            }
        }
    }
    
    return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return (x > *this);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (this->sign == 0) return x;
    if (x.sign == 0) return *this;

    if (this->sign == x.sign) {
        LongNumber result = plus_modules(*this, x);
        result.sign = this->sign;
        return result;
    }

    int cmp = this->compare(x);
    if (cmp == 0) return LongNumber("0");
    
    LongNumber result = minus_modules(*this, x);
    if (cmp == 1) {
        result.sign = this->sign;
    } else {
        result.sign = x.sign;
    }
    return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if (x.sign == 0) return *this;
    if (this->sign == 0) {
        LongNumber result = x;
        result.sign = -x.sign;
        return result;
    }

    if (this->sign != x.sign) {
        LongNumber result = plus_modules(*this, x);
        result.sign = this->sign;
        return result;
    }

    int cmp = this->compare(x);
    if (cmp == 0) return LongNumber("0");
    
    LongNumber result = minus_modules(*this, x);
    
    if ((this->sign == 1 && cmp == 1) || (this->sign == -1 && cmp == -1)) {
        result.sign = 1;
    } else {
        result.sign = -1;
    }
    
    return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	if (this->sign == 0 || x.sign == 0) return LongNumber("0");

    int* a = new int[length];
    int* b = new int[x.length];
    
    for (int i = 0; i < length; i++) {
        a[i] = numbers[i];
    }
    for (int i = 0; i < x.length; i++) {
        b[i] = x.numbers[i];
    }

	int len_a = this->length;
	int len_b = x.length;
	
	std::reverse(a, a + len_a);
	std::reverse(b, b + len_b);
	
	int len_c = len_a + len_b;
	int* c = new int[len_c]();
	
	int sign_c = (this->sign == x.sign) ? 1 : -1;

	for (int i = 0; i < len_a; i++){
        for (int j = 0; j < len_b; j++){
            c[i + j] += a[i] * b[j];
        }
    }
    
    for (int i = 0; i < len_c - 1; i++){
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

	while (len_c > 1 && c[len_c - 1] == 0) {
        len_c--;
    }

    string result_str;
    for (int i = len_c - 1; i >= 0; i--) {
        result_str += to_string(c[i]);
    }

    delete[] a;
    delete[] b;
    delete[] c;

    LongNumber result(result_str.c_str());
    if (result_str != "0") {
        result.sign = sign_c;
    }
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x.sign == 0) return LongNumber("0");
    if (this->sign == 0) return LongNumber("0");

    // Определяем знак результата
    bool result_negative = (this->sign != x.sign);
    
    // Работаем с абсолютными значениями
    LongNumber dividend = *this;
    LongNumber divisor = x;
    dividend.sign = 1;
    divisor.sign = 1;
    
    if (dividend.compare(divisor) == -1) {
        LongNumber result("0");
        // Если делимое не ноль и оба числа отрицательные, то -1
        if (this->sign == -1 && x.sign == -1 && dividend != LongNumber("0")) {
            result.sign = -1;
            result = LongNumber("1");
        }
        return result;
    }
    
    LongNumber result("0");
    LongNumber current("0");
    
    for (int i = 0; i < dividend.length; i++) {
        if (!(current.length == 1 && current.numbers[0] == 0)) {
            int* new_digits = new int[current.length + 1];
            for (int j = 0; j < current.length; j++) {
                new_digits[j] = current.numbers[j];
            }
            new_digits[current.length] = dividend.numbers[i];
            delete[] current.numbers;
            current.numbers = new_digits;
            current.length++;
        } else {
            delete[] current.numbers;
            current.length = 1;
            current.numbers = new int[1];
            current.numbers[0] = dividend.numbers[i];
        }
        
        int digit = 0;
        while (current.compare(divisor) >= 0) {
            current = minus_modules(current, divisor);
            digit++;
        }
        
        if (result.length == 1 && result.numbers[0] == 0 && digit == 0) {
            continue;
        }
        
        if (result.length == 1 && result.numbers[0] == 0) {
            delete[] result.numbers;
            result.length = 1;
            result.numbers = new int[1];
            result.numbers[0] = digit;
        } else {
            int* new_digits = new int[result.length + 1];
            for (int j = 0; j < result.length; j++) {
                new_digits[j] = result.numbers[j];
            }
            new_digits[result.length] = digit;
            delete[] result.numbers;
            result.numbers = new_digits;
            result.length++;
        }
    }
    
    bool has_remainder = !(current.length == 1 && current.numbers[0] == 0);
    
    if (result.length == 1 && result.numbers[0] == 0) {
        result.sign = 0;
        return result;
    }
    
    // Корректировка только когда оба числа отрицательные и есть остаток
    if (this->sign == -1 && x.sign == -1 && has_remainder) {
        LongNumber one("1");
        result = plus_modules(result, one);
        result.sign = 1;
    } else if (this->sign == -1 && x.sign == 1 && has_remainder) {
        // Для отрицательного делимого и положительного делителя
        LongNumber one("1");
        result = plus_modules(result, one);
        result.sign = -1;
    } else {
        result.sign = result_negative ? -1 : 1;
    }
    
    return result;
}
LongNumber LongNumber::operator % (const LongNumber& x) const {
    if (x.sign == 0) return LongNumber("0");
    
    LongNumber quotient = *this / x;
    LongNumber product = quotient * x;
    LongNumber remainder = *this - product;
    
    if (remainder.sign == -1) {
        if (x.sign == 1) {
            remainder = remainder + x;
        } else {
            LongNumber positive_x = x;
            positive_x.sign = 1;
            remainder = remainder + positive_x;
        }
    }
    
    if (remainder.compare(LongNumber("0")) == 0) {
        remainder.sign = 0;
    }
    
    return remainder;
}

bool LongNumber::is_negative() const noexcept {
	return (sign == -1);
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int result = 0;
	int start = 0;
	if (str[0] == '-'){
		start = 1; 
	}

	for (int i = start; str[i] != '\0'; i++){
		result++;
	}

	return result;
}

void LongNumber::create_from_str(const char* const str){
    delete[] numbers;
    numbers = nullptr;
    length = 0;
    sign = 0;
    
    int start = 0;
    if (str[0] == '-') {
        sign = -1;
        start = 1;
    } else if (str[0] == '+') {
        sign = 1;
        start = 1;
    } else {
        sign = 1;
        start = 0;
    }
    
    int str_len = strlen(str);
    while (start < str_len && str[start] == '0') {
        start++;
    }
    
    if (start == str_len) {
        sign = 0;
        length = 1;
        numbers = new int[1];
        numbers[0] = 0;
        return;
    }
    
    length = str_len - start;
    numbers = new int[length];
    
    for (int i = 0; i < length; ++i) {
        numbers[i] = str[start + i] - '0';
    }
}

int LongNumber::compare(const LongNumber& other) const {
    if (this->length > other.length) return 1;
    if (this->length < other.length) return -1;
    
    for (int i = 0; i < this->length; i++) {
        if (this->numbers[i] > other.numbers[i]) return 1;
        if (this->numbers[i] < other.numbers[i]) return -1;
    }
    return 0;
}

LongNumber LongNumber::plus_modules(const LongNumber& a, const LongNumber& b) const {

    int len_a = a.length;
    int len_b = b.length;
    int* a_digits = new int[len_a];
    int* b_digits = new int[len_b];
    
    for (int i = 0; i < len_a; i++) a_digits[i] = a.numbers[i];
    for (int i = 0; i < len_b; i++) b_digits[i] = b.numbers[i];

    std::reverse(a_digits, a_digits + len_a);
    std::reverse(b_digits, b_digits + len_b);

    if (len_a < len_b) {
        swap(a_digits, b_digits);
        swap(len_a, len_b);
    }

    int result_len = len_a + 1;
    int* result = new int[result_len]();

    for (int i = 0; i < len_a; i++) {
        result[i] = a_digits[i];
    }

    for (int i = 0; i < len_b; i++) {
        result[i] += b_digits[i];
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    for (int i = 0; i < result_len - 1; i++) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    while (result_len > 1 && result[result_len - 1] == 0) {
        result_len--;
    }

    string result_str;
    for (int i = result_len - 1; i >= 0; i--) {
        result_str += to_string(result[i]);
    }
    
    delete[] a_digits;
    delete[] b_digits;
    delete[] result;
    
    return LongNumber(result_str.c_str());
}

LongNumber LongNumber::minus_modules(const LongNumber& a, const LongNumber& b) const {
    int cmp = a.compare(b);

    if (cmp == 0) return LongNumber("0");

    int len_a = a.length;
    int len_b = b.length;
    int* a_digits = new int[len_a];
    int* b_digits = new int[len_b];
    
    for (int i = 0; i < len_a; i++) a_digits[i] = a.numbers[i];
    for (int i = 0; i < len_b; i++) b_digits[i] = b.numbers[i];

    std::reverse(a_digits, a_digits + len_a);
    std::reverse(b_digits, b_digits + len_b);

    bool a_bigger = (cmp == 1);
    if (!a_bigger) {
        swap(a_digits, b_digits);
        swap(len_a, len_b);
    }

    for (int i = 0; i < len_b; i++) {
        if (a_digits[i] < b_digits[i]) {
            int j = i + 1;
            while (j < len_a && a_digits[j] == 0) j++;
            if (j < len_a) {
                a_digits[j]--;
                for (int k = j - 1; k > i; k--) {
                    a_digits[k] = 9;
                }
                a_digits[i] += 10;
            }
        }
        a_digits[i] -= b_digits[i];
    }

    while (len_a > 1 && a_digits[len_a - 1] == 0) {
        len_a--;
    }
    
    string result_str;
    for (int i = len_a - 1; i >= 0; i--) {
        result_str += to_string(a_digits[i]);
    }
    
    delete[] a_digits;
    delete[] b_digits;
    
    return LongNumber(result_str.c_str());
}
// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace bvs {
	ostream& operator << (std::ostream &os, const LongNumber& x) {
		if(x.sign == 0){
			os << "0";
			return os;
		}
		if(x.sign == -1){
			os << "-";
		}
		for(int i = 0; i < x.length; i++){
			os << x.numbers[i];
		}
		return os;
	}
}