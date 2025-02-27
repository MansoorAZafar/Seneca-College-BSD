# Mansoor Zafar
# 100503226
# BTP405NAA
"""
Why did you choose a DS?
> I chose a list because appending to a list only takes O(1) time
> and it's memory efficent. Furthermore, I have no need for any extra
> functionality rather, I just need to store the data and return it as a list
> so I chose to use a list comphrension since it does the job without any excess functionaltiies
> whilst still being fast and efficent 

Can you avoid a loop?
> No. You'll have one loop inside the helper function to determine
> if the argument is a prime or not and the second loop will be in the 
> list comprehension to loop through the values and check the condition.

Can you avoid a function call?
> Yes and no. If you wish to meet the requirement of having a "helper function" then 
> no you cannot however, you could merge the two together into one code and 
> avoid the second function call at the cost of readability & maintainability

Can you avoid repitive code?
> No, because both loops are needed as explained inside 
> the "[c]an you avoid a loop?" question.

Do you understand every line of your code?
> Yes
"""

from math import sqrt;

'''
* For Every value in range between [2, sqrt(n) + 1]
* We check if it's a prime by seeing if its divisible
* by another value besides itself and 1
* Up to sqrt(n) included.

* If YES: return False
* If NO : return True

-----
Note
-----
* We go from 2 to Square root of n (inclusive)
* [2, sqrt(n)]
* Because, after that point, the factors repeat in
* opposite order
* EX. 16 factors are : (1,16) (2,8) (4,4) (8,2) (16,1)
* After (4,4) or the combinations of sqrt(16) -> 
* The factors repeat just in opposite order

'''
def isPrime(n):
    for i in range(2, int(sqrt(n)) + 1):
        if n%i == 0:
            return False;
    return True;


'''
* For every prime number in the range from [2, n]
* Add it into a list and return it
-------
Note
-------
* We start from 2 since 1 & 0 are not primes and
* negative numbers cannot be prime numbers
* n is included to check if the value of n itself is a prime
* Expression | Loop | Condition
* Prime        [2,n]  isPrime()
'''
def getPrimeNumbers(n):
    return [prime for prime in range(2, n + 1) if isPrime(prime)];

#TESTING
print(getPrimeNumbers(10)) # [2, 3, 5, 7]
print(getPrimeNumbers(2))  # [2]
print(getPrimeNumbers(0))  # []
print(getPrimeNumbers(-50))# []
print(getPrimeNumbers(13)) # [2, 3, 5, 7, 11]