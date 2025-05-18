#include "../include/swe/concurrent_static_event.hpp"
#include <atomic>
#include <chrono>
#include <gtest/gtest.h>
#include <thread>
#include <vector>

namespace
{
    struct TestCaller
    {
        static swe::concurrent_static_event<TestCaller, int> event;

        static void trigger_event(int value)
        {
            event(value);
        }

        static void reset()
        {
            event._callbacks.clear();
        }
    };

    swe::concurrent_static_event<TestCaller, int> TestCaller::event;

    struct CallbackTracker
    {
        static std::atomic<int> counter;
        static std::atomic<int> last_value;

        static void callback1(int val)
        {
            counter.fetch_add(1, std::memory_order_relaxed);
            last_value.store(val, std::memory_order_relaxed);
        }

        static void callback2(int val)
        {
            counter.fetch_add(2, std::memory_order_relaxed);
            last_value.store(val, std::memory_order_relaxed);
        }
    };

    std::atomic<int> CallbackTracker::counter{0};
    std::atomic<int> CallbackTracker::last_value{0};
} // namespace

TEST(ConcurrentStaticEventTest, BasicSubscribeInvoke)
{
    CallbackTracker::counter = 0;
    CallbackTracker::last_value = 0;
    TestCaller::reset();

    TestCaller::event += &CallbackTracker::callback1;
    TestCaller::event += &CallbackTracker::callback2;

    TestCaller::trigger_event(42);

    EXPECT_GE(CallbackTracker::counter.load(), 3);
    EXPECT_EQ(CallbackTracker::last_value.load(), 42);
}

TEST(ConcurrentStaticEventTest, Unsubscribe)
{
    CallbackTracker::counter = 0;
    CallbackTracker::last_value = 0;
    TestCaller::reset();

    TestCaller::event += &CallbackTracker::callback1;
    TestCaller::event += &CallbackTracker::callback2;
    TestCaller::event -= &CallbackTracker::callback1;

    TestCaller::trigger_event(7);

    EXPECT_EQ(CallbackTracker::counter.load(), 2);
    EXPECT_EQ(CallbackTracker::last_value.load(), 7);
}

TEST(ConcurrentStaticEventTest, ConcurrentSubscribeUnsubscribe)
{
    CallbackTracker::counter = 0;
    CallbackTracker::last_value = 0;
    TestCaller::reset();

    auto subscribe_fn = []()
    {
        for (int i = 0; i < 1000; ++i)
        {
            TestCaller::event += &CallbackTracker::callback1;
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            TestCaller::event -= &CallbackTracker::callback1;
        }
    };

    auto invoke_fn = []()
    {
        for (int i = 0; i < 1000; ++i)
        {
            TestCaller::trigger_event(i);
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    };

    std::thread t1(subscribe_fn);
    std::thread t2(invoke_fn);

    t1.join();
    t2.join();

    // Just ensure no crash or deadlock and counter is non-negative
    EXPECT_GE(CallbackTracker::counter.load(), 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}