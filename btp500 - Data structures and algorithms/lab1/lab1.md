# Lab 1

## Part A 
```python
"""
O(n) time complexity
O(n) space complexity

- Requires more space than a nested for loop
"""
def sum_to_goal(numbers_list, goal):
    targets = set(numbers_list);
    answer  = 0;
    
    for num in numbers_list:
        key = goal - num
        if key in targets and key != num:
            return num * key;
    
    return answer;


"""
O(n) time complexity
O(1) space complexity
"""
def fib(n):
    if(n <= 1):
        return n;
    previous  = 0
    current = 1
    for i in range(2,n+1):
        current, previous = previous + current, current
    return current

```


1. Did your teammate's analysis match what you thought your function's runtime was?

	- Yes my analysis matched what I thought my function's runtime was. Both my and their analysis was O(n)

2. Rewrite the two functions for part A in lab2.md file.  You can write exactly what you wrote on paper or you can alter it based on your discussions with your teammates.  If you made a change (outside of correcting syntax), why did you do it? if you did not alter it why not?

	- I made one change, changing my first function, sum_to_goal, adding a condition I missed. Before hand, I had my sum_to_goal function create a set of the values and then check if the goal minus the current value existed in the set and returned the product of them otherwise, just return 0 if no suitable pairs. However, I forgot to check if the value was the same as the goal minus the current value, meaning, if the current value's sum with itself reached the goal, it would return it's product with itself. So I added an if condition to ensure the current value + the goal minus current value is not the same.  

3. How would you test whether or not your analysis was correct?  Write a small python program to test your functions and demonstrate that the function behaves according to the expected runtime.  Provide the code for this test program here.

	- I would test my analysis with a a function that times the time taken to execute with increasingly larger inputs and random, and would compare it to a worser implementation and compare the time difference between larger time frames. For my test program, i'll show an example testing for sum_to_goal. For this example, I used a set to create the numbers as to make them all unique and then casted them into a list since the quesiton requires a list.

 	```python
  	#test.py
  
	import time
	import random

	def good_sum_to_goal(numbers_list, goal):
	    targets = set(numbers_list);
	    answer  = 0;
	    
	    for num in numbers_list:
		key = goal - num
		if key in targets and key != num:
		    return num * key;
	    
	    return answer;
	    
	def bad_sum_to_goal(numbers_list, goal):
	    for num in numbers_list:
		for num2 in numbers_list:
		    if num != num2 and (num + num2) == goal:
			return num * num2;
	    return 0;
	
	def measure_time(func, *args):
		start = time.time();
		func(*args)
		return time.time() - start;

	def test_sum_to_goal(func):
	    print(f'\nTesting: {func}')
	    for n in [10**2, 10**3, 10**4, 10**6]:
	        numbers = {random.randint(1,100) for _ in range(n)}
	        goal = random.randint(1,200)
	        print(f"n = {n}, time = ",
			f"{measure_time(func,list(numbers), goal):.7f} seconds")
	
 	if __name__ == "__main__":
		test_sum_to_goal(bad_sum_to_goal)
		test_sum_to_goal(good_sum_to_goal)
  	```

## Part B:

### function 1:

Analyze the following function with respect to number

```python
def function1(number):
	total = 0		# 1 for the assignment 

	for i in range(number):	# n + 1
					# loops n times 
					# 1 more for the call to the range function 
		
		x = i + 1	# 2 n 
					# there are two operations
					# assingment and addition operations
					# n as the loop runs n times 
		total += x * x	# 3 n 
					# there are three operations
						# assignment, + and * operations 
					# n as the loop runs n times 

	return total 		# 1 for the return

"""
T(n) = 1 + n + 1 + 2n + 3n + 1
T(n) = 6n + 3
Therefore T(n) is O(n)
"""
```



### function 2:

Analyze the following function with respect to number

```python
def function2(number):
	return (number * (number + 1) * (2 * number + 1)) // 6
	# 1 + 1 + 1 + 1 + 1 + 1 + 1 operations 
			# 1 for return 
			# 1 for the (number *) operation 
			# 1 for the (number + 1) operation 
			# 1 for the () * () operation 
			# 1 for the (2 * number) operation 
			# 1 for the (... number + 1) operation 
			# 1 for the // operation

"""
T(n) = 1 + 1 + 1 + 1 + 1 + 1 + 1
T(n) = 7
Therefore T(n) is O(1)
""" 
```

### function 3:

Analyze the following with respect to the length of the list.  Note that the function call len() which returns the length of the list is constant (O(1)) with respect to the length of the list.
```python
def function3(list):
	n = len(list)					# 2
								# 1 for the assignment 
								# 1 for the call to len function call
	for i in range(n - 1):				# (n-1) + 1 + 1
								# loops (n - 1) times 
								# 1 for the range function call
								# 1 for the - operator called 
		for j in range(n - 1 - i):		# ((n - 1 - i) + 1 + 1 + 1) (n-1)
								# loops (n - 1 - i) times 
								# 1 for the range function call 
								# 2 for the - operator called 
								# called (n - 1) times 
			if list[j] > list[j+1]:		# 4 ((n - 1 - i) (n - 1))
								# 1 for the +1 operation 
								# 2 for the [] operation 
								# 1 for the greater than (>) check 
				tmp = list[j]		# 2 ((n - 1 - i) (n - 1))
								#1 for the assignment
								#1 for the indexing operation 
				list[j] = list[j+1]	# 4 ((n - 1 - i) (n - 1))
								# 2 for the indexing operation 
								# 1 for the assignment 
								# 1 for the + operation 	
				list[j + 1] = tmp	# 3 ((n - 1 - i) (n - 1))
								# 1 for the indexing operation 
								# 1 for the + operation 
								# 1 for the assignment operation 

"""
T(n) = 2 + (n-1) + 1 + 1
	+ ((n - 1 - i) + 1 + 1 + 1) (n-1)
	+  4 ((n - 1 - i) (n - 1))
	+ 2 ((n - 1 - i) (n - 1))
	+ 4 ((n - 1 - i) (n - 1))
	+ 3 ((n - 1 - i) (n - 1))
= 5n^2 − 5ni − 6n + 18 + 5i
	-> Drop constants and insignificant (very small values)
T(n) = n^2 
Therefore T(n) is O(n^2)
"""
```

### function 4:


Analyze function4 with respect to the length of the mystring.  Hint, you will need to set up two mathematical functions for operator counting.  one for function2 and the other for recursive_function2

```python

def recursive_function4(mystring,a, b):
	if(a >= b ):							# 1 for the <= operator called 
		return True						# 1 for the return 
	else:
		if(mystring[a] != mystring[b]): 			# 3
										# 2 for [] (indexing) operator called 
										# 1 for != operator called 
			return False					# 1 for return 
		else:
			return recursive_function4(mystring,a+1,b-1) 	# n/2 * 3
									  # 1 for + operator called 
									  # 1 for - operator called 
									  # 1 for return 
									  # n/2 since 
									    # indexs (a,b) meet at half in worst scenario
									    # so this function will run n/2 times in worst case scenario 
"""
recursive_function4:

T(n) = 1 + 1 + 3 + 1 + (n/2 * 3)
T(n) = 6 + 3n/2
Therefore T(n) is O(n)
"""

def function2(mystring):
	return recursive_function4(mystring, 0,len(mystring)-1)	  # 4
									# 1 for return 
									# 1 for len function call 
									# 1 for - operator called 
									# 1 for recursive_function4 called
"""
function2:

T(n) = 4
T(n) = 4 
Therefore T(n) is O(1)
"""

"""
In Total:

T(n) = 6 + 3n/2 + 4 
T(n) = 10 + 3n/2
Therefore T(n) is O(n)
"""

```


### function 5:

Analyze the following function with respect to number


```python
def function5(value, number):
	if (number == 0):					# 1 for the == operator 
		return 1					# 1 for the return 
	elif (number == 1):					# 1 for the == operator 
		return value					# 1 for the return 
	else:
		half = number // 2				# 2 
									# 1 for the assignment operation
									# 1 for the // floor division operator 
		result = function5(value, half)			# logn 
									# problem is halved at every call 
									# proportional to log of value 
		if (number % 2 == 0):				# 2
									# 1 for the modulo % operator 
									# 1 for the == operator 
			return result * result			# 2
									# 1 for the return 
									# 1 for the * operator 
		else:
			return value * result * result		# 3 
									# 1 for return 
									# 2 for the * operator 

"""
T(n) = 1 + 1 + 1 + 1 + 2 + logn + 2 + 2 + 3
T(n) = 13 + logn
Therefore T(n) is O(logn)
"""
```
