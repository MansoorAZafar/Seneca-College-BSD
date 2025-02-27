import YournameComp from "../components/YournameComp";
import YournameCrs from "../components/YournameCrs";

export default function Home() {
  return (
    <>
      <YournameComp/>
      <YournameCrs props={["BTI425", "BTN415", "BTC440", "BTS435", "BTP405"]}/>
    </>
  )
}

