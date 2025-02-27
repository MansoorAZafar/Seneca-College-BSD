require('dotenv').config();
const Sequelize = require('sequelize');

// set up sequelize to point to our postgres database
let sequelize = new Sequelize(process.env.DB_NAME, process.env.USER, process.env.PASSWORD, {
  host: process.env.HOST,
  dialect: 'postgres',
  port: 5432,
  dialectOptions: {
    ssl: { rejectUnauthorized: false },
  },
});

const Theme = sequelize.define(
    'Theme',
    {
      id: {
        type: Sequelize.INTEGER,
        primaryKey: true, // use "project_id" as a primary key
        autoIncrement: true, // automatically increment the value
      },
      name: Sequelize.STRING,
    },
    {
      createdAt: false, // disable createdAt
      updatedAt: false, // disable updatedAt
    }
  );

  const Set = sequelize.define(
    'Set',
    {
      set_num: {
        type: Sequelize.STRING,
        primaryKey: true, // use "project_id" as a primary key
      },
      name: Sequelize.STRING,
      year: Sequelize.INTEGER,
      num_parts: Sequelize.INTEGER,
      theme_id: Sequelize.INTEGER,
      img_url: Sequelize.STRING,
    },
    {
      createdAt: false, // disable createdAt
      updatedAt: false, // disable updatedAt
    }
  );

  Set.belongsTo(Theme, {foreignKey: 'theme_id'})

  const setData = require("../data/setData");
  const themeData = require("../data/themeData");
  let sets = [];

function initialize()
{
  return new Promise(async (resolve, reject) =>{
    try
    {
      await sequelize.sync();
      resolve()
    }catch(err)
    {
      console.log(err)
      reject(`unable to sync the database...`)
    }   
  })
}

function getAllSets()
{
  return new Promise(async (resolve,reject)=>{
    try{
      Set.findAll({include:[Theme]}).then((data) =>{
        resolve(data)
      })
    }catch(err)
    {
      console.log(err)
      reject("couldn't get all sets...")
    }
  })
}

function getSetsByNum(setNum)
{
  return new Promise(async (resolve,reject) =>{
    try{
      Set.findAll({where: {set_num: setNum}, include: [Theme]}).then((data) => {
        resolve(data[0])
      })
    }catch(err)
    {
      console.log(err)
      reject(`unable to find requested set`)
    }
  })
}

function getSetsByTheme(theme)
{
  return new Promise(async (resolve,reject) =>{
    try{
      let data = Set.findAll({include: [Theme], where: {'$Theme.name$': {[Sequelize.Op.iLike]: `%${theme}%`}}});
      resolve(data)
    }catch(err)
    {
      console.log(err)
      reject(`unable to find requested set`)
    }
  })
}

function addSet(setData)
{
  return new Promise(async (resolve, reject)=>{
    try{
      let _themeID = await getSetsByTheme(setData.theme)
      await Set.create(setData)
      resolve();
    }catch(err)
    {
      console.log(err)
      reject("bad set")
    }
  })
}

function getAllThemes()
{
  return new Promise(async (resolve, reject)=>{
    try{
      let themes = Theme.findAll().then((data) =>{
        resolve(data)
      })
    }catch(err)
    {
      console.log(err)
      reject("themes don't exist")
    }
  })
}

function editSet(set_num, setData)
{
  return new Promise(async (resolve,reject)=>{
    try{
      console.log("--------------");
      console.log(set_num);
      console.log("--------------")
      await Set.update(setData, {
        where: {
          set_num : set_num
        }
      })
      resolve()
    }catch(err)
    {
      console.log(err)
      reject(err)
    }
  })
}

function deleteSet(set_num)
{
  return new Promise(async (resolve, reject)=>{
    try{
      await Set.destroy({
        where: {set_num: set_num},
      })
      resolve()
    }catch(err)
    {
      reject(err)
    }
  })
}

module.exports = { initialize, getAllSets, getSetsByNum, getSetsByTheme, addSet, getAllThemes, editSet, deleteSet }