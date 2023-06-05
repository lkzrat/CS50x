#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    while (true)
    {
        //int input
        height = get_int("Height: ");
        //checks if it is positive and between [1, 8]
        if (height > 0 && height < 9)
        {
            break;
        }
    }
    //empty spaces
    int spaces = height - 1;
    for (int i = 0; i < height; i++)
    {
        //row's white spaces
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        //row's blocks
        for (int k = 0; k < height - spaces; k++)
        {
            printf("#");
        }
        printf("\n");
        //next loop with less 1 white space
        spaces--;
    }
}