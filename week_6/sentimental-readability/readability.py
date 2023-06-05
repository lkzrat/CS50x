def main():
    text = str(input('Text: '))  # Getting input
    print(get_grade(text))  # Printing grade


def get_grade(t):
    s = 0
    w = 1
    l = 0

    # Couting Sentences, Words and Letters
    for i in range(len(t)):
        if t[i] in ('.', '!', '?'):
            s += 1
        if t[i] == ' ':
            w += 1
        if t[i].isalpha():
            l += 1

    # Getting the average
    S = float(s * 100 / w)
    L = float(l * 100 / w)

    # Calculating grade
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    # Checking grade
    if grade < 1:
        return 'Before Grade 1'
    elif grade >= 16:
        return 'Grade 16+'
    else:
        return f'Grade {grade}'


if __name__ == '__main__':
    main()