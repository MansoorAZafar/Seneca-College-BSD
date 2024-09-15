/********************************************************************************** 
* BTI425 – Assignment 1
* I declare that this assignment is my own work in accordance with Seneca Academic Policy.
* No part of this assignment has been copied manually or electronically from any other source
* (including web sites) or distributed to other students.
*
* Name: Mansoor Ahmad Zafar Student ID: 100503226 Date: 2024-01-27
*
*
******************************************************************************
**/

//Global Variables
let locations = [];
let len = 0;
const MAX_LOCATIONS = 50;
//Almost completed URLS
const FLAG_URL = `https://openweathermap.org/images/flags/`;
const ICON_URL = `https://openweathermap.org/img/wn/`

function populateCities(location)
{
    let URL = `http://api.openweathermap.org/data/2.5/find?q=${location}&units=metric&cnt=${MAX_LOCATIONS}&appid=70b92e58e676788891b68e4c2913235e`
    fetch(URL)
    .then(res => res.json())
    .then(data => 
    {
        // idea : return promise and have it so only resolve if len == loc.len 
        //reject if under 
        // afrer call the divpages
        if(!data || !data.list || data.list.length == 0) reportError();
        else
        {
            len = data.list.length;
            data.list.forEach(element => {
                fetch(`https://api.openweathermap.org/data/2.5/weather?id=${element.id}&lat=${element.coord.lat}&lon=${element.coord.lon}&units=metric&appid=70b92e58e676788891b68e4c2913235e`)
                .then(res => res.json())
                .then(data => 
                {
                    locations.push(data);
                    if(locations.length == len) dividePages();
                }).catch(err => console.log(err))
            })
        }
    }).catch(err => console.log(err))
    
}

function reportError() { document.querySelector("#table").innerHTML = "No results found..." }

//This function will divide the cities into length/3 amount of pages
//This function ensures that each pages has 3 items 
function dividePages()
{
    getContent(0, locations); // by default, have the content of page 1
    var length = locations.length / 3;
    let pagnation = `<ul class="pagination">`;
    for(var i = 0; i < length; ++i)
    {
        pagnation += `
        <li class="page-item" style="padding-right: 10px">
            <button onclick="getContent(${i*3})" class="page-link">${i + 1}</button>
        </li>`;
    }
    pagnation += `</ul>`;
    document.querySelector("#Pages").innerHTML = pagnation;
}

function getContent(index)
{
    // [index, index+3)

    if(len != locations.length) return reportError();
    const MAX_CONTENT = index+3 > locations.length ? locations.length : index+3; // Can only show 3 items per page
    //01d@2x.png
    let content = `
    <div>
        <div class="row">
            <div class="col">
                <table class="table table-hover" id="postsTable">
                    <tbody>
    `;
    for(let i = index; i < MAX_CONTENT; ++i)
    {
        //Variables
        let sunrise     = new Date(locations[i].sys.sunrise * 1000);
        let sunset      = new Date(locations[i].sys.sunset * 1000);
        let icon        = `${ICON_URL}${locations[i].weather[0].icon}@2x.png`;
        let nameCountry = `${locations[i].name}, ${locations[i].sys.country}`;
        let flag        = `${FLAG_URL}${(locations[i].sys.country).toLowerCase()}.png`;
        let weatherDesc = `${locations[i].weather[0].description}`;
        let temp        = `${locations[i].main.temp}`;
        let maxTemp     = `${locations[i].main.temp_max}`;
        let minTemp     = `${locations[i].main.temp_min}`;
        content += `
        <tr>
            <td><img src="${icon}"</td>
            <td>
                <b>${nameCountry}</b>
                <img src="${flag}">
                <b>${weatherDesc}</b>  <br>
                Currently it is: <b>${temp}</b> &deg;C
                The temperatures range from ${maxTemp}&deg;C to ${minTemp}&deg;C
                <br>wind: ${locations[i].wind.speed}m/s, clouds ${locations[i].clouds.all} %, ${locations[i].main.pressure} hpa</br>
                humidity: ${locations[i].main.humidity}, <br>sunset: ${sunset}</br>sunrise: ${sunrise}
                <br>Geo Coords [${locations[i].coord.lat}, ${locations[i].coord.lon}]</br>
            </td>
        </tr>`
    }
    content += `    </tbody>
                </table>
            </div>
        </div>
    </div>`

    document.querySelector("#table").innerHTML = content;
}

function setDefaultLoc()
{
    try
    {
        navigator.geolocation.getCurrentPosition((position) => 
        {
            fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${position.coords.latitude}&lon=${position.coords.longitude}&units=metric&appid=70b92e58e676788891b68e4c2913235e`)
            .then(res => res.json())
            .then(data => {
                populateCities(data.name);
            })
        })
    }catch(err)
    {
        console.log(err)
    }
}

document.addEventListener('DOMContentLoaded', () => 
{
    //Get users current loc
    setDefaultLoc();
    document.querySelector("#searchForm").addEventListener('submit', event => 
    {
        locations = [];
        event.preventDefault();
        populateCities(document.querySelector("#loc").value)
    })
})