/**
 * @file concurrent_static_event.hpp
 * @author Stellar Wolf Entertainment (SWE)
 * @brief Thread-safe static event system for the SWE library.
 *
 * This header provides a thread-safe static event system for registering and invoking
 * static or free function callbacks. Only the specified Caller class can trigger the event,
 * while other classes may subscribe or unsubscribe callbacks. All operations are protected
 * by a mutex for safe concurrent access. Only free/static functions (not member functions
 * or capturing lambdas) are supported for callbacks.
 *
 * @copyright MIT License
 * @date created 2025-05-16
 * @version 1.0
 */

#pragma once

#include <algorithm>
#include <mutex>
#include <vector>

namespace swe
{
    /**
     * @brief Thread-safe static event system for free/static function callbacks.
     *
     * Only the specified Caller class can invoke the event. Other classes can subscribe or unsubscribe
     * static/free functions as callbacks. All operations are protected by a mutex for thread safety.
     *
     * @tparam Caller The class allowed to trigger the event.
     * @tparam Args   The argument types passed to the callbacks.
     */
    template <typename Caller, typename... Args>
    class concurrent_static_event
    {
        friend Caller;

      public:
        /**
         * @brief Type alias for the callback function pointer.
         */
        using callback = void (*)(Args...);

        /**
         * @brief Default constructor.
         */
        concurrent_static_event() = default;

        /**
         * @brief Deleted copy constructor.
         */
        concurrent_static_event(const concurrent_static_event&) = delete;

        /**
         * @brief Deleted move constructor.
         */
        concurrent_static_event(concurrent_static_event&&) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        concurrent_static_event& operator=(const concurrent_static_event&) = delete;

        /**
         * @brief Deleted move assignment operator.
         */
        concurrent_static_event& operator=(concurrent_static_event&&) = delete;

        /**
         * @brief Destructor.
         */
        ~concurrent_static_event() = default;

        /**
         * @brief Subscribe a callback to the event.
         * @param cb The static/free function to add.
         */
        void operator+=(callback cb)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _callbacks.push_back(cb);
        }

        /**
         * @brief Unsubscribe a callback from the event.
         * @param cb The static/free function to remove.
         */
        void operator-=(callback cb)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = std::remove(_callbacks.begin(), _callbacks.end(), cb);
            if (it != _callbacks.end())
            {
                _callbacks.erase(it, _callbacks.end());
            }
        }

      private:
        /**
         * @brief Invoke all registered callbacks with the provided arguments.
         *
         * Only the Caller class can invoke this. All callbacks are called while holding the mutex.
         *
         * @param args Arguments to pass to each callback.
         */
        void operator()(Args... args)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            for (auto& cb : _callbacks)
            {
                cb(args...);
            }
        }

        /**
         * @brief Mutex for thread safety.
         */
        std::mutex _mutex;

        /**
         * @brief List of registered callbacks.
         */
        std::vector<callback> _callbacks;
    };
} // namespace swe