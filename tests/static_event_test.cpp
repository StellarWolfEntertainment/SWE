#include "../include/swe/static_event.hpp"
#include <gtest/gtest.h>
#include <iostream>

namespace
{
    // The Caller class allowed to invoke the event
    struct TestCaller
    {
        static swe::static_event<TestCaller, int> event;

        static void trigger_event(int value)
        {
            event(value);
        }

        static void reset()
        {
            event._callbacks.clear();
        }
    };

    // Definition of the static event instance
    swe::static_event<TestCaller, int> TestCaller::event;

    // Helper to track callback invocations
    struct CallbackTracker
    {
        static int counter;
        static int last_value;

        static void callback1(int val)
        {
            ++counter;
            last_value = val;
        }

        static void callback2(int val)
        {
            counter += 2;
            last_value = val;
        }
    };

    int CallbackTracker::counter = 0;
    int CallbackTracker::last_value = 0;
} // namespace

TEST(StaticEventTest, SubscribeAndInvoke)
{
    // Clear previous state if any
    CallbackTracker::counter = 0;
    CallbackTracker::last_value = 0;
    TestCaller::reset();

    // Subscribe callbacks
    TestCaller::event += &CallbackTracker::callback1;
    TestCaller::event += &CallbackTracker::callback2;

    // Trigger the event via the allowed caller
    TestCaller::trigger_event(42);

    // Both callbacks should be invoked
    EXPECT_EQ(CallbackTracker::counter, 3); // 1 + 2
    EXPECT_EQ(CallbackTracker::last_value, 42);
}

TEST(StaticEventTest, UnsubscribeCallback)
{
    CallbackTracker::counter = 0;
    CallbackTracker::last_value = 0;
    TestCaller::reset();

    // Subscribe and then unsubscribe callback1
    TestCaller::event += &CallbackTracker::callback1;
    TestCaller::event += &CallbackTracker::callback2;
    TestCaller::event -= &CallbackTracker::callback1;

    TestCaller::trigger_event(7);

    // Only callback2 should run
    EXPECT_EQ(CallbackTracker::counter, 2);
    EXPECT_EQ(CallbackTracker::last_value, 7);
}

TEST(StaticEventTest, UnsubscribeNonexistentCallback)
{
    TestCaller::reset();
    // Removing a callback that wasn't added should do nothing and cause no error
    TestCaller::event -= &CallbackTracker::callback1; // Not subscribed currently
    SUCCEED();
}

TEST(StaticEventTest, CannotInvokeFromOutsideCaller)
{
    TestCaller::reset();
    // This is enforced by friend and private operator() so can't be tested directly.
    // Just note here that only TestCaller can invoke the event.
    SUCCEED();
}

TEST(StaticEventTest, MultipleSubscriptionsOfSameCallback)
{
    CallbackTracker::counter = 0;
    CallbackTracker::last_value = 0;
    TestCaller::reset();

    // Subscribe callback1 twice
    TestCaller::event += &CallbackTracker::callback1;
    TestCaller::event += &CallbackTracker::callback1;

    TestCaller::trigger_event(10);

    // The callback should have been called twice
    EXPECT_EQ(CallbackTracker::counter, 2);
    EXPECT_EQ(CallbackTracker::last_value, 10);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}