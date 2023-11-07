#include "main.h"

/**
 * Determine if the shell is in interactive mode.
 * @param info - a pointer to a structure
 * @return 1 if the shell is in interactive mode, 0 otherwise
 */
int isInteractiveMode(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * Check if a character is a delimiter.
 * @param c - the character to check
 * @param delim - the delimiter string
 * @return 1 if it's a delimiter, 0 if it's not
 */
int isCharacterDelimiter(char c, char *delim)
{
    while (*delim)
        if (*delim++ == c)
            return 1;
    return 0;
}
/**
 * Check if a character is alphabetic.
 * @param c - the character to check
 * @return 1 if 'c' is an alphabetic character, 0 otherwise
 */
int isAlphabeticCharacter(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else
        return 0;
}
/**
 * Convert a string to an integer.
 * @param s - the string to be converted
 * @return 0 if there are no numbers in the string, the converted number otherwise
 */
int convertStringToInteger(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return output;
}

