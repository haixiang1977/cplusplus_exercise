// c++ conditional varible to implement interruptable sleep

#include <unistd.h>
#include <time.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
bool running = true;

void run() {
    chrono::system_clock::time_point abs_time;
    while (running == true) {
        std::unique_lock<std::mutex> lck(mtx); // lock mutex

        cout << "bf " << time(nullptr) << endl;
        // cv.wait(lck); // mutex unlocked
        if (cv.wait_for(lck, chrono::milliseconds(10 * 1000)) == cv_status::timeout) { // test with 10 seconds
            cout << "timeout " << endl;
        } else {
            cout << "up" << endl; // mutex locked again
        }
        cout << "af " << time(nullptr) << endl;
        // unlock the mutex when quit
    }
    return;
}

void go() {
    std::unique_lock<std::mutex> lck(mtx); // lock the mutex

    cout << "waking" << endl; // wake up condition variable
    cv.notify_all();

    // unlock the mutex when quit

    return;
}

int main() {
    std::thread thread = std::thread(run);

    sleep (20); // sleep 20 seconds to waiting for the thread running and see timeout

    for (int i = 0; i < 10; i++) {
        go();
        sleep(1);
    }

    // to quit
    go();
    running = false;
    thread.join();

    return 0;
}

