import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>SPACE DOME</h1>
        <label for="gameID">Game ID:</label>
        <input type="text" id="gameID" name="gID" placeholder="Game ID: 1234"/>
        <input type="submit" value="Submit"></input>
      </header>
    </div>
  );
}

export default App;
