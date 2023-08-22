#include "main.h"
#include <stdio.h>
#include <stdarg.h>
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	int printed_chars = 0;

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;

			if (*format == 'c')
			{
				char c = va_arg(args, int);

				putchar(c);

				printed_chars++;
			}
			else if (*format == 's')
			{
				char *s = va_arg(args, char *);

				if (s != NULL)
				{
					while (*s != '\0')
					{
						putchar(*s);

						s++;

						printed_chars++;
					}
				}
			}
			else if (*format == '%')
			{
				putchar('%');

				printed_chars++;
			}
		}
		else
		{
			putchar(*format);

			printed_chars++;
		}

		format++;
	}

	va_end(args);

	return (printed_chars);
}
/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

