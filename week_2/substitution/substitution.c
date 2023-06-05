#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Setting the functions
string crypt(string s, string k);
bool keycheck(string k);
bool alphacheck(string s);

int main(int argc, string argv[])
{
    string k = argv[1];
    // Checks if there is only one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Checks if key is valid
    if (!keycheck(k))
    {
        printf("Key must contain 26 non-equal alphabetic characters\n");
        return 1;
    }
    // Asking plaintext
    printf("plaintext:  ");
    string plaintext = get_string("");
    // Returning ciphertext
    printf("ciphertext: %s\n", crypt(plaintext, k));
}

// Encrypts the string s using the key k
string crypt(string s, string k)
{
    // Loop for each char of the string
    for (int i = 0; i < strlen(s); i++)
    {
        char c = toupper(s[i]);
        // Encrypting
        for (char j = 'A'; j <= 'Z'; j++)
        {
            if (c == j)
            {
                c = k[j - 'A'];
                break;
            }
        }
        if (isupper(s[i]))
        {
            s[i] = toupper(c);
        }
        else
        {
            s[i] = tolower(c);
        }
    }
    return s;
}

// Checks if the key is valid
bool keycheck(string k)
{
    // Verify if the key is alphabetic and has 26 chars
    if (!alphacheck(k) || strlen(k) != 26)
    {
        return false;
    }
    // Verify if none of the chars are the same
    for (int i = 0; i < strlen(k); i++)
    {
        for (int j = 0; j < strlen(k); j++)
        {
            if (i != j && k[i] == k[j])
            {
                return false;
            }
        }
    }
    return true;
}

// Checks if the string is alphabetic
bool alphacheck(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}