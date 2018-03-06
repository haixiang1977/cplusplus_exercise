#include <unistd.h>

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

static bool poll_run = false;
static bool pub_run = false;

static std::thread poll_task;
static std::thread pub_task;

static int count = 0;

// read/write lock structure
static std::mutex m_mutex;
static std::condition_variable read_cv, write_cv;
static int read_cnt = 0;
static int write_cnt = 0;
static int read_wait_cnt = 0;
static int write_wait_cnt = 0;

void Read_Lock() {
    std::unique_lock<std::mutex> lck(m_mutex);

    if ((write_cnt > 0) || (write_wait_cnt > 0)) {
        read_wait_cnt ++;
        do {
            read_cv.wait(lck);
        } while ((write_cnt > 0) || (write_wait_cnt > 0));
        read_wait_cnt --;
    }
    read_cnt ++;

    return;
}

void Read_UnLock() {
    std::unique_lock<std::mutex> lck(m_mutex);

    read_cnt --;
    if (write_wait_cnt > 0) {
        write_cv.notify_all();
    }

    return;
}

void Write_Lock() {
    std::unique_lock<std::mutex> lck(m_mutex);

    if ((read_cnt > 0) || (write_cnt > 0)) {
        write_wait_cnt ++;
        do {
            write_cv.wait(lck);
        } while ((read_cnt > 0) || (write_cnt > 0));
        write_wait_cnt --;
    }
    write_cnt = 1;

    return;
}

void Write_UnLock() {
    std::unique_lock<std::mutex> lck(m_mutex);

    write_cnt = 0;
    if (write_wait_cnt > 0) {
        write_cv.notify_all();
    } else if (read_wait_cnt > 0) {
        read_cv.notify_all();
    }

    return;
}

void PollTask() {
    std::cout << "Poll Task Running" << std::endl;

    while (poll_run) {
        Read_Lock();
        std::cout << "read " << count << std::endl;
        Read_UnLock();
        sleep (1);
    }

    std::cout << "Poll Task Quit" << std::endl;
}

void PubTask() {
    std::cout << "Pub Task Running" << std::endl;

    while (pub_run) {
        Read_Lock();
        std::cout << "read " << count << std::endl;
        Read_UnLock();
        sleep (1);
    }

    std::cout << "Pub Task Quit" << std::endl;
}

int main() {
    // main routine is hierachy update task
    std::cout << "Hierachy Task Running" << std::endl;
    
    // start poll task
    poll_run = true;
    poll_task = std::thread(&PollTask);

    // start pub task
    pub_run = true;
    pub_task = std::thread(&PubTask);

    while (count < 100) {
        Write_Lock();
        count ++;
        std::cout << "write " << count << std::endl;
        Write_UnLock();

        sleep(1);
    }

    std::cout << "Hierachy Task Quit" << std::endl;

    poll_run = false;
    poll_task.join();

    pub_run = false;
    pub_task.join();

    return 0;
}
