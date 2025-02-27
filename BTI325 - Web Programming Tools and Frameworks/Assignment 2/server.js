/********************************************************************************* 
* BTI325/WEB322 – Assignment 05
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* https://www.senecacollege.ca/about/policies/academic-integrity-policy.html
*
* Name: Mansoor Ahmad Zafar Student ID: 100503226 Date: 2023-11-19
*
* Published URL: https://bti325-assignment4.cyclic.app/
*********************************************************************************/

const legoData = require("./modules/legoSets")
const express = require('express')
const app = express()
const path = require('path')
const HTTP_PORT = process.env.PORT || 8080; //default HTTP port is 80
app.use(express.static("public"))
app.use(express.urlencoded({ extended: true }));
app.set("view engine", "ejs");

app.get('/', (req,res) => {
    //Use res.render("");
    //insetad of .html we do .ejs
    //do render('home") // dont even put file name or path
    res.render("home")
})

app.get('/lego/sets', async (req,res) => {

    if(req.query.theme)
    {
        try
        {
            let data = await legoData.getSetsByTheme(req.query.theme);
            res.render("sets", {sets: data})
        }
        catch(err)
        {
            res.status(404).render("404", {message: "Unable to find requested theme."})
        }
    }
    else
    {
        try
        {
            let data = await legoData.getAllSets();
            res.render("sets", {sets: data})
        }
        catch(err)
        {
            res.status(404).render("404", {message: "Unable to find requested theme."})
        }
    }
})

app.get('/about', (req,res) =>{
    res.render("about")
})

app.get('/lego/sets/:id', async (req,res) => {
    try
    {
        let data = await legoData.getSetsByNum(req.params.id)
        res.render("set", {set: data})
    }
    catch(err)
    {
        res.status(404).render("404", {message: "Unable to find requested set."})
    }
})

app.get('/lego/addSet', async (req,res) =>{
    try
    {
        let themes = await legoData.getAllThemes();
        res.render("addSet", { themes: themes });
    }catch(err)
    {
        res.status(404).render("404", {message: "Unable to find requested set."})
    }
})

app.post('/lego/addSet', async (req, res) =>{
    try{
        await legoData.addSet(req.body);
        res.redirect('/lego/sets')
    }catch(err)
    {
        res.render("500", { message: `I'm sorry, but we have encountered the following error: ${err}` });
    }
})

app.get('/lego/editSet/:num', async (req,res)=>{
    try
    {
        let setData = await legoData.getSetsByNum(req.params.num)
        let themeData = await legoData.getAllThemes();
        res.render("editSet", { themes: themeData, set: setData });
    }catch(err)
    {
        res.status(404).render("404", {message: err})
    }
})

app.post('/lego/editSet', async (req,res)=>{
    try{
        await legoData.editSet(req.body.set_num, req.body)
        res.redirect('/lego/sets')
    }catch(err)
    {
        res.render("500", { message: `I'm sorry, but we have encountered the following error: ${err}`});
    }
})

app.get('/lego/deleteSet/:num', async(req,res)=>{
    try{
        await legoData.deleteSet(req.params.num)
        res.redirect('/lego/sets')
    }catch(err)
    {
        res.render("500", { message: `I'm sorry, but we have encountered the following error: ${err}`});
    }
})

app.use((req,res,next) =>{
    res.status(404).render("404", {message: "I'm sorry, we're unable to find what you're looking for."})
})

legoData.initialize().then(()=>{
    app.listen(HTTP_PORT, ()=>{
        console.log(`Server Listening on: ${HTTP_PORT}`)
    })
})
