import { useRouter }           from "next/router";
import { useEffect, useState } from "react";
import Search                  from "../../components/Search";

export default function Display() {
    const router = useRouter();
    const info = router.query.display;
    const [location, setLocation] = useState(null);

    useEffect(() => {
        if (info) setLocation(JSON.parse(info));
    }, [info]);

    if (!location) return <div>Not yet...</div>;

    const FLAG_URL = `https://openweathermap.org/images/flags/`;
    const ICON_URL = `https://openweathermap.org/img/wn/`;

    const icon = `${ICON_URL}${location.weather[0].icon}@2x.png`;
    const nameCountry = `${location.name}, ${location.sys.country}`;
    const flag = `${FLAG_URL}${location.sys.country.toLowerCase()}.png`;
    const weatherDesc = location.weather[0].description;

    const sunrise = new Date(location.sys.sunrise * 1000).toLocaleTimeString();
    const sunset = new Date(location.sys.sunset * 1000).toLocaleTimeString();
    const temp = location.main.temp;
    const maxTemp = location.main.temp_max;
    const minTemp = location.main.temp_min;
    const wind = location.wind.speed;
    const clouds = location.clouds.all;
    const hpa = location.main.pressure;
    const humidity = location.main.humidity;
    const geoCoords = `[${location.coord.lat}, ${location.coord.lon}]`;
    const cityID    = location.id;

    return (
        <>
            <Search/>
            <table>
                <tbody>
                    <tr>
                        <td><img src={icon} alt="Weather icon" /></td>
                        <td>
                            <b>{nameCountry}</b>
                            <img src={flag} alt="Flag" />
                            <b>{weatherDesc}</b>
                            Currently it is: <b>{temp}</b> °C
                            The temperatures range from {maxTemp}°C to {minTemp}°C
                            <br/>wind: {wind}m/s, clouds {clouds}%, {hpa}hpa
                            <br/>humidity: {humidity}, <br/>sunset: {sunset}, sunrise: {sunrise}
                            <br/>Geo Coords {geoCoords}<br></br>
                            <b>CityID: </b> {cityID}
                        </td>
                    </tr>
                </tbody>  
            </table>
        </>
    );
}
