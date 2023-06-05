#include <cs50.h>
#include <stdio.h>

// Setting functions
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

// Asks for a positiver int value
int get_cents(void)
{
    int cents;
    while (true)
    {
        cents = get_int("Change owed: ");
        if (cents > 0)
        {
            break;
        }
    }
    return cents;
}

// Return the number of quarters in x cents
int calculate_quarters(int cents)
{
    return (int)(cents / 25);
}

// Return the number of dimes in x cents
int calculate_dimes(int cents)
{
    return (int)(cents / 10);
}

// Return the number of nickels in x cents
int calculate_nickels(int cents)
{
    return (int)(cents / 5);
}

// Return the number of pennies in x cents
int calculate_pennies(int cents)
{
    return cents;
}