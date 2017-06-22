#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mpi.h>

/*
 * Визначити ефективність і прискорення
 * Вивести час роботи кожного процеса
 */

int	sum_of_num(int num)
{
	int	sum;
	int remainder;

	sum = 0;
	remainder = num;
	while (remainder > 0)
	{
		sum += remainder % 10;
		remainder /= 10;
	}
	return (sum);
}

char *itoa(int val, int base){

	static char buf[32] = {0};

	int i = 30;
	if (val == 0)
		return ("0\0");

	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];

}

int main(int argc, char **argv)
{
	int	year_sum;
	int month;
	int day;
	int sum;
	int num_of_answers;
	int answer;
	int fd;
	int n;
	int	frequency;
	int i;
	char *str;

	i = 0;
	day = 15;
	month = 7;
	year_sum = 24;
	num_of_answers = 0;
	sum = day + month + year_sum;
	n = atoi(argv[1]);
	fd = open("answers", O_WRONLY);
	if (fd == -1)
	{
		printf("Wrong file.");
		exit(0);
	}
//	MPI_INIT(&argc, &argv);
	while (i <= n)
	{
		if (sum_of_num(i) == sum)
		{
			str = itoa(i, 10);
			write(fd, str, strlen(str));
			write(fd, "\n", 1);
			num_of_answers++;
		}
		i++;
	}
	write(fd, "num_of_answers = ", 17);
	str = itoa(num_of_answers, 10);
	write(fd, str, strlen(str));
	write(fd, " out of ", 8);
	str = itoa(i - 1,10);
	write(fd, str, strlen(str));
	write(fd, " numbers\n", 9);
	write(fd, "frequency: 0.", 13);
	int zeros = 0;
	while (num_of_answers / i == 0 && num_of_answers != 0)
	{
		num_of_answers *= 10;
		zeros++;
	}
	int j = -1;
	while (++j < zeros)
		write(fd, "0", 1);
	str = itoa(num_of_answers / i, 10);
	write(fd, str, strlen(str));
	write(fd, "\n", 1);
	return 0;
}
