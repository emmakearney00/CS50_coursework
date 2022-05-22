#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name;
    int age;
    string number;

    name = get_string("What's the contact's name? ");
    printf("The contact's name is "%s\n", name);

    age = get_int("What's the contact's age? ");
    printf("The contact's age is "%i\n", age);

    number = get_string("What's the contact's number? ");
    printf("The contact's phone number is "%s\n", number);
}


