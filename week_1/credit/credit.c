#include <cs50.h>
#include <stdio.h>

// Setting verify function
bool verify(long card);
int get_digits(long n);
string get_flag(long card);

int main(void)
{
    // Asks the card number
    long card = get_long("Number: ");
    // Verify if the card number is valid
    if (verify(card))
    {
        printf("oi");
        printf("%s", get_flag(card));
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function that applies the Luhn’s Algorithm to verify the card number
bool verify(long card)
{
    long N = card;
    long n = N;
    int sum = 0;
    // The last digit is ignored in the beggining
    n /= 10;
    while (n > 0)
    {
        // Value that is going to be added in sum
        int value = (n % 10) * 2;
        // If the value has 2 digits its added eaech digit
        if (value > 9)
        {
            sum += (value % 10 + (value / 10) % 10);
        }
        else
        {
            sum += value;
        }
        //Jump 2 digits and repeat the process
        n /= 100;
    }
    // Restore n value to use it in the second part
    n = N;
    while (n > 0)
    {
        // Adding the digits that weren't multiplied
        sum += n % 10;
        //Jump 2 digits and repeat the process
        n /= 100;
    }
    // If sum's last digit is 0, the card number is VALID
    if (sum % 10 == 0)
    {
        return true;
    }
    // Else, it is INVALID
    else
    {
        return false;
    }
}

//Gets what flag the card is
string get_flag(long card)
{
    if (get_digits(card) == 15)
    {
        // Getting the last 2 digits
        while (card / 100 > 0)
        {
            card /= 10;
        }
        // Verifying if they are valid for AMEX
        if (card == 34 || card == 37)
        {
            return "AMEX\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    else if (get_digits(card) == 16)
    {
        // Getting the last 2 digits
        while (card / 100 > 0)
        {
            card /= 10;
        }
        // Verifying if they are valid for MASTERCARD
        if (card == 51 || card == 52 || card == 53 || card == 54 || card == 55)
        {
            return "MASTERCARD\n";
        }
        else
        {
            // Getting the last digit
            card /= 10;
            // Verifying if they are valid for VISA
            if (card == 4)
            {
                return "VISA\n";
            }
            else
            {
                return "INVALID\n";
            }
        }
    }
    else if (get_digits(card) == 13)
    {
        // Getting the last digit
        while (card / 10 > 0)
        {
            card /= 10;
        }
        // Verifying if they are valid for VISA
        if (card == 4)
        {
            return "VISA\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    else
    {
        return "INVALID\n";
    }
}

// Gets how many digits n has
int get_digits(long n)
{
    int digits = 0;
    while (n > 0)
    {
        n /= 10;
        digits++;
    }
    return digits;
}