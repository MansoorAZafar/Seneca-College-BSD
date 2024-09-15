import { useRouter } from 'next/router';

export default function Search() {
    const router = useRouter();

    const handleInput = (event) => {
        event.preventDefault();
        if (!event.target.elements[0].value) return;

        const value = event.target.elements[0].value.replace(/ /g, '').replace(/_/g, ',').toLowerCase();
        const path = isNaN(value) ? `/search/${value}` : `/searchCityID/${value}`;

        router.push(path);
        event.target.elements[0].value = ''; // empty the search bar
    };

    return (
        <div style={{ textAlign: 'center', marginTop: '20px' }}>
            <form onSubmit={handleInput} style={{ margin: '0 auto', marginBottom: "50px"}}>
                <input
                    type="search"
                    placeholder="Enter a City/Country or City ID"
                    style={{ width: '70%', padding: '10px', fontSize: '17px' }}
                />
                <button 
                    type="submit" 
                    style={{ width: '30%', padding: '10px', fontSize: '17px' }}>Submit</button>
            </form>
        </div>
    );
}
