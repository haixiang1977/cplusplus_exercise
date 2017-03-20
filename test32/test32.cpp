/*
 * test32.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: liu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* castochar(unsigned char c) {
	char *s = new char[3]; //Value of 3 because unsigned char can be 2 characteres + 1 of '\0'
	s[0] = c;
	snprintf(s, 3, "%02x", c);
	return s;
}

char* inttochar(int i) {
	// in hart, int can be 10 characteres + 1 of '\0'
	char *s = new char[11];

	snprintf(s, 11, "%d", i);
	return s;
}

char* floattochar(float f) {
	// in hart, float can be 7 characteres + 1 of '\0'
	if (f != f) {
		return "0";
	}
	char *s = new char[8]; //Value of 8 by sizeof(float) + 1
	snprintf(s, 8, "%.3f", f);
	return s;
}

char* timetochar(time_t t) {
	char *s = new char[12]; //Value of 10 because need milliseconds precision of 10 + 1 of '\0'
	snprintf(s, 12, "%ld", t);
	return s;
}

char* longlongtochar(long long l) {
	char *s = new char[14];
	snprintf(s, 14, "%lld", l);
	return s;
}

int main()
{
	unsigned char a = 'A';
	printf("'A' cast to char %s\n", castochar(a));

	int i = 123456789;
	printf ("123456789 cast to char %s\n", inttochar(i));

	float f = 123.456;
	printf ("123.456 cast to char %s\n", floattochar(f));

	time_t t = time(NULL);
	printf ("current time cast to char %s\n", timetochar(t));

	long long l = 1234567890123;
	printf("size of long %d\n", sizeof(long long));
	printf ("'1234567890123' cast to char %s\n", longlongtochar(l));

	return 0;
}
