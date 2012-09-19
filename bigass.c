#include <stdio.h>
#include <stdlib.h>

extern void bigass_function(void);

int main(int argc, const char *argv[])
{
	printf("Starting bigass_loop...");
	bigass_function();

	fprintf(stderr, "ERROR: Big Ass Loop Returned!\n");
	return EXIT_FAILURE;
}
