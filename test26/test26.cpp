/*
 * test26.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: liu
 */

#include <stdio.h>
#include <time.h>

int main()
{
    struct tm gmt;
    time_t utc = 0;

    // 2017-01-24 5:5:45
    gmt.tm_sec = 45;
    gmt.tm_min = 5;
    gmt.tm_hour = 5;
    gmt.tm_mday = 24;
    gmt.tm_mon = 0; // month - 1
    gmt.tm_year = 117; // year - 1900

    utc = mktime(&gmt);
    printf ("printf %llu \n", (unsigned long long)utc);
}



