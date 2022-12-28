#include <gtest.h>
#include "LStack.h"
#include "LQueue.h"

TEST(lstack, can_create_empty_stack) {
	EXPECT_NO_THROW(List<int> a);
}

TEST(lstack, can_copy_stack) {
	LStack<int> a;
	a.push(1);
	a.push(2);
	EXPECT_NO_THROW(LStack<int> b(a));
}

TEST(lstack, copied_stack_is_equal_to_source_one) {
	LStack<int> a;
	a.push(1);
	a.push(2);
	LStack<int> b(a);
	if (b.getTop() != a.getTop())
		ADD_FAILURE();
	a.pop();
	b.pop();
	if (b.getTop() != a.getTop())
		ADD_FAILURE();
	SUCCEED();
}

TEST(lstack, popping_works_correctly) {
	LStack<int> a;
	a.push(4);
	a.push(3);
	a.pop();

	EXPECT_EQ(4, a.getTop());
}

TEST(lstack, pushing_works_correctly) {
	LStack<int> a;
	a.push(1);
	EXPECT_EQ(1, a.getTop());
}

TEST(lstack, size_is_calculated_correctly) {
	LStack<int> a;
	a.push(1);
	a.push(2);
	a.pop();
	a.push(3);
	EXPECT_EQ(2, a.getSize());
}

TEST(lQueue, push_back_works_correctly) {
	LQueue<int> a;
	a.push(1);
	a.push(2);
	EXPECT_EQ(1, a.getTop());
}

