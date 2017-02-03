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

int main()
{
	int i = 100;

	custom_printf(CUSTOM_DEBUG, "int i = %d\n", i);

	return 0;
}

