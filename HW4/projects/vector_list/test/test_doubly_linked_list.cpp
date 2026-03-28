#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using biv::DoublyLinkedList;

TEST(DoublyLinkedListTest, DefaultConstructor) {
	DoublyLinkedList<int> list;
	EXPECT_EQ(list.get_size(), 0);
}

TEST(DoublyLinkedListTest, PushBackAndGetSize) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	EXPECT_EQ(list.get_size(), 3);
}

TEST(DoublyLinkedListTest, HasItem) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	EXPECT_TRUE(list.has_item(20));
	EXPECT_FALSE(list.has_item(100));
}

TEST(DoublyLinkedListTest, RemoveFirstExisting) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	EXPECT_TRUE(list.remove_first(20));
	EXPECT_EQ(list.get_size(), 2);
	EXPECT_FALSE(list.has_item(20));
}

TEST(DoublyLinkedListTest, RemoveFirstNonExisting) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	EXPECT_FALSE(list.remove_first(100));
	EXPECT_EQ(list.get_size(), 3);
}

TEST(DoublyLinkedListTest, RemoveFirstFromBeginning) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	EXPECT_TRUE(list.remove_first(10));
	EXPECT_EQ(list.get_size(), 2);
	EXPECT_FALSE(list.has_item(10));
	EXPECT_TRUE(list.has_item(20));
	EXPECT_TRUE(list.has_item(30));
}

TEST(DoublyLinkedListTest, RemoveFirstFromEnd) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	EXPECT_TRUE(list.remove_first(30));
	EXPECT_EQ(list.get_size(), 2);
	EXPECT_TRUE(list.has_item(10));
	EXPECT_TRUE(list.has_item(20));
	EXPECT_FALSE(list.has_item(30));
}

TEST(DoublyLinkedListTest, RemoveFirstDuplicate) {
	DoublyLinkedList<int> list;

	list.push_back(20);
	EXPECT_TRUE(list.remove_first(20));
	EXPECT_EQ(list.get_size(), 0);

	list.push_back(20);
	list.push_back(10);	
	EXPECT_TRUE(list.remove_first(20));
	EXPECT_EQ(list.get_size(), 1);

	list.push_back(20);
	EXPECT_TRUE(list.remove_first(20));
	EXPECT_EQ(list.get_size(), 1);

	list.push_back(20);
	list.push_back(10);
	list.push_back(30);
	EXPECT_TRUE(list.remove_first(20));
	EXPECT_EQ(list.get_size(), 2);
	// Должен удалить первый 20, второй 20 должен остаться
	EXPECT_TRUE(list.has_item(20));

	list.push_back(20);
	EXPECT_TRUE(list.remove_first(20));
	EXPECT_EQ(list.get_size(), 2);
	// Должен удалить первый 20, второй 20 должен остаться
	EXPECT_TRUE(list.has_item(10));
	EXPECT_TRUE(list.has_item(30));

	list.push_back(20);
	EXPECT_TRUE(list.remove_first(10));
	EXPECT_EQ(list.get_size(), 2);
	// Должен удалить первый 20, второй 20 должен остаться
	EXPECT_TRUE(list.has_item(20));
}

TEST(DoublyLinkedListTest, MultiplePushBack) {
	DoublyLinkedList<int> list;
	for (int i = 0; i < 100; ++i) {
		list.push_back(i);
	}
	EXPECT_EQ(list.get_size(), 100);
}

TEST(DoublyLinkedListTest, RemoveAllElements) {
	DoublyLinkedList<int> list;
	list.push_back(10);
	list.push_back(20);
	list.push_back(30);
	
	list.remove_first(10);
	list.remove_first(20);
	list.remove_first(30);
	
	EXPECT_EQ(list.get_size(), 0);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}