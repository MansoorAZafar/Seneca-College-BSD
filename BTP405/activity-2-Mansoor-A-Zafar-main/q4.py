# Mansoor Zafar
# 100503226
# BTP405NAA
"""
Why did you choose a DS?
> There is no DS being used here, 
> none needed in the requirements either

Can you avoid a loop?
> No, the first loop is for getting each line inside the file
> then the comprehensions loop inside the decorator function could be replaced
> with a manual loop however, you'd still have a loop and it'd be slower since
> list comprehensions are faster than regular loops 

Can you avoid a function call?
> Sort of. Decorator functions are useful for adding functionalities to 
> a function without having to modify the caller of it. If you just wrote the 
> full functionality in the printInfo() function then you wouldn't need
> a decorator and thus reduce the function call. But, with the conditions, you
> cannot avoid any function call here.

Can you avoid repitive code?
> No

Do you understand every line of your code?
> Yes
"""

"""
* We take in a function to add the functionality of 
* printing out the total length of the numbers, 
* the max number and the average of the numbers.

* Then we return the original function with its param
* so it can run its own original functionality
-----
Note
-----
* We define an inner function to actually add the additional
* functionality to the function
* The outside function takes in the function to modify
* and the inner actually adds the extra functionalities

* we return the inner function to actually override the 
* previous function
"""
def smart_printInfo(func):
    def inner(line):
        numbers = [int(n) for n in line if n.isdigit()];
        totalN = len(numbers);
        maxN   = max(numbers);
        avg    = sum(numbers) / totalN;
        print(f'avg is : {avg} and max is : {maxN} and the totalN is {totalN}');
        func(line);
    return inner;

#you could also do 
#printInfo = smart_printInfo(printInfo);
#Links the printInfo to the decorator
@smart_printInfo
def printInfo(line):
    print(f'The numbers are {line}');


"""
* We open the file with 'with' so it automatically closes
* for every line inside the fine, we pass it as an argument to the
* decorator helper function
"""
def printStats(t):
    with open(t, "r") as file:
        for line in file:
            printInfo(line);

#Testing
printStats("Stats_Test.txt");

