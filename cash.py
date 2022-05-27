from cs50 import get_float

while True:
    change = get_float("Change owed: ") * 100
    if change > 0:
        break
print(change)

if change >= 25:
    quarter = change // 25
    dime = (change % 25) // 10 
    nickel = ((change % 25) % 10) // 5 
    penny = (((change % 25) % 10) % 5) // 1
    count = quarter + dime + nickel + penny
elif change >= 10:
    dime = change // 10
    nickel = ((change % 10) // 5)
    penny = ((change % 10) % 5) 
    count = dime + nickel + penny
elif change >= 5:
    nickel = change // 5
    penny = change % 5
    count = nickel + penny
else:
    penny = change
    count = penny
    
print(count)