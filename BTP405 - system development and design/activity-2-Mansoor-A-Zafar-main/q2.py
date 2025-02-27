# Mansoor Zafar
# 100503226
# BTP405NAA
"""
Why did you choose a DS?
> I chose a list since I am using the bucketing technique. Each index will contain the number of occurance for that set range
> Lists don't use as much memory as dicts and are faster for random access searchs. 
> However, the main reason I used a list over a dict is because with the bucketing technique,
> every value is already sorted in a sense. Ex. all the values in the range of 0-10 will be in the 0th index
> and the 0th index is always the at list[0]. However, for lists, the order that the items will appear isn't 
> the same. So dict[0] is NOT always the 0th values. EX. {2: 1, 0: 10}
> The keys are not sorted but with the bucketing technique with lists, they are in order. 
> The reason the order matters is because, when putting the values into the graph, the order the keys are in matters
> since that determines the bars and how they will look.

Can you avoid a loop?
> No, both the loop for iterating through the files and looping through length of the list are both needed

Can you avoid a function call?
> No.

Can you avoid repetitive code?
> Yes, the .extend could be avoided by using dictionaries however, that would also come at a cost
> I considered and implemented using dicts rather than a list and then sorting the dict however, without the use
> of any external libraries like the collections and sorted dict, the memory cost is too great of a trade off to 
> actually implement it. Or, you could implement a resize of sort. Where rather than potentially calling .extend() a 
> large amount of times, you resize it to its own length * 2. However, this could potentially use excess memory that won't
> every be used, so if you had a large file and the values Or the values in the file are in ascending order then it would
> be better to resize it so you just had length * 2. However, if the values are ever in descending order, then this current way
> of calling extend will always be better. 

Do you understand every line of your code?
> Yes
"""

from math import ceil;
import numpy as np
import matplotlib.pyplot as plt

"""
* I create a list called "snow" and will use the bucketing technique 
* to get the values and assoicate them with the number of occurances
->
* We open the file with 'with' to automatically close the file 
* then we get value on the currnet line and round it to the nearest 10th then divide by 10
* after, we subtract it by 1 to get it's respective index (to start the array at 0) 
* Then, we check if the index is already in the array by checking if the index is less than the size of the array
* YES -> Increment that respective index
* NO  -> add the missing elements inbetween len(snow) and num with the default value of 0
----
Note
----
* We add 1 for the formula since num has already 1 subtracted since we're using it as an index

* Then we get the string text for the ranges
* We create the graph
"""
def graphSnowFall(t):
    snow = []
    with open(t, "r") as file:
        for line in file:
            # Round to the nearest 10's -> divide by 10 and subtract 1 for the index
            num = ceil(int(line) / 10) - 1;
            if num < len(snow):
                snow[num] += 1;
            else:
                # Because we are using the index of the num (original num - 1) we have to add 1 at the end
                snow.extend([0] * (num - len(snow) + 1));
                snow[num] = 1;
    
    ranges = [f'{n*10 if n == 0 else n*10+1} - {(n+1) * 10}' for n in range(0, len(snow))];
    # Create the Graph
    plt.bar(ranges, snow);
    plt.xlabel("Ranges");
    plt.ylabel("Occurrences");
    plt.title("Snowfall Accumulation");
    plt.show();
        
#Testing
graphSnowFall("Snowfall_Test.txt");