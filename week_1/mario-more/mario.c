#include <cs50.h>
#include <stdio.h>

//setting function
void pyramid(int height);

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
    pyramid(height);
}

//pyramid print function
void pyramid(int height)
{
    //empty spaces
    int spaces = height - 1;
    //gap's length
    int gap = 2;
    for (int i = 0; i < height; i++)
    {
        //row's left spaces
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        //row's left blocks
        for (int j = 0; j < height - spaces; j++)
        {
            printf("#");
        }
        //row's gap
        for (int j = 0; j < gap; j++)
        {
            printf(" ");
        }
        //row's right blocks
        for (int j = 0; j < height - spaces; j++)
        {
            printf("#");
        }
        printf("\n");
        //next loop with less 1 white space
        spaces--;
    }
}