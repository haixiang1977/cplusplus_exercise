// https://stackoverflow.com/questions/14351352/will-asynclaunchasync-in-c11-make-thread-pools-obsolete-for-avoiding-expen
// https://stackoverflow.com/questions/15752659/thread-pooling-in-c11

// thread pool purpose:
//     the overhead of a threaded function call vs. a normal one is enormous
//     The overhead for creating a thread to handle a function call is something like 10000 or more times slower than a plain function call.
//     So, if you're issuing a lot of small function calls, a thread pool might be a good idea.

// idea to design thread pool:
//    A pool of threads means that all your threads are running, all the time – in other words, the thread function never returns. 
// 1. Start with maximum number of threads a system can support

// the typical data path: input request queue -> thread pool -> output response queue
#include <unistd.h>

#include <iostream>
#include <vector>
#include <thread>

void worker_thread(int idx) {
    std::cout << "worker_thread: " << idx << " started" << std::endl;

    while (1) {
        // 1. pop request from input queue
        //    conditional_variable_wait() and notified by provider notify_one
        // 2. process request
        //    call process_request()
        // 3. push response to output queue
        // 4. go back step 1
        sleep(1);
    }

    std::cout << "worker thread: " << idx << " stopped" << std::endl;

    return;
}

int main() {
    //  1. Start with maximum number of threads a system can support
    int num_threads = 10;

    // 2. initialize thread pool
    std::vector<std::thread> ThreadPool(num_threads);

    // 3. start the thread pool
    for (int i = 0; i < num_threads; i++) {
        ThreadPool[i] = std::thread(worker_thread, i);
    }

    std::cout << "main thread sleep" << std::endl;
    while (1) {
        sleep(1);
    }

    return 0;
}
   