/********************************************************************************** 
WEB322 – Assignment 1* I declare that this assignment is my own work in accordance with Seneca Academic Policy.
* No part of this assignment has been copied manually or electronically from any other source
* (including web sites) or distributed to other students.
** Name: Mansoor Ahmad Zafar Student ID: 100503226 Date: 2023-09-07 (September 7, 2023)
*********************************************************************************/
const readline = require('readline');
const read = readline.createInterface(process.stdin, process.stdout);
const fs = require('fs');
const { dir } = require('console');

function longestWord(arr)
{
    index = 0;
    for(var i = 0; i < arr.length; ++i)
    {
        if(arr[index].length < arr[i].length)
        {
            index = i
        }
    }
    return index
}

function sort(arr)
{
    for(var i = 0; i < arr.length-1; ++i)
    {
        for(var j = i; j < arr.length; ++j)
        {
            if(arr[i] < arr[j])
            {
                let tmp = arr[i]
                arr[i] = arr[j]
                arr[j] = tmp
            }
        }
    }
    return arr
}

function mostOccur(arr)
{   
    var occur = 0
    var index = 0
    for(var i = 0; i < arr.length-1; ++i)
    {
        var count = 1
        for(var j = i+1; j < arr.length; ++j)
        {
            if(arr[j] == arr[i])
            {
                count++
            }
        }
        if(count >= occur)
        {
            index = i
            occur = count;
        }
    }
    //3 words repeat 11 times (amet, sit, in)
    //since the output from the assignment 1 was amet
    //I assumed it just uses the last largest occurances
    //aka since amet occurs 11 times and it appears after checking sit and in
    //I assumed we just use amet 
    console.log(`Most Repeated Word: ${arr[index]} - ${occur}`)
}

read.question(`Do you wish to process a File (f) or directory (d): `, function(response){
    if(response.toLowerCase() != 'd' && response.toLowerCase() != 'f')
    {
        console.log('Invalid Selection')
        read.close()
    }
    else if(response.toLowerCase() == 'f')
    {
        read.question(`Enter the FILE name: `, function(filename)
        {
            fs.readFile(filename, function(err, fileData)
            {
                if(err) console.log(err.message)
                else
                {
                    let fileContent = fileData.toString().replace(/\s+/g, ' ');
                    numOfChar = fileContent.length
                    console.log(`Number of Charactrs (including spaces): ${numOfChar}`)
                    let fileContentArr = fileContent.replace(/[^\w\s\']/g, "").split(' ');
                    words = fileContentArr.length
                    console.log(`Number of Words: ${words}`)
                    index = longestWord(fileContentArr)
                    console.log(`Longest Word: ${fileContentArr[index]}`)
                    mostOccur(fileContentArr)
                }
            })
           read.close()
        })
    }
    else
    {
        read.question(`Enter the DIRECTORY name: `, function(dirname)
        {
            fs.readdir(dirname, function(err, dirData)
            {
                dirData = sort(dirData)
                console.log(dirData)
                for(var i = 0; i < dirData.length; ++i)
                {
                    let name = dirData[i]
                    let filepath = `\\${dirname}\\${dirData[i]}`;
                    fs.stat(`${__dirname}\\${filepath}`, function(err, stats)
                    {
                        if(err) console.log(err.message)
                        else
                        {
                            console.log(`${name}: ${stats.size} bytes`)
                            //zucchini always came as 1360 bytes
                        }
                    })
                }
                read.close()  
            })
        })
    }
});