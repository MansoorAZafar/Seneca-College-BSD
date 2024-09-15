import { useRouter }           from "next/router";
import { useState, useEffect } from 'react';
import Search                  from "../../components/Search";
import Pagnation               from "@/components/Pagnation";

export default function Id() {
    const router            = useRouter();
    const { id }            = router.query;
    const MAX_LOC           = 50;
    const [loc, setLoc]     = useState(null);
    let [cache, setCache]   = useState({});
    
    useEffect(() => {
        if (!id) return;
        if(cache[id]) {
            console.log('cache has it :>')
            setLoc(cache[id]);
            return;
        }
        else
        {
            const URL = `http://api.openweathermap.org/data/2.5/find?q=${id}&units=metric&cnt=${MAX_LOC}&appid=70b92e58e676788891b68e4c2913235e`;
            fetch(URL)
            .then(res => {
                if(!res.ok) {
                    setCache(res => ({...res, [id]:null}))
                    throw new Error("Invalid");
                }
                else {
                    return res.json();
                }
            })
            .then(data => {
                setCache(res => ({...res, [id]: data}));
                console.log("HELO")
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
            {loc !== null && loc.list.length > 0 ? ( <Pagnation loc={loc.list}/> ) : ( <p>No Such Result Exists...</p> )}
        </div>
    )
}
