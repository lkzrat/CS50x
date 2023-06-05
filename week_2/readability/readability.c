#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Setting function
void get_grade(string s);

int main(void)
{
    // Inputting the text
    string text = get_string("Text: ");
    // Computing the grade
    get_grade(text);
}

void get_grade(string s)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;
    // Counting the nubmer of letters, words and sentences
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]))
        {
            letters++;
        }
        if (isspace(s[i]))
        {
            words++;
        }
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    // Calculating the grade
    float L = (float)letters * 100 / words;
    float S = (float)sentences * 100 / words;
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    // Printing the grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}