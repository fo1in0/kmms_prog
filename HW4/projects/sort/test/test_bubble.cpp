#include <gtest/gtest.h>
#include "bubble_sort.hpp"

TEST(BubbleSortTest, SortsArray) {
    int arr[] = {5, 3, 8, 1, 2};
    bubble_sort(arr, 5);
    for (int i = 0; i < 4; i++) {
        EXPECT_LE(arr[i], arr[i+1]);
    }
}

TEST(BubbleSortTest, SingleElement) {
    int arr[] = {42};
    bubble_sort(arr, 1);
    EXPECT_EQ(arr[0], 42);
}

TEST(BubbleSortTest, EmptyArray) {
    int arr[] = {};
    bubble_sort(arr, 0);
    SUCCEED();  // Просто проверяем, что не падает
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}