//import "@/styles/globals.css";

import 'bootstrap/dist/css/bootstrap.min.css';
import Top from "../components/Top"

export default function App({ Component, pageProps }) {
  return (
    <div style={{backgroundColor:"gray", minHeight: "100vh"}}>  
      <Top/>
      <Component {...pageProps} />
    </div>
  )
}
