import random

def main():
    #make list of numbers 1 through 10 -> store in a constant variable
    numbers = list(range(1,11))
    #shuffle list
    sample = random.sample(numbers, len(numbers))
    #print first element in shuffled list
    print(sample[0])
main()