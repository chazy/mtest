#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <errno.h>

#define PAGE_SIZE 4096
#define PAGE_MASK (~(PAGE_SIZE-1))
#define MB2B(_x) ((_x) * 1024 * 1024)

static void usage(const char **argv)
{
	fprintf(stderr, "%s [memsize]\n", argv[0]);
}

static void do_scan(unsigned int amount)
{
	volatile unsigned long *start, *ptr, *end;
	unsigned long size = MB2B(amount) & PAGE_MASK;
	unsigned long offset = 0;

	start = ptr = malloc(size);
	if (!ptr) {
		perror("couldn't allocate memory");
		exit(EXIT_FAILURE);
	}

	end = start + size/sizeof(unsigned long);

	for (ptr = start; ptr < end; ptr++) {
		*ptr = (unsigned long)ptr;
	}

	ptr = start;
	while (1) {
		if (*ptr != (unsigned long)ptr) {
			printf("Corrupted memory found at %p, should be "
			       "%p, was %#08lx\n", ptr, ptr, *ptr);
			printf("Page dump:\n\n");

			unsigned long *ps, *pptr, *pend;
			ps = (unsigned long *)((unsigned long)ptr & PAGE_MASK);
			pend = ps + PAGE_SIZE/sizeof(unsigned long);
			for (pptr = ps; pptr < pend; pptr++) {
				printf("%0x:\t%#08lx %#08lx %#08lx %#08lx\n",
				       pptr - ps, pptr[0], pptr[1],
				       pptr[2], pptr[3]);
				pptr += 4;
			}
		}
		ptr++;
		if (ptr == end)
			ptr = start;
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

	do_scan(amount);
	return 0;
}
