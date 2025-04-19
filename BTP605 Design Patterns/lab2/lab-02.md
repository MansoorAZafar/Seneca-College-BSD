# Lab 2

## Objectives:

* Learn to adapt a program to follow the Decorator pattern
* Learn how to adjust patterns with different languages

## Background/Reading

Processing is a Java based language that allows for the creation of visual "sketches" (the name for a processing program).  p5.js is the JavaScript based version of processing.  The easiest way to think about p5.js is to think of it as a JavaScript drawing library.  In this assignment, you will be altering a p5.js sketch to follow the decorator pattern.

Read the sections referring to Decorators in the following:

* [Learning JavaScript design patterns](https://github.com/addyosmani/essential-js-design-patterns)
* JavaScript patterns by Stoyan Stefanov      (available through library)


## Initial Sketch:

### Files:

* index.html - Do not change this file.  To run the sketch simply open the index.html file inside a modern web browser.
* p5.min.js - the P5.js library.  Do not alter this file.
* decorator.js - All your work will go into this file.  There are two functions at the bottom (setup() and draw()) that should NOT be modified in anyway.

### Description

The initial sketch in your repository contains a function called Label which allows for the creation of a Label object.   A Label is simply a text string that can have a border.  There are three styles of border, a border (thin and rectangular), a thick border (thick lines, rectangular) and a dots border (surrounds label with red dots).

There are 4 buttons and a set of radio buttons to select a label.  Initially the sketch does the following:

* Click on the radio button selects one of the 5 labels.  
* Clicking any of the "add" buttons will toggle that type of border on the label.  
* Clicking any of the "add buttons twice will remove that style of border.  
* Clicking The remove last button is not used in initial sketch.

The borders are drawn in the same place so if you add a thick border you won't see the thin border (even though it will be there).

## Alter the Sketch:

Alter the sketch to follow the decorator pattern. To do so make the following changes:

* Create a decorator for each style of border (thick, thin, dots) (hint, use the available code in Label's original draw() function to help you do the drawing part.. you shouldn't need other functions to do this)
* Alter the Label so that it is flagless.  A Label is just a label.  It should have a text string with a draw() method that will draw that text string in the correct position.  It should not contain any code to draw borders or any flags to indicate if a border should be drawn.
* Do not use a list of decorators.  they should follow the idea of a "wrapper"
* Modify the "Add" buttons:
  * Clicking any of the "Add" buttons adds a border of that style to the selected label.
  * When a border is added, it should not be drawn on top of other borders.  It should expand (amount to expand is up to you... just make sure it is clear when you add a border) to encompass all previously added borders and the original label.
* Add one other type of decoration to the label.  This decorator can be anything you want.  You can be creative about it.  It can be a border... but it doesn't have to be a border.  The decorator must:
  * involve a visual display
  * allow multiple decorators to be added and all decorators should be distinctly visible
  * add a button to add the decorator on click
  * decorator must be visually linked to the label it decorates (ie it needs to be on/near the label it is decorating.
  


### Challenge:

* Make the "Remove Last" button work.  This button allows you to remove the most recently added border.
  
### Demo:

* Create a video demo of your code. In the video be sure to capture the following:
  * apply at least 2 of each type of border to at least 2 different labels
  * apply borders to one label, select a different label apply some borders, go back to first label apply more borders
  * If you did the challenge, make sure you demonstrate removing the last border on two different labels.
  * demonstrate the use of your custom decorator.

## References:

* JavaScript the good parts by Douglas Crockford  (available through library)
* JavaScript the definitive guide - David Flanagan (available through library)

### Submission:

* Create a link to your video into lab2.md
* push your code into your repo.  Note that if I clone your repo and open the index.html file in your lab2 folder, your code should work, so make sure you are placing your code correctly into the repo.


## Rubrics

| | Level 0 | Level 1| Level 2| Level 3| Level 4|
|---|---|---|---|---|---|
| Demonstration of Pattern| No demo video submitted and No program submitted (just original source in repo) |  Working Demo Video provided and code submitted but GoF pattern was not followed in any meaningful way or Demo Video does not fully demonstrate usage as per requirement or code does not fully work (for example can't put borders on every label or only some borders work but not others... NOTE: these are just examples... there are other possible issues) | Working Demo Video provided and code submitted to GitHub, and there was an attempt implementation following GoF patterns but the implementation had major flaws or crucial elements were ignored or not implemented. |Working Demo Video provided and code submitted to GitHub  but there are minor flaws to how the pattern was implemented =| Working Demo Video provided and code submitted to GitHub and code follows pattern |

