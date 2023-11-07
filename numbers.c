#include "shell.h"

/**
 * long_to_string - Converts a number to a string representation.
 * @number: The number to be converted.
 * @string: A buffer to store the string representation of the number.
 * @base: The base to use for the conversion.
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
    int index = 0, isNegative = 0;
    long remainder = number;
    char digits[] = "0123456789abcdef";

    if (remainder == 0)
        string[index++] = '0';

    if (string[0] == '-')
        isNegative = 1;

    while (remainder)
    {
        if (remainder < 0)
            string[index++] = digits[-(remainder % base)];
        else
            string[index++] = digits[remainder % base];
        remainder /= base;
    }
    
    if (isNegative)
        string[index++] = '-';

    string[index] = '\0';
    str_reverse(string);
}

/**
 * _atoi - Converts a string to an integer.
 *
 * @s: A pointer to the original string.
 * Return: The integer value of the string or 0.
 */
int _atoi(char *s)
{
    int sign = 1;
    unsigned int number = 0;

    /* 1 - Analyze the sign */
    while (!('0' <= *s && *s <= '9') && *s != '\0')
    {
        if (*s == '-')
            sign *= -1;
        if (*s == '+')
            sign *= +1;
        s++;
    }

    /* 2 - Extract the number */
    while ('0' <= *s && *s <= '9' && *s != '\0')
    {
        number = (number * 10) + (*s - '0');
        s++;
    }
    
    return (number * sign);
}

/**
 * count_characters - Counts the occurrences of a character in a string.
 *
 * @string: A pointer to the original string.
 * @character: The character to be counted.
 * Return: The count of occurrences of the character in the string.
 */
int count_characters(char *string, char *character)
{
    int i = 0, count = 0;

    for (; string[i]; i++)
    {
        if (string[i] == character[0])
            count++;
    }
    
    return count;
}
