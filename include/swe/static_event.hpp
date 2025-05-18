/**
 * @file static_event.hpp
 * @author Stellar Wolf Entertainment (SWE)
 * @brief Lightweight static event system for the SWE library.
 *
 * This header provides a simple, efficient event system for registering and invoking
 * static or free function callbacks. Only the specified Caller class can trigger the event,
 * while other classes may subscribe or unsubscribe callbacks. This system is designed for
 * performance and type safety, supporting only free/static functions (not member functions
 * or capturing lambdas).
 *
 * @copyright MIT License
 * @date created 2025-05-16
 * @version 1.0
 */
#pragma once

#include <algorithm>
#include <iostream>
#include <vector>


namespace swe
{
    /**
     * @brief A lightweight static event system for free/static function callbacks.
     * 
     * Only the specified Caller class can invoke the event. Other classes can subscribe or unsubscribe
     * static/free functions as callbacks. This event system only supports free and static functions,
     * and not capturing lambdas or member functions.
     * 
     * @tparam Caller The class allowed to trigger the event.
     * @tparam Args   The argument types passed to the callbacks.
     */
    template <typename Caller, typename... Args>
    class static_event
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
        static_event() = default;

        /**
         * @brief Deleted copy constructor.
         */
        static_event(const static_event&) = delete;

        /**
         * @brief Deleted move constructor.
         */
        static_event(static_event&&) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        static_event& operator=(const static_event&) = delete;

        /**
         * @brief Deleted move assignment operator.
         */
        static_event& operator=(static_event&&) = delete;

        /**
         * @brief Destructor.
         */
        ~static_event() = default;

        /**
         * @brief Subscribe a callback to the event.
         * @param cb The static/free function to add.
         */
        void operator+=(callback cb)
        {
            _callbacks.push_back(cb);
        }

        /**
         * @brief Unsubscribe a callback from the event.
         * @param cb The static/free function to remove.
         */
        void operator-=(callback cb)
        {
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
         * Only the Caller class can invoke this.
         * 
         * @param args Arguments to pass to each callback.
         */
        void operator()(Args... args)
        {
            for (auto& cb : _callbacks)
            {
                cb(args...);
            }
        }

        /**
         * @brief List of registered callbacks.
         */
        std::vector<callback> _callbacks;
    };
} // namespace swe