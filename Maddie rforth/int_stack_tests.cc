//
// Created by George Thiruvathukal on 2/17/24.
//

#include <gtest/gtest.h>

#include "int_stack.hh"

TEST(IntStackTests, Initialization)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}

TEST(IntStackTests, PushToCapacityAndOverflow)
{
    // create stack that can hold 10 items
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // ensure it's full
    ASSERT_EQ(int_stack_size(&stack1), capacity);

    // try to add one more
    int result = int_stack_push(&stack1, capacity+1);

    // and make sure it is an overflow (error)
    ASSERT_FALSE(result);
}


TEST(IntStackTests, PushToCapcacityPopUntilUnderflow
)
{
    // create stack that can hold 10 items [similar to previous test]
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}


TEST(IntStackTests, AdditionOperation) {
    // Create stack that can hold 4 items
    int_stack_t stack1;
    const int capacity = 4;
    int_stack_init(&stack1, capacity);

    // Fill it with specific values
    for (int i = 1; i <= capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    
    int expected_sum = 10;


    for (int i = 0; i < 2; i++) { 
        int value1, value2;
        ASSERT_TRUE(int_stack_pop(&stack1, &value1));
        ASSERT_TRUE(int_stack_pop(&stack1, &value2));

        int sum = value1 + value2; 
        ASSERT_TRUE(int_stack_push(&stack1, sum)); 
    }
    int sum1, sum2, final_sum;
    ASSERT_TRUE(int_stack_pop(&stack1, &sum1));
    ASSERT_TRUE(int_stack_pop(&stack1, &sum2));
    final_sum = sum1 + sum2;

    ASSERT_EQ(final_sum, expected_sum);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}


TEST(IntStackTests, LessThanComparison) {
    int_stack_t stack1;
    const int capacity = 2;
    int_stack_init(&stack1, capacity);

    int values[2] = {1, 4};
    for (int i = 0; i < capacity; i++) {
        int_stack_push(&stack1, values[i]);
    }

    int comparisonResult = int_stack_less(&stack1);
    int_stack_push(&stack1, comparisonResult);

    int finalResult;
    int_stack_pop(&stack1, &finalResult);

    int expectedComparisonResult = (values[0] < values[1]) ? -1 : 0;
    ASSERT_EQ(finalResult, expectedComparisonResult);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}


TEST(IntStackTests, GreaterThanComparison) {
    int_stack_t stack1;
    const int capacity = 2;
    int_stack_init(&stack1, capacity);

    int values[2] = {1, 4};
    for (int i = 0; i < capacity; i++) {
        int_stack_push(&stack1, values[i]);
    }

    int comparisonResult = int_stack_greater(&stack1);
    int_stack_push(&stack1, comparisonResult);

    int finalResult;
    int_stack_pop(&stack1, &finalResult);

    int expectedComparisonResult = (values[0] > values[1]) ? -1 : 0;
    ASSERT_EQ(finalResult, expectedComparisonResult);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, EqualComparison) {
    int_stack_t stack1;
    const int capacity = 2;
    int_stack_init(&stack1, capacity);

    int values[2] = {1, 4};
    for (int i = 0; i < capacity; i++) {
        int_stack_push(&stack1, values[i]);
    }

    int comparisonResult = int_stack_equal(&stack1);
    int_stack_push(&stack1, comparisonResult);

    int finalResult;
    int_stack_pop(&stack1, &finalResult);

    int expectedComparisonResult = (values[0] == values[1]) ? -1 : 0;
    ASSERT_EQ(finalResult, expectedComparisonResult);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, AndComparison) {
    int_stack_t stack1;
    const int capacity = 4;
    int_stack_init(&stack1, capacity);

    int values[4] = {10, 20, 40, 30};
    for (int i = 0; i < capacity; i++) {
        int_stack_push(&stack1, values[i]);
    }

    int s3, s4;
    int_stack_pop(&stack1, &s4);
    int_stack_pop(&stack1, &s3);
    int res1 = (s3 > s4) ? -1 : 0;
    int_stack_push(&stack1, res1);

    int s1, s2;
    int_stack_pop(&stack1, &s2);
    int_stack_pop(&stack1, &s1);
    int res2 = (s1 > s2) ? -1 : 0; 
    int_stack_push(&stack1, res2);

    int comparisonResult = int_stack_and(&stack1);

    int finalResult;
    int_stack_pop(&stack1, &finalResult);

    int expectedComparisonResult = (values[0] < values[1] && values[2] < values[3]) ? -1 : 0;
    ASSERT_EQ(finalResult, expectedComparisonResult);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, OrComparison) {
    int_stack_t stack1;
    const int capacity = 4;
    int_stack_init(&stack1, capacity);

    int values[4] = {10, 20, 40, 30};
    for (int i = 0; i < capacity; i++) {
        int_stack_push(&stack1, values[i]);
    }

    int s3, s4;
    int_stack_pop(&stack1, &s4);
    int_stack_pop(&stack1, &s3);
    int res1 = (s3 > s4) ? -1 : 0;
    int_stack_push(&stack1, res1);

    int s1, s2;
    int_stack_pop(&stack1, &s2);
    int_stack_pop(&stack1, &s1);
    int res2 = (s1 < s2) ? -1 : 0; 
    int_stack_push(&stack1, res2);

    int comparisonResult = int_stack_or(&stack1);

    int finalResult;
    int_stack_pop(&stack1, &finalResult);

    int expectedComparisonResult = (values[0] > values[1] || values[2] < values[3]) ? -1 : 0;
    ASSERT_EQ(finalResult, expectedComparisonResult);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, Invert) {
    int_stack_t stack1;
    const int capacity = 2;
    int_stack_init(&stack1, capacity);

    int values[2] = {10, 20};
    for (int i = 0; i < capacity; i++) {
        int_stack_push(&stack1, values[i]);
    }

    int s1, s2;
    int_stack_pop(&stack1, &s2);
    int_stack_pop(&stack1, &s1);
    int res2 = (s1 < s2) ? -1 : 0; 
    int_stack_push(&stack1, res2);

    int comparisonResult = int_stack_invert(&stack1);

    int finalResult;
    int_stack_pop(&stack1, &finalResult);

    int expectedComparisonResult = !(values[0] < values[1]) ? -1 : 0;
    ASSERT_EQ(finalResult, expectedComparisonResult);

    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
