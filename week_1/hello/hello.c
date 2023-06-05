#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //creating str var and inputting a str value
    string name = get_string("What's your name? ");
    //printing "hello, str input"
    printf("hello, %s\n", name);
}