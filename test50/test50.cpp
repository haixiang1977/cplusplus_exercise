#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>

#include <cstdint>

int main() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::cout << "hours since epoch - " \
              << std::chrono::duration_cast<std::chrono::hours>( \
                 now.time_since_epoch()).count() << std::endl;

    std::cout << "seconds since epoch - " \
              << std::chrono::duration_cast<std::chrono::seconds>( \
                 now.time_since_epoch()).count() << std::endl;

    std::cout << "milliseconds since epoch - " \
              << std::chrono::duration_cast<std::chrono::milliseconds>( \
                 now.time_since_epoch()).count() << std::endl;

    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>( \
                 now.time_since_epoch()).count();

    printf("uint64_t ms - %lu\n", ms);

    return 0;
}


