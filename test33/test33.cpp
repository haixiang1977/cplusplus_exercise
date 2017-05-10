#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

#define MSG_POST_USER_DATA 0
#define MSG_EXIT_THREAD 1

typedef struct User_s {
    int id;
    std::string msg;
}User_t;

class RestApiThread {
public:
    // Constructor
    RestApiThread(const char* threadName);
    
    // Destructor
    ~RestApiThread();

    // called once to create thread
    bool CreateThread();

    // called once to exit thread
    void ExitThread();

    // Add message into thread queue
    void PostMsg(const User_t* data);

private:
    RestApiThread(const RestApiThread&);
    RestApiThread& operator=(const RestApiThread&);

    // Entry point for process message
    void Process();

    std::thread* m_thread;
    std::queue<const User_t*> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    const char* THREAD_NAME;
};

RestApiThread::RestApiThread(const char* threadName)
{
    THREAD_NAME = threadName;
    m_thread = nullptr;
}

RestApiThread::~RestApiThread()
{
    
}

void RestApiThread::PostMsg(const User_t* data)
{
    std::cout << "RestApiThread::PostMsg In" <<std::endl;

    // mutex lock the queue
    std::unique_lock<std::mutex> lock(m_mutex);
    // push data into queue
    m_queue.push(data);
    // wakeup the process
    m_cv.notify_one();

    std::cout << "RestApiThread::PostMsg Out" <<std::endl;

    return;
}

void RestApiThread::Process()
{
    std::cout << "RestApiThread::Process started" <<std::endl;
    bool running = true;

    // wait for the queue
    while (running) {
        const User_t* data = nullptr;

        {
            // mutex lock the queue
            std::unique_lock<std::mutex> lock(m_mutex);
            // sleep to wait for wakeup
            if (m_queue.empty()) {
                // unlock the mutex during sleep
                //std::cout << "sleep" << std::endl;
                m_cv.wait(lock);
                //std::cout << "wakenup" << std::endl;
            }
            // waken up and get the mutex lock
            if (m_queue.empty()) {
                // do nothing
            } else {
                std::cout << "message received " << m_queue.size() << std::endl;
                // retrieve message from queue
                data = m_queue.front();
                m_queue.pop();
            }
            // unlock the mutex
        }

        // check valid data
        if (data != nullptr) {
            switch (data->id) {
                case MSG_POST_USER_DATA:
                {
                    // process message
                    std::cout << data->msg << std::endl;
                    // delete message
                    delete data;
                    data = nullptr;
                }
                break;
                case MSG_EXIT_THREAD:
                    // process message
                    std::cout << data->msg << std::endl;
                    // delete message
                    delete data;
                    data = nullptr;
                    running = false;
                break;
                default:
                break;
            }
        }
    }

    std::cout << "RestApiThread::Process quit" <<std::endl;
    return;
}

bool RestApiThread::CreateThread()
{
    if (m_thread == nullptr) {
        m_thread = new std::thread(&RestApiThread::Process, this);
        if (m_thread == nullptr) return false;
    }
    return true;
}

void RestApiThread::ExitThread()
{
    std::cout << "RestApiThread::ExitThread In" <<std::endl;

    if (m_thread == nullptr) return;

    User_t* data = new User_t();
    data->id = MSG_EXIT_THREAD;
    data->msg = std::string("byebye world");

    {
        // mutex lock the queue
        std::unique_lock<std::mutex> lock(m_mutex);
        // push data into queue
        m_queue.push(data);
        // wakeup the process
        m_cv.notify_one();
    }

    m_thread->join();
    delete m_thread;
    m_thread = nullptr;

    std::cout << "RestApiThread::ExitThread Out" <<std::endl;

    return;
}

int main()
{
    RestApiThread* rest = new RestApiThread("restapi");

    // create thread
    if (rest->CreateThread() == false) {
        std::cout << "failed to create thread" << std::endl;
        delete rest;
        rest = nullptr;
        return -1;
    }

    // wait for the thread running
    sleep(5);
    
    // send data into message queue
    User_t* data = new User_t();
    data->id = MSG_POST_USER_DATA;
    data->msg = std::string("hello world");

    rest->PostMsg(data);
    
    rest->ExitThread();

    delete rest;
    rest = nullptr;

    return 0;
}
