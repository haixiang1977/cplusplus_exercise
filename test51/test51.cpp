// convert hart time to UTC time and keep milli second reslution
// g++ -std=c++11 test51.cpp -o test51.out

#include <stdio.h>
#include <cstdint>
#include <ctime>
#include <cstring>

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

    // get current utc time
    time_t tm;
    struct tm gmt_tm;

    tm = time(nullptr);
    gmtime_r(&tm, &gmt_tm);
    int chour = gmt_tm.tm_hour;

    // Assume that the time passed in is from "today".
    if ((hour != chour) && (chour == 0)) {
        // Figure out if we went over midnight
        tm = tm - (24 * 60 * 60);  // -1 day
        std::memset(&gmt_tm, 0, sizeof(tm));
        gmtime_r(&tm, &gmt_tm);
    }
    gmt_tm.tm_hour = hour;
    gmt_tm.tm_min = minute;
    gmt_tm.tm_sec = sec;
    uint64_t utc = mktime(&gmt_tm);

    printf("utc sec\t - %lu\n", utc);
    printf("utc ms\t - %lu\n", utc * 1000 + ms);

    return 0;
}
