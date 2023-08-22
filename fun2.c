#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
void ptr_to_hex(void *ptr, char *hex_str)
{
	snprintf(hex_str, BUFF_SIZE, "%p", ptr);
}
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}
/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}
/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
void apply_rot13(const char *input, char *output)
{
	int length = strlen(input);

	for (int i = 0; i < length; i++)
	{
		char c = input[i];
		if (isalpha(c))
		{
			char base = islower(c) ? 'a' : 'A';

			output[i] = (c - base + 13) % 26 + base;
		}
		else
		{
			output[i] = c;
		}
	}
	output[length] = '\0';
}
int print_rot13(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *s = va_arg(types, char *);

	int chars_written = 0;
	int len = strlen(rot13);

	if (s != NULL)
	{
		char rot13[BUFF_SIZE];
		apply_rot13(s, rot13);

		if (flags == '-')
		{
			strncpy(buffer + chars_written, rot13, len);

			chars_written += len;

			while (chars_written < width)
			{
				buffer[chars_written++] = ' ';
			}
		}
		else
		{
			while (chars_written < width - len)
			{
				buffer[chars_written++] = ' ';
			}
			strncpy(buffer + chars_written, rot13, len);
			chars_written += len;
		}
	}
	return (chars_written);
}
