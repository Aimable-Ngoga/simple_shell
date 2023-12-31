#include "main.h"

/**
 * _getenv - return  value of env variable key
 * @key: variable
 *
 * Return: value of env variable
 */

char *_getenv(char *key)
{
        int i = 0;
        char *token;


        while (environ[i])
        {
                token = strtok(environ[i], "=");

                if (strcmp(key, token) == 0)
                {
                        return (strtok(NULL, "="));
                }
                i++;
        }

        return (NULL);
}
