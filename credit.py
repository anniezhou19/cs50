# AMEX: 15-Digit #'s, Star with: 34 or 37
# MASTERCARD: 16-Digit #'s, Start with: 51, 52, 53, 54, or 55
# VISA: 13-16-Digit #'s, Start with: 4
# Luhn’s Algorithm

from cs50 import get_string
import math

card = get_string("Number: ")
length = len(card)
sum = 0
for i in range(length-2, -1, -2):
    digit = int(card[i]) * 2
    if digit < 9:
        sum += digit
    else:
        sum += digit//10 + digit % 10
for i in range(length-1, -1, -2):
    sum += int(card[i])

if sum % 10 == 0:
    if length == 15:
        start = int(card) // math.pow(10, 13)
        if start == 34 or start == 37:
            print("AMEX")
    elif length == 16:
        start = int(card) // math.pow(10, 14)
        if 51 <= start <= 55:
            print("MASTERCARD")
    if 13 <= length <= 16:
        start = int(card) // math.pow(10, length-1)
        if start == 4:
            print("VISA")
else:
    print("INVALID")
    