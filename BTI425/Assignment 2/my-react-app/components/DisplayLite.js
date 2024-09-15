import { useRouter } from 'next/router';

export default function DisplayLite({ location }) {
    const router   = useRouter();
    const FLAG_URL = `https://openweathermap.org/images/flags/`;
    const ICON_URL = `https://openweathermap.org/img/wn/`;

    const icon = `${ICON_URL}${location.weather[0].icon}@2x.png`;
    const nameCountry = `${location.name}, ${location.sys.country}`;
    const flag = `${FLAG_URL}${location.sys.country.toLowerCase()}.png`;
    const weatherDesc = location.weather[0].description;

    const handleClick = () => {
        router.push(`/details/${JSON.stringify(location)}`);
    }

    return (
        <tr onClick={handleClick}>
            <td><img src={icon} alt="Weather icon" /></td>
            <td>
                <b>{nameCountry}</b>
                <img src={flag} alt="Flag" />
                <b>{weatherDesc}</b>
            </td>
        </tr>
    );
}
