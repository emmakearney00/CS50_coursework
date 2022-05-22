from cs50 import get_float
from math import floor


def main():
    # get amount from user
    while True:
        n = get_float("Amount: ")
        if n > 0:
            break
    # convert to cents
    cents = 100*n

    # calculate quarters
    quarters = floor(cents/25)
    cents = cents - quarters*25

    # calculate dimes
    dimes = floor(cents/10)
    cents = cents - dimes*10

    # calculate nickels
    nickels = floor(cents/5)
    cents = cents - nickels*5

    # calculate pennies
    pennies = cents

    # total number of coins to return
    coins = quarters + dimes + nickels + pennies
    print(coins)


main()

