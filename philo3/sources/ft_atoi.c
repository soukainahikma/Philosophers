#include "../headers.h"

int	ft_atoi(const char *str)
{
	unsigned long	number;
	int				c;

	number = 0;
	c = 1;
	while (*str != '\0' && (*str == '\n' || *str == '\t' || *str == '\r'
			|| *str == ' ' || *str == '\f' || *str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			c = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		number = number * 10 + *str - '0';
		if (number > LONG_MAX && c == 1)
			return (-1);
		if (number > LONG_MAX && c == -1)
			return (0);
		str++;
	}
	return (c * number);
}
