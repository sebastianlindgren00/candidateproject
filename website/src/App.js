import logo from './logo.svg';
import './App.css';

// Icon for the arrow will be changed current solution is not good enough

function showInfoBox(){
  //TODO: Add rolling up and down InfoBox
  console.log("test")
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

      <div className="InfoBox" style={{}}>
        <button id="InfoButton" type="button" onClick={showInfoBox}>
          <svg width="20px" height="20px" viewBox="0 0 24 24" strokeWidth="2" fill="none" xmlns="http://www.w3.org/2000/svg" color="white">
          <path d="M12 21L12 3M12 3L20.5 11.5M12 3L3.5 11.5" stroke="white" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round"></path>
          </svg>
          INFO
        </button>
      </div>
    </div>
  );
}

export default App;