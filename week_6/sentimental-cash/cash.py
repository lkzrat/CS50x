def main():
    change = get_change()
    print(count_coins(change))


# Check for valid input and returns it in float
def get_change():
    while True:
        cash = str(input("Change owed: "))  # User's input

        if '$' in cash:
            cash = cash.replace('$', '')  # Remove '$'

        try:
            cash = float(cash)
            if cash > 0:
                return cash
        except:
            continue

# Return the minimum coin


def count_coins(cash):
    cash *= 100
    coins = coin = 0

    c = [25, 10, 5, 1]  # Array of coins

    for i in c:
        coin += int(cash/i)
        coins += coin
        cash -= coin * i
        coin = 0

    return coins


if __name__ == '__main__':
    main()