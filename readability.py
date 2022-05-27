# Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
# L is the average number of letters per 100 words in the text
# S is the average number of sentences per 100 words in the text.

from cs50 import get_string

text = get_string("Text: ")

letter = 0
word = 1
sentence = 0
length = len(text)

for i in range(length):
    if text[i].isalpha() == True:
        letter += 1
    elif text[i] == " ":
        word += 1
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        sentence += 1

index = round(0.0588 * (100 * letter / word) - 0.296 * (100 * sentence / word) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")