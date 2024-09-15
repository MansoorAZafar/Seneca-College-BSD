import { useState } from "react";
import DisplayLite from "../components/DisplayLite";

export default function Pagnation({ loc }) {
    console.log(`I happened`)
    const [currentPage, setCurrentPage] = useState(0);
    
    const getContent = (index) => {
        const MAX_CONTENT = index + 3 > loc.length ? loc.length : index + 3;
        return loc.slice(index, MAX_CONTENT).map((location, key) => (
            <DisplayLite key={key} location={location}/>
        ));
    }

    const dividePages = () => {
        const length  = loc.length / 3;
        const buttons = [];
        for(let i = 0; i < length; ++i) { 
            buttons.push(
                <li key={i} style={{ display: "inline-block", margin: "15px", width: "10px" }}>
                    <button onClick={() => setCurrentPage(i)}>{i+1}</button>
                </li>
            )
        }
        return buttons;
    }

    return (
        <>
            {loc.length > 0 && (
                <div>
                    <table>
                        <tbody>
                            {getContent(currentPage * 3)}
                        </tbody>
                    </table>
                    <ul>
                        {dividePages()}
                    </ul>
                </div>
            )}
        </>
    )
}
