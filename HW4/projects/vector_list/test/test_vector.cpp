#include <gtest/gtest.h>

#include "vector.hpp"

using biv::Vector;

TEST(VectorTest, DefaultConstructor) {
	Vector<int> vec;
	EXPECT_EQ(vec.get_size(), 0);
}

TEST(VectorTest, PushBackAndGetSize) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	EXPECT_EQ(vec.get_size(), 3);
}

TEST(VectorTest, HasItem) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	EXPECT_TRUE(vec.has_item(20));
	EXPECT_FALSE(vec.has_item(100));
}

TEST(VectorTest, InsertAtBeginning) {
	Vector<int> vec;
	vec.push_back(20);
	vec.push_back(30);
	
	EXPECT_TRUE(vec.insert(0, 10));
	EXPECT_EQ(vec.get_size(), 3);
	EXPECT_TRUE(vec.has_item(10));
}

TEST(VectorTest, InsertAtMiddle) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(30);
	
	EXPECT_TRUE(vec.insert(1, 20));
	EXPECT_EQ(vec.get_size(), 3);
	EXPECT_TRUE(vec.has_item(20));
}

TEST(VectorTest, InsertAtEnd) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	
	EXPECT_TRUE(vec.insert(2, 30));
	EXPECT_EQ(vec.get_size(), 3);
	EXPECT_TRUE(vec.has_item(30));
}

TEST(VectorTest, InsertInvalidPosition) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	
	EXPECT_FALSE(vec.insert(5, 30));
	EXPECT_EQ(vec.get_size(), 2);
}

TEST(VectorTest, RemoveFirstExisting) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	EXPECT_TRUE(vec.remove_first(20));
	EXPECT_EQ(vec.get_size(), 2);
	EXPECT_FALSE(vec.has_item(20));
}

TEST(VectorTest, RemoveFirstNonExisting) {
	Vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	EXPECT_FALSE(vec.remove_first(100));
	EXPECT_EQ(vec.get_size(), 3);
}

TEST(VectorTest, RemoveFirstDuplicate) {
	Vector<int> vec;
	vec.push_back(20);
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	
	EXPECT_TRUE(vec.remove_first(20));
	EXPECT_EQ(vec.get_size(), 3);
	EXPECT_TRUE(vec.has_item(20));
}

TEST(VectorTest, CapacityGrowth) {
	Vector<int> vec;
	for (int i = 0; i < 10; ++i) {
		vec.push_back(i);
	}
	EXPECT_EQ(vec.get_size(), 10);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}