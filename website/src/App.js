import './App.css';

// Icon for the arrow will be changed current solution is not good enough

function showInfoBox(){
  //TODO: Add rolling up and down InfoBox, very bad solution at the moment
  const iB = document.getElementById('InfoBox');
  const svg = document.getElementById('svgArrow');
  if(iB.style.marginTop === "-3.5em"){
    iB.style.marginTop = "-20em"
  }else{
    iB.style.marginTop = "-3.5em"
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

      <div className="InfoBox" id="InfoBox">
        <button id="InfoButton" type="button" onClick={showInfoBox}>
          INFO
        </button>
        <p style={{padding:"0.5em"}}>
          Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor
          incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud
          exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure
          dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.
          Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt 
          mollit anim id est laborum.
          </p>
      </div>
    </div>
  );
}

export default App;