"""
Why did you choose a DS?
> I chose a dictionary since for every unique word, we want to
> append the line number in which the word appears. This functionality 
> is a {key, value} pair property. Which matches using a dictionary precisely.

Can you avoid a loop?
> You could avoid a nested loop but at the cost of memory and still having a second loop exist. Instead of having a nested for loop
> that splits the words then loops through that and adding the key and values there,
> you could just have a list called 'words' that just stores the splitted words for each line
> alongside having a indexes list that stores the line numbers 
> Then outside of the first loop, loop through the words and respectively assign the indexes

Can you avoid a function call?
> No, there's only one function that being the unit itself.

Can you avoid repitive code?
> No

Do you understand every line of your code?
> Yes
"""

"""
* Create a hashmap that will have a {string, list} 
* key:value pair
* 
* We open the file with 'with' so it automatically closes
* we loop through the file and grab the lineNumber and the line's text
* we split the text into seperate words and loop through that
* for every word in the line, we append the number
-----
Note
-----
* We use .setdefault() for 2 reasons:
*    1. Avoid if & else statements
*    2. If the key doesn't exist, it is initialized with
*       with an empty list []
"""
def wordCount(t):
    dictionary = {};
    with open(t, "r") as file:    
        for [fileLine, line] in enumerate(file):
            for word in line.split():
                dictionary.setdefault(word, []).append(fileLine);
    return dictionary;

#Testing
print(wordCount("Words_Test.txt"));
