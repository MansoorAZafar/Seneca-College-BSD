import { useRouter }           from "next/router";
import { useState, useEffect } from 'react';
import DisplayLite             from "../../components/DisplayLite";
import Search                  from "../../components/Search";

export default function CityId() {
    const router = useRouter();
    const id     = router.query.city_id;
    const [loc, setLoc] = useState(null);
    const [cache, setCache] = useState({});

    useEffect(() => {
        if (!id) return;
        if(cache[id]){
            console.log('cached :>>')
            setLoc(cache[id]);
            return;
        }
        else {
            const URL = `http://api.openweathermap.org/data/2.5/weather?id=${id}&units=metric&appid=70b92e58e676788891b68e4c2913235e`;

            fetch(URL)
            .then(res => {
                if(!res.ok) {
                    setCache(res => ({...res, [id]: null }))
                    throw new Error("Invalid");
                }
                else {
                    return res.json();
                }
            })
            .then(data => {
                console.log(data)
                setCache(res => ({...res, [id]: data }))
                setLoc(data);
            })
            .catch(err => {
                setLoc(null);
            })
        }
        

    }, [id]);

    return (
        <div>
            <Search/>
            <table>
                <tbody>
                    {loc ? ( <DisplayLite location={loc} /> ) : ( <tr><td>No Such Result Exists...</td></tr> )}
                </tbody>
            </table>
        </div>
    )
}
