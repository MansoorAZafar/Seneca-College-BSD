# Lab 2

Based on what you did in class, describe an algorithm to sort a deck of numbers

An algorithm to sort a deck of numbers would be merge sort. Layout the cards as a grid and then divide them by their rows, for each row you can divide the cards by halves until they become sortable just by looking at them wihtout having to think. Then just 'merge' / put together the piles of cards together sorting them along the way. Then, just repeat this for the rows and merge them together as you repeat the steps. Thus, sorting the entire deck of cards in an easy and fast way. 

### Members
- Mansoor Zafar
- Joseph Chu
- Kosta Velev

## In-Class Discussion part


Sorting many numbers

Joespeh
	- he had a 'pivot' in which he put all the numbrs greater above and all the numbers lesser below 
	- 3:10 min 

Kosta
	- spread it out and selectively sort each row 
	- 2:51 min
Mansoor 
	- Go through each one and put in higher lower 
		3:50 min
	
Merging lists

as a group discuss the process of merging sorted vs unsorted lists
	-> sorting on a sorted list 
	-> sorting on an unsorted list 
	
- Merging a unsorted list requires a lot of steps and moving cards around each other. For instance, if we had 1 5 6 8 and the other half had 2 3 9 7 we would merge them together and have to put them in the proper placements. Whereas using a sorted list, we could just put them together without having to worry about placing them in the right area rather, we could just push the piles together. However, this is under the assumption you are using 1 gaint sorted list. If you had multiple sorted lists then the time taken would be similar to merging completely unsorted lists but still different as when comparing the inner lists, you don't need to compare it to itself. 
	Ex.
		[1, 8, 9, 10] [2, 4, 15, 19]
		
	As their own lists, they are sorted and so when comparing them against itself, you don't need to worry about their positions, but when merging it with another list, you have to swap around mis-matching positons to be correct.
	
	1:30~

Partitioning
	
Sorting the small piles became a lot faster as the piles shortened in length. As they became shorter, it was easier and much faster seperating the larger and smaller values. During the beginning, it took a long amount of time to seperate the larger and smaller numbers but then as we kept breaking it down, it kept becoming faster and faster to seperate a the numbers. 

2:11~
 
Come up with the fastest way to sort
	-> The best idea we came up with was to simply spread out the cards as a grid and sort each row as a sorted row and then from there merge them together. It was useful to put them as a grid as we could then see the entire grid easily. Joesph liked stacking them ontop of each other since then merging them became easier and nicer to work with. However, it was slow to just randomly pick the cards out from the deck without spreading them out as a grid and just trying to sort from there. 
	
The best way to sort a set of numbers on a paper is to lay them out as a grid and sort each row together and then merge from there. As this allows you to have an easier time seeing which values need to go where and gives an easier time merging them. 
	
	1:30~
	1:45~
	1:25~
