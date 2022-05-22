#include <string.h>

#include "ctype.h"

// Return true if c is alphabetical (uppercase or lowercase), else false
bool isalpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Return true if c is a decimal digit, else false
bool isdigit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Return true if c is alphabetical (uppercase or lowercase)
// or numeric (i.e., a decimal digit), else false
bool isalnum(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Return true if every char in s is alphabetical and uppercase, else false
bool areupper(char *s)
{
    int count = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            count++;
        }
    }
    if (count == n)
    {
        return true;
    }
    else
    {
        return false;
    }

}
