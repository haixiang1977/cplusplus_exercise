/*
 * test30.c
 *
 *  Created on: Feb 4, 2017
 *      Author: liu
 */

#include <stdio.h>
#include <stdarg.h>

#define CUSTOM_DEBUG 0
#define CUSTOM_ERROR 1

void custom_printf(int level, const char* fmt, ...) {
	va_list ap;
	va_start (ap, fmt);

	switch (level) {
	case CUSTOM_DEBUG:
		printf("DEBUG	printf	");
		printf (fmt, ap);
		// works with vprintf
		printf("DEBUG	vprintf	");
		vprintf (fmt, ap);
		break;
	}
	va_end(ap);
	return;
}

//#define macro_printf(level, fmt, ...) printf(fmt, __VA_ARGS__)
#define macro_printf(level, fmt, ...) \
	do { \
		switch(level) { \
		case CUSTOM_ERROR: \
			printf("ERROR	printf	"); \
			printf(fmt, __VA_ARGS__); \
			break; \
		default: \
			break; \
		} \
	} while(0);

int main()
{
	int i = 100;

	custom_printf(CUSTOM_DEBUG, "int i = %d\n", i);

	macro_printf(CUSTOM_ERROR, "int i = %d\n", i);

	return 0;
}

