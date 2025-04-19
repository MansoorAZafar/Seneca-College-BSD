# Code Reading
### Table of Contents
1. Video
2. Code Reading
	1. Software Chosen
	2. Files I examined
	3. First Reactions
	4. How code is organized
	5. How Invalid filenames are handled
	6. Two similarities
	7. Two differences  

## Video
https://youtu.be/mxSmVWye2Lo

## Code Reading
### Software Chosen
Chosen Software are:
1. Apache Ant
2. Mono

### 1. Files I examined 
#### Mono
For searching for the entry point for mono, I already knew due to prior C# knowledge, that the entry point will be named Program.cs. Then I looked in a random .cs file to see what convention they used for namespaces, in this case, they expanded the namespace as seen below.
```cs
namespace example 
{

}
```  
Versus, what they could have done:
```cs
namespace example;
// other code
```

The reason I did this, is because I wanted to see the general convention they were following, if the namespace was written like the 2nd example, (which is now done in more recent times) then they're most likely using top-level statements. Which if that was the case, searching for the 'main' function would be increasingly difficult as they would not have a function called main. For reference, here's an example of top-level statements vs non-top level.
```cs
//Program.cs
//Top level:
using System;
System.Console.WriteLine("Hello World!");

//Program.cs
// Not using Top Level
using System;
namespace Main 
{
	class Program 
	{
		public static void Main(String[] args) 
		{
			System.Console.WriteLine("Hello World!");
		}
	}
}
```

This allowed me to narrow it to them using main. Now, when searching I figured they're likely **not** using top-level statements, so now I just had to grep inside the root directory for the word "main" and within all files named "Program.cs". Unfortunately, I couldn't grep for public static void main as main in c# can return a Task, be an int, could be static async Task<int> Main or what-not. So I searched for Main and would check the 2 lines above and below to give me more context for the situation the word "main" is used in. So I ran this:

```bash
grep -r -i -w -C 2 -n "Main" --include="Program.cs" .
``` 

After running this, I was able to find a result that had the comment saying:
```cs
/// <summary>
/// The main entry point for the application.
/// </summary>
[STAThread]
static void Main()
{
	string[] args = new string[] { "../DbLinq-Sqlite-Sqlserver.nunit" };
	NUnit.Gui.AppEntry.Main(args);
}
```

However, there were multiple files that had the text "The main entry point for the application", so rather than just looking into this one file, I looked through all the results and found a result that had a function called "ProcessArguments". So I decided to look into this function and found the function that processes and calls the respective arguments. Snippet code:
```cs
"Options:", 
{ "h|help|?",
	"Show this message and exit",
	v => help = v != null},
... 
```

#### Apache Ant
For this one, I just used grep to find the Main file. So I just searched:
```bash
grep -r -i -n -w -C 2 "public static void main" --include="Main.java" .
```
This allowed me to directly and easily find the Main file. Which was: ./src/main/org/apache/tools/ant/Main.java. Within this file, the Main argument then calls the function called 'start', which then calls a startAnt function, which then calls processArgs which then calls the function that handles the command line arguments.


### 2. First Reactions
When I was first reviewing the files, I was very suprised and annoyed that a lot of the files share the same name of the Main of the program. (This is mainly for mono, as ant only had 1 file named Main.java). I can understand the reasoning as the respective 'Program.cs's are the 'main' for the part their in, however, it makes it harder for a user to go around and find the actual entry point into the program. Especially when they share the same comment of "The main entry point of the application". An absurd and annoying comment that misleads the user since they all cannot be the main entry for this singular application. However, for apache ant, I was pleased to see that they only had one Main.java file the word 'main', so it was very refreshing and nice. Especially they're style, it was very elegant.

### 3. Command Line Switches Organization
For apache ant, they put the function to handle command line switches in the same file as the main program, but they have they main program stored in a path like: **src/main/org/apache/tools/ant/Main.java**. They organize their code by different directories, all the code goes into the src, and the main code goes in the main directory, and so forth. As for the mono, it's in the directory: **./mcs/tools/aprofutil/Program.cs**. As for their reasoning, they organize it in a similar way (sort of). They also have all their important code within a tools directory and they store their command line switches in something called aprofutil. Which is AOT profile tool, (AOT stands for ahead-of-time compiler), so they store the main program that handles the command line in a profile tool which makes sense.


### 4. How are Invalid Filenames dealt with?
They are dealt by just having them in a different package/namespace by having them in different directories.

### 5. 2 Similarities
1. Both have their main program that handles the command line switches in a tools/ directories
2. Both use a function to print out a message rather than using the respective console prints.

```cs
//Mono
options.WriteOptionDescriptions(out);
```
```java
//Apache Ant
printUsage();
```
### 6. 2 Differences
1. Mono has multiple mains, Apache ant only has 1 Main.java with 'main'
2. Mono has less directories (34 Directories), Apache ant has more directories and seperations (36 Directories)
