import React from 'react'
import './App.css';
import { createSearchParams,useNavigate } from "react-router-dom";
import {useState} from 'react';
import {useEffect} from 'react';
import useWebSocket, { ReadyState } from "react-use-websocket"


function App() {

  const [userID, setUserId] = useState('inital')
  const [userName, setUserName] = useState('inital')
  const [srvAuth, setSrvAuth] = useState('not authorized')

  var infoBoxStatus = true; // Is the info box opened, when the page loads in this is incorrect but the var needs to be true for the if statement to work



  const socketUrl = 'wss://omni.itn.liu.se/ws/'; // Omni websocket

  const { sendJsonMessage, lastJsonMessage, readyState } = useWebSocket(
    socketUrl,
    {
      share: false,
      shouldReconnect: () => true,
    },
  )

  // Run when the connection state (readyState) changes
  useEffect(() => {
    console.log("Connection state changed")
    if (readyState === ReadyState.OPEN) {
      sendJsonMessage({
        token: "bdf3f64d-20fa-4687-bb04-5e86343d90d2"
      })
    }
  }, [readyState])

  

  // Run when a new WebSocket message is received (lastJsonMessage)
  useEffect(() => {
    console.log(`Got a new message: ${JSON.stringify(lastJsonMessage)}`)
    if(JSON.stringify(lastJsonMessage).includes('Authorized')){
          setSrvAuth('authorized')
    }
  }, [lastJsonMessage])

  window.onload=function(){ //TODO: Fix bug that disables the opening and closing of the info box when navigating back to this page
    document.getElementById("InfoButton").addEventListener('click', function(){
      const iB = document.getElementById('InfoBox');
      if(infoBoxStatus){
        iB.style.marginTop = "-20em"
        infoBoxStatus = false;
      }else{
        iB.style.marginTop = "-3.5em"
        infoBoxStatus = true;
      }
    })
  }


  // Source for generateUUID(): https://stackoverflow.com/a/8809472 , acquired 2024-03-20
  function generateUUID() { // Public Domain/MIT
    var d = new Date().getTime();//Timestamp
    var d2 = ((typeof performance !== 'undefined') && performance.now && (performance.now()*1000)) || 0;//Time in microseconds since page-load or 0 if unsupported
    return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
        var r = Math.random() * 16;//random number between 0 and 16
        if(d > 0){//Use timestamp until depleted
            r = (d + r)%16 | 0;
            d = Math.floor(d/16);
        } else {//Use microseconds since page-load if supported
            r = (d2 + r)%16 | 0;
            d2 = Math.floor(d2/16);
        }
        return (c === 'x' ? r : (r & 0x3 | 0x8)).toString(16);
    });
}

  const navigate = useNavigate();
 
  useEffect(() => { // Is called every render cycle, because of this an if statement is used before the user is navigated to the controller page
    console.log('State updated: \n', userID,' : ', userName);
    console.log('Client is ',srvAuth);

    if(userID != 'inital' && userName != 'inital' && userName !='' && srvAuth == 'authorized'){ // The ID and Name must be separate from the inital values, and the username cannot be blank

      sendJsonMessage({
        userID: userID,
        userName: userName
      })
      navigate({
          pathname: '/controller', 
          search: createSearchParams({ // Creates and extension to the URL which is used by Controller.js to read ID and Name
            userID:userID,
            userName:userName
          }).toString()
      })
    }
  }, [userID, userName])

  const updateUserValues = () => { // Set user states
      setUserId(generateUUID())
      setUserName(document.getElementById("userName").value)
  }


  return (
    <div className="App">
      <header className="App-header">
        <h1>SPACE DOME</h1>
        <label htmlFor="userName">Namn:</label>
        <input type="text" id="userName" name="uName" placeholder="Anders Andersson"/>
        <input type="submit" value="Gå med" onClick={updateUserValues}></input><br></br>
      </header>
      <div className="InfoBox" id="InfoBox">
        <button id="InfoButton" type="button">
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