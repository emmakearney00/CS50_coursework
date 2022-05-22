#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int f(char*s);

int main(void)
{
    printf("%c\n", f("abc"));
}

int f(char*s)
{
    int r=0;
    for(int i=0,n=strlen(s);i<n;i++)
    {
        r+=(s[n-i-1]-'0')*pow(10,i);
    }
    return r;
}





