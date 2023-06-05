#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Setting the functions
bool numcheck(string s);
string caesar(string s, long k);

int main(int argc, string argv[])
{
    string k = argv[1];
    // Checks if there is only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Checks if the key is a non-negative int
    else if (numcheck(k) == false || atol(k) < 0 || atof(k) / atol(k) != 1)
    {
        printf("Key must be a non-negative int\n");
        return 1;
    }
    else
    {
        // Asking plaintext
        printf("plaintext:  ");
        string plaintext = get_string("");
        // Returning ciphertext
        printf("ciphertext: ");
        printf("%s\n", caesar(plaintext, atol(k)));
    }

}

// Returns the cyphertext of s using the key k
string caesar(string s, long k)
{
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        // Checking if the atual char is alphabetic
        if (isalpha(c))
        {
            if (isupper(c))
            {
                // Increasing the key to the char
                c += k;
                // Verifying if the char is still alphabetic
                while (!(c >= 'A' && c <= 'Z'))
                {
                    // While it isn't subtract 26
                    c -= 26;
                }
            }
            if (islower(c))
            {
                // Increasing the key to the char
                c += k;
                // Verifying if the char is still alphabetic
                while (!(c >= 'a' && c <= 'z'))
                {
                    // While it isn't subtract 26
                    c -= 26;
                }
            }
        }
        // Modifying the actual char
        s[i] = c;
    }
    return s;
}

// Checks if the string is a number
bool numcheck(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}