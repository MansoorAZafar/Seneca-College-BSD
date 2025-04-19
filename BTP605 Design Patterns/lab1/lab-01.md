# Lab 1

## Due Date: Jan 19

## Partnering

You can work in a team of 2 or 3 if you wish for this lab.  However, everyone must submit their own labs.  Part of the submission will be done in class.

## Objectives:

* Learn to read source code
* Learn to the basics of OBS Studio (or if you want to use some other piece of video capture software you are welcome to do so.. but you need to learn to use one for the course)


## Background articles/Reading

Read the following:
* [Things you should never Do](http://www.joelonsoftware.com/articles/fog0000000069.html) - Joel Spolsky
* [Reading Code is Like Reading the Talmud](http://www.joelonsoftware.com/articles/fog0000000053.html) - Joel Spolsky
* Chapter 11 - a complete example of Code Reading in **Code reading : the open source perspective** by ***Spinellis, Diomidis***.  This is available through the Seneca Library portal (https://senecacollege.primo.exlibrisgroup.com/permalink/01SENC_INST/goqo0g/alma997134617003226)

## Software

* If you don't have a some type of screen capture software you can get OBS Studio here: https://obsproject.com/
* OBS Studio is available for Windows, macOS and Linux
* Video on the basics of OBS (https://web.microsoftstream.com/video/10e4ee75-5fe7-4a54-989e-e10cfe230ccd)


## Code Reading (15 marks)

Ant, Make, NAnt and XBuild are all software building tools.  You do not need to read all 4 of them.  Pick any 2 for this lab.


* https://github.com/nant/nant
* https://github.com/apache/ant
* https://github.com/mono/mono/tree/master/mcs/tools/xbuild
* https://www.gnu.org/software/make/ (alternatively you can clone the repo: ```git clone https://git.savannah.gnu.org/git/make.git```)

 
In this exercise, you will read the code for processing command-line switches and filenames in 2 of these projects.  During this process the key is to note the similarities and differences between this aspect of the code for these projects.  

For your chosen projects do the following:

* download appropriate archive
* Examine the code for processing command-line switches and file names (finding it may be first task :) ).
* Answer the following questions:

1. List the file(s) you examined when looking for command line switches. For each file explain why you chose to examine that file
1. What are your first reactions to these files when you examine them?
1. How is the code regarding command line switches organized at the method, class, and project level?
1. How are invalid filenames dealt with?
1. Describe two similarities in the code between your two chosen projects?
1. Describe two differences in the code between your two chosen projects?


## Modify the tool (5 marks)


1. Build **ONE** of the tool from the source code by following instructions in the project to verify that code is buildable.  If you want to ever modify code, start by making sure what is provided builds.  NOTE:  You cannot choose to modify make because we are doing this in class together.  Pick one of the other 3.
2. Commit the source files for the project you are going to modify into your repo (no executables or binaries).
3. Create a "hello world" program as well as whatever configuration files are needed to use your build of the tool to build the hello world program.  For example, if you chose make, you would create a makefile as well as your hello world program.
4. Add a command line switch using your names or initials of the members of your team.  If the switch is used, the build software will output the following text during the Build process "BTP605 - **all your names**". subbing in all your names with the names of every member of your team.  **This change must be made in the source code of the project and not the build configuration files.**
5. Rebuild the software with this change.
6. Commit and push the changed files into your repo.  We should have at least 2 commits in the repo... 1 commit is the original files, the second is the updated version of your files that handles the flags (we should be able to use diffs to see what you changed).
7. Create a video showing that your build works. This video needs to include the following:
     * erase any exe's of your helloworld program you might have created during testing
     * use of your modified software to build "hello world" **without** the switch you added
     * run the exe for helloworld
     * erase the exe for helloworld
     * use of your modified software to build "hello world" **with** the switch you added
     * run the exe for helloworld   
     * a brief walkthrough of what you changed and where you changed it.
     * describe briefly how you found what you needed to change.

This may be useful for you:[Intro to OBS](https://web.microsoftstream.com/video/10e4ee75-5fe7-4a54-989e-e10cfe230ccd)


## Submitting your Lab

* Capture the following video:
    * Using your modified version of the software with the appropriate switch to build hello world.
    * In your video show what and where changes were made to the original code.
* Edit the file lab1.md in your lab-set1 repo and put all your answers to the questions above
* Put your video into stream over sharepoint or as an unlisted youtube video.  ensure that permissions are set so that I can see it.
* Place the link to your video in your lab1.md file
* Push your two commits for the chosen project into project folder (commit one, is the original files as downloaded from the internet, commit two is the updated source code that handles your new flag)

## Rubrics

