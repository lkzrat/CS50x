def main():
    card = 0

    # Pompting user's input
    while True:
        try:
            card = int(input('Number: '))
            break
        except:
            continue

    # Printing result
    if (verify(card)):
        print(get_flag(card))
    else:
        print('INVALID')


def verify(c):
    digits1 = []
    digits2 = []
    sum = 0
    l = len(str(c))

    # Separating digits
    for i, j in zip(range(l - 1, -1, -1), range(l)):
        if j % 2 != 0:
            digits1.append(str(c)[i])
        else:
            digits2.append(str(c)[i])

    # Multiplying first digits array
    for i, j in zip(digits1, range(len(digits1))):
        digits1[j] = int(i) * 2

    # Adding the digits
    for i in digits1:
        if len(str(i)) > 1:
            for j in range(len(str(i))):
                sum += int(str(i)[j])
        else:
            sum += i

    # Adding the digits
    for i in digits2:
        sum += int(i)

    # Vrifying if the last sum digit is a 0 and if the card number length is correct
    if str(sum)[-1] == '0' and l in (13, 15, 16):
        return True
    else:
        return False


def get_flag(c):
    c = str(c)

    # Checking for all card number lengths
    match len(c):
        case 16:
            # Checking for MATERCARD
            if int(c[:2]) in (51, 52, 53, 54, 55):
                return 'MASTERCARD'
            # Checking for VISA 16 lenght
            if int(c[0]) == 4:
                return 'VISA'
            return 'INVALID'
        case 15:
            # Checking for AMEX
            if int(c[:2]) in (34, 37):
                return 'AMEX'
            return 'INVALID'
        case 13:
            # Checking for VISA 13 length
            if int(c[0]) == 4:
                return 'VISA'
            return 'INVALID'


if __name__ == '__main__':
    main()