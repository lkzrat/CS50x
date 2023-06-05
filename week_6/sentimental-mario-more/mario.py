height = 0
while str(height).isnumeric() == False or (0 < int(height) <= 8) == False:  # Check if input is valid
    height = input('Height: ')  # Gets user's input

height = int(height)

for i in range(1, height + 1):
    print(' ' * (height - i) + '#' * i + '  ' + '#' * i)  # Prints a mario pyramid with user's input