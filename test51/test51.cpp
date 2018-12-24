// convert hart time to UTC time and keep milli second reslution
// g++ -std=c++11 test51.cpp -o test51.out

#include <stdio.h>
#include <cstdint>
#include <chrono>

int main() {
    uint64_t hart_value = 24 * 60 * 60 * ((uint64_t)32000) - (uint64_t)1; // 1 sec and 32 ms

    // convert to ms
    uint64_t hart_value_in_ms = hart_value / 32;
    int ms = hart_value_in_ms % 1000;
    printf("extracted ms %d\n", ms);

    // convert to sec
    uint64_t hart_value_in_sec = hart_value_in_ms / 1000;
    int sec = hart_value_in_sec % 60;
    printf("extracted sec %d\n", sec);

    // convert to minute
    uint64_t hart_value_in_minute = hart_value_in_sec / 60;
    int minute = hart_value_in_minute % 60;
    printf("extracted minute %d\n", minute);

    // convert to hour
    int hour = hart_value_in_minute / 60;
    printf("extracted hour %d\n", hour);

    // current utc - ms
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    uint64_t now_ms = std::chrono::duration_cast<std::chrono::milliseconds>( \
                 now.time_since_epoch()).count();

    printf("current utc ms - %lu\n", now_ms);
    
    return 0;
}
