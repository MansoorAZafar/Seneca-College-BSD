#Time Decorator
import time;
def timer(func):
    def inner(*args):
        start = time.time();
        func(*args);
        end = time.time();
        return end - start;
    return inner;


#Memoization using Closures
def memoization(func):
    cache = {};
    def inner(*args):
        if args in cache:
            return cache[args];
        cache[args] = func(*args);
        return cache[args];
    return inner;



allowedUser = {"bob":123, "joe":789};
def Authorization(func):
    def inner(username, password, *args):
        if username in allowedUser and password is allowedUser[username]: 
            return func(*args);
        else:
            print('Unauthorized user');
            return;
    return inner;


"""
#Testing Authorization
@Authorization 
def doWork():
    print('hi');

doWork("heo", "123");
doWork("bob", "123");
"""

'''
#Testing Memoization
@memoization
def fib(n):
    if(n <= 1):
        return n;
    return fib(n-1) + fib(n - 2);
'''

'''
#Testing Timer
@timer
def doWork():
    cnt = 0;
    for i in range(10000000):
        cnt += 1;

print(doWork());
'''