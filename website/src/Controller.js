import './Controller.css';
import './App'
import {useState, useEffect} from 'react'
import { useSearchParams } from 'react-router-dom';
import { Joystick } from 'react-joystick-component'; // Package source: https://www.npmjs.com/package/react-joystick-component
import useWebSocket, { ReadyState } from "react-use-websocket"

function Controller() {
    const [searchparams] = useSearchParams() // Used to search in the URL
    const [scrOrientation, setScreenOrientation] = useState(window.screen.orientation)
    const [srvAuth, setSrvAuth] = useState('not authorized')

    const baseColor = 'radial-gradient(circle, rgba(0,0,0,1) 0%, rgba(70,70,70,1) 69%, rgba(101,101,101,1) 100%)'
    const stickColor = 'radial-gradient(circle, rgba(16,187,0,1) 0%, rgba(31,147,0,1) 71%, rgba(3,62,0,1) 100%)'
    


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

    scrOrientation.addEventListener('change', function() { //When screen orientation is changed
        setScreenOrientation(window.screen.orientation)
        if(scrOrientation.type === 'landscape-primary' || scrOrientation.type === 'landscape-secondary'){
            document.getElementById('orientationDisclaimer').style.display = 'none'
            document.getElementById('jStick').style.display = 'flex'
            document.getElementById('fireButton').style.display = 'flex'
            document.getElementById('controlPanel').style.display = 'flex'
        }else{
            document.getElementById('orientationDisclaimer').style.display = 'flex'
            document.getElementById('jStick').style.display = 'none'
            document.getElementById('fireButton').style.display = 'none'
            document.getElementById('controlPanel').style.display = 'none'
        }
    })

    useEffect(()=>{ // When page loads
        if(scrOrientation.type === 'landscape-primary' || scrOrientation.type === 'landscape-secondary'){
            document.getElementById('orientationDisclaimer').style.display = 'none'
            document.getElementById('jStick').style.display = 'flex'
            document.getElementById('fireButton').style.display = 'flex'
            document.getElementById('controlPanel').style.display = 'flex'
        }else{
            document.getElementById('orientationDisclaimer').style.display = 'flex'
            document.getElementById('jStick').style.display = 'none'
            document.getElementById('fireButton').style.display = 'none'
            document.getElementById('controlPanel').style.display = 'none'
        }
    })

    
    
    function joystickController({ // Constructs a joystick based on given parameters
        move,
        start,
        stop
    }){
        return(
        <div id = 'jStick'>
            <Joystick
                size={100}
                baseColor={baseColor}
                stickColor={stickColor}
                throttle={200}
                move={(e) => {
                    handleMove({ x: e.x, y: e.y})
                  }}
                  stop={() => {
                    handleMove({ x: 0, y: 0 })
                  }}
                start={start}
            />
        </div>
        );
    }

    // Called by joystick
    const handleMove = (e) => { 
        //console.log(e)
        sendJsonMessage({
          move: e,
          userID: searchparams.get('userID')
        })
        console.log(JSON.stringify(
          {move: e,
           userID: searchparams.get('userID')},
        ))
      };
      const handleStop = (e) => {
        //console.log(e);
        sendJsonMessage({
          move: e,
          userID: searchparams.get('userID')
        })
        console.log(JSON.stringify(
          {move: e,
           userID: searchparams.get('userID')}
        ))
      };
      const handleStart = (e) => {
        //console.log(e);
        sendJsonMessage({
          move: e,
          userID: searchparams.get('userID')
        })
        console.log(JSON.stringify(
          {move: e,
           userID: searchparams.get('userID')}
        ))
      };

      //Called by fireButton
      const handleShoot = (e) =>{ //Cannot be called while steering with the joystick, must be fixed
        //console.log(e.type);
        sendJsonMessage({
          move: e.type,
          userID: searchparams.get('userID')
        })
        console.log(JSON.stringify(
          {move: e.type,
           userID: searchparams.get('userID')}
        ))
      }


    return(
        <div className="Controller">
            {/* Developer tools
                <div className="devBox">
                    <p style={{color:'white'}}>UserID: {searchparams.get('userID')}</p>
                    <p style={{color:'white'}}>UserName: {searchparams.get('userName')}</p>
                    <p style={{color:'white'}}>Screen orientation: {scrOrientation.type}</p> {/*Does not update, needs to be fixed*/}
            {/*</div>*/}
            <div className="cPanel"  id="controlPanel">
                {joystickController(handleMove, handleStart, handleStop)}
                <div className="board" id="board">
                  <div className="boardContent" id="boardContent">
                      <p style={{marginLeft:"1%"}}>Poäng: </p>
                  </div>
                  <div className="boardContent" id="boardContent">
                      <p style={{marginLeft:"1%"}}>Lag: </p>
                  </div>
                </div>
                <span id='fireButton' onTouchStart={handleShoot}>FIRE</span>
            </div>
            <h1 id='orientationDisclaimer'>Rotera mobilen för att spela</h1>
        </div>
    );
}

export default Controller;