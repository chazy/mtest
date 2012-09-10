#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>

#define PAGE_SIZE 4096
#define PAGE_MASK (~(PAGE_SIZE-1))
#define MB2B(_x) (_x * 1024UL * 1024UL)

static void usage(const char **argv)
{
	fprintf(stderr, "%s [memsize]\n", argv[0]);
}

static void do_scan(unsigned int amount)
{
	volatile char *start, *ptr, *end;
	unsigned long size = MB2B(amount & PAGE_MASK);

	start = ptr = malloc(size);
	if (!ptr) {
		perror("couldn't allocate memory");
		exit(EXIT_FAILURE);
	}

	end = start + size;
	while (1) {
		*ptr = 42;
		ptr += PAGE_SIZE;
		if (ptr == end) {
			printf(".");
			fflush(stdout);
			ptr = start;
		}
	}
}

int main(int argc, const char *argv[])
{
	unsigned int amount = 384; /* size to cyclic scan in MB */

	if (argc > 2) {
		usage(argv);
		return EXIT_FAILURE;
	} else if (argc == 2) {
		amount = atoi(argv[1]);

	}

	if (amount >= 2048) {
		fprintf(stderr, "value too large, max 2048 MB\n");
		return EXIT_FAILURE;
	}

	do_scan(amount);

	return 0;
}
