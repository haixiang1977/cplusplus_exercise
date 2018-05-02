/*
 * test42.cpp
 *
 *  Created on: May 1, 2018
 *      Author: liu
 */

// http://en.cppreference.com/w/cpp/thread/future
// http://www.cnblogs.com/haippy/p/3239248.html
// https://blog.csdn.net/liuxuejiang158blog/article/details/17354115

// c++11 library provide several async mechanism:
// if need to wait for event repeatedly, normally use conditional_variable.
// but sometimes only need to wait for event once or only need result (like time waste caculation), we can use future.

// Provider class: class to provide data in provider-consumer
//                 std::promise, std::package_task

// Future class: class to get the result data after async
//               std::future

// Provider function: functinon to schedule work load function as a task to execute
//                    std::async

// Currently, std::async is probably best suited to handling either very long running computations or long running IO for fairly simple programs.
// It doesn't guarantee low overhead though (and in fact the way it is specified makes it difficult to implement with a thread pool behind the scenes),
// so it's not well suited for finer grained workloads.

// For that you either need to roll your own thread pools using std::thread or use something like Microsoft's PPL or Intel's TBB.

#include <unistd.h>

#include <iostream>
#include <future>

int worker_thread() {
    int result = 0;
    std::cout << "worker thread started. time consuming ..." << std::endl;
    sleep(5);
    result = 10;
    std::cout << "worker thread stopped. result returned" << std::endl;

    return result;
}

int main() {
    // example 1: future/async example
    // create future and start async
    std::future<int> f = std::async(std::launch::async, worker_thread);

    // wait for the result return
    f.wait();

    // get the result
    std::cout << "result: " << f.get() << std::endl;

    // example 2: future/packaged_task
    // Use std::async if you want some things done and don't really care when they're done
    // Use std::packaged_task if you want to wrap up things in order to move them to other threads or call them later
    // In the end a std::packaged_task is just a lower level feature for implementing std::async
    // (which is why it can do more than std::async if used together with other lower level stuff, like std::thread).
    // Simply spoken a std::packaged_task is a std::function linked to a std::future and std::async wraps and calls a std::packaged_task (possibly in a different thread).

    // example 3: future/promise
    // use std::promise when you need more control over the future.
    
    return 0;
}
