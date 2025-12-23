#include <gtest/gtest.h>
#include "bubble_sort.hpp"

TEST(BubbleSortTest, SortsArray) {
    int arr[] = {5, 3, 8, 1, 2};
    int expected[] = {1, 2, 3, 5, 8};
    bubble_sort(arr, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(BubbleSortTest, EmptyArray) {
    int arr[] = {};
    bubble_sort(arr, 0);
    SUCCEED();
}

TEST(BubbleSortTest, SingleElement) {
    int arr[] = {42};
    bubble_sort(arr, 1);
	EXPECT_EQ(arr[0], 42);
}