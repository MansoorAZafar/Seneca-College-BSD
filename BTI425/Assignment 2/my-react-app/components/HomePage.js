import DisplayLite from './DisplayLite'
import Search     from './Search';
import {useState, useEffect} from 'react';

export default function HomePage() {
  const [loc, setLoc] = useState(null);

  useEffect(() => {
      navigator.geolocation.getCurrentPosition((position) => 
      {
        fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${position.coords.latitude}&lon=${position.coords.longitude}&units=metric&appid=70b92e58e676788891b68e4c2913235e`)
        .then(res => res.json())
        .then(data => {
          setLoc(data);      
        }).catch(err => console.log(err))
      })
  }, [])

  return (
    <div>
      <Search/>
      <table>
        <tbody>
          {loc !== null ? (
            <DisplayLite location={loc}/>
          ) : (
            <tr><td>Loading...</td></tr>
          )}
        </tbody>
      </table>
    </div>
  );

  
}
