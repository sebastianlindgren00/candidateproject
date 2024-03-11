import logo from './logo.svg';
import './App.css';

// Icon for the arrow will be changed current solution is not good enough

function showInfoBox(){
  //TODO: Add rolling up and down InfoBox, very bad solution at the moment
  const iB = document.getElementById('InfoBox');
  const svg = document.getElementById('svgArrow');
  if(iB.style.height === "3.5em"){
    iB.style.transitionProperty = "margin-top"
    iB.style.height = "20em"
    iB.style.marginTop = "-20em"
    svg.style.transform = "rotate(0)"
    console.log(iB.style.height)
  }else{
    iB.style.transitionProperty = "height"
    iB.style.height = "3.5em"
    iB.style.marginTop = "-3.5em"
    svg.style.transform = "rotate(3.142rad)"
    console.log(iB.style.height)
  }
}


function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>SPACE DOME</h1>
        <label htmlFor="gameID">Game ID:</label>
        <input type="text" id="gameID" name="gID" placeholder="1234"/>
        <input type="submit" value="Submit"></input><br></br>
      </header>

      <div className="InfoBox" id="InfoBox" style={{}}>
        <button id="InfoButton" type="button" onClick={showInfoBox}>
          <svg id ="svgArrow" width="20px" height="20px" viewBox="0 0 24 24" strokeWidth="2" fill="none" xmlns="http://www.w3.org/2000/svg" color="white">
          <path d="M12 21L12 3M12 3L20.5 11.5M12 3L3.5 11.5" stroke="white" strokeWidth="4" strokeLinecap="round" strokeLinejoin="round"></path>
          </svg>
          INFO
        </button>
      </div>
    </div>
  );
}

export default App;