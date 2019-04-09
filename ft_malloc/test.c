#include "ft_malloc.h"
#include <stdio.h>

int main()
{
	int s = 1000;
	char *a[s];
	for (int i = 0; i < s; ++i)
		a[i] = malloc(500 * 2 * i / s);
	show_alloc_mem();
	return (0);
}
