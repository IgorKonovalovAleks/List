#include <gtest.h>
#include "List.h"

TEST(list, can_create_empty_list) {
	EXPECT_NO_THROW(List<int> a);
}

TEST(list, can_create_list_with_set_size) {
	EXPECT_NO_THROW(List<int> a(5));
}

TEST(list, can_create_list_from_node) {
	Node<int>* a = new Node<int>();
	EXPECT_NO_THROW(List<int> b(a));
}

TEST(list, can_create_list_from_initializer) {
	EXPECT_NO_THROW(List<int> a({1, 2, 3, 4}));
}

TEST(list, can_create_list_from_initializer_correctly) {
	List<int> a({ 1, 2, 3, 4 });
	auto it = a.first;
	for (int i : {1, 2, 3, 4}) {
		if (i != it->value)
			ADD_FAILURE();
		it = it->next;
	}
	SUCCEED();
}

TEST(list, can_copy_list) {
	List<int> a(2);
	EXPECT_NO_THROW(List<int> b(a));
}

TEST(list, copied_list_equals_to_the_source_one) {
	List<int> a({ 1, 2, 3 });
	List<int> b(a);
	EXPECT_EQ(a, b);
}

TEST(list, can_move_list) {
	List<int> a({ 1, 2, 3 });
	EXPECT_NO_THROW(List<int> b = std::move(a));
}

TEST(list, can_take_iterator) {
	List<int> a({ 1, 2, 3 });
	EXPECT_NO_THROW(List<int>::Iterator it = a.begin());
}

TEST(list, can_iterate_on_the_list) {
	List<int> a({ 1, 2, 3 });
	auto it = a.begin();
	for (int i : {1, 2, 3}) {
		if (i != it.ptr->value)
			ADD_FAILURE();
		++it;
	}
	SUCCEED();
}

TEST(list, insertion_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.insert(1, 2);
	EXPECT_EQ(List<int>({ 1, 2, 2, 3 }), a);
}

TEST(list, erasion_by_position_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.erase(1);
	EXPECT_EQ(List<int>({ 1, 3 }), a);
}

TEST(list, erasion_by_iterator_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.erase(a.begin());
	EXPECT_EQ(List<int>({ 1, 3 }), a);
}

TEST(list, pushing_back_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.push_back(2);
	EXPECT_EQ(List<int>({ 1, 2, 3, 2 }), a);
}

TEST(list, pushing_front_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.push_front(2);
	EXPECT_EQ(List<int>({ 2, 1, 2, 3 }), a);
}

TEST(list, popping_back_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.pop_back();
	EXPECT_EQ(List<int>({ 1, 2 }), a);
}

TEST(list, popping_front_works_correctly) {
	List<int> a({ 1, 2, 3 });
	a.pop_front();
	EXPECT_EQ(List<int>({ 2, 3 }), a);
}

TEST(list, popping_back_returns_correct_value) {
	List<int> a({ 1, 2, 3 });
	int i = a.pop_back();
	EXPECT_EQ(3, i);
}

TEST(list, popping_front_returns_correct_value) {
	List<int> a({ 1, 2, 3 });
	int i = a.pop_front();
	EXPECT_EQ(1, i);
}