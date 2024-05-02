import './Controller.css';
import './App'
import {useState, useEffect} from 'react'
import { useSearchParams } from 'react-router-dom';
import { Joystick } from 'react-joystick-component'; // Package source: https://www.npmjs.com/package/react-joystick-component
import useWebSocket, { ReadyState } from "react-use-websocket"

function Controller() {
    const [searchparams] = useSearchParams() // Used to search in the URL
    const [scrOrientation, setScreenOrientation] = useState(window.screen.orientation)
    const [boostState, setBoostState] = useState(100);
    const [teamState, setTeamState] = useState('no team')
    const [pointsState, setPointsState] = useState(0);
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

    // Incremental increase of the boost bar every 500ms, will become redundant
    useEffect(() => {
      const interval = setInterval(() => {if(boostState<=100){
        setBoostState(boostState + 0.5);
      }
      }, 100);

      if(boostState < 25){
        document.getElementById('boostButton').style.background= 'radial-gradient(circle, rgb(166, 146, 82) 0%, rgb(83, 75, 50) 90%, rgba(0,0,0,1) 100%)'
        document.getElementById('boostButton').style.color = 'lightgray'
        document.getElementById('boostButton').style.boxShadow = 'inset 0 2px 4px 0 rgba(0, 0, 0, 0.2),inset 0 3px 10px 0 rgba(0, 0, 0, 0.19)'
      }else{
        document.getElementById('boostButton').style.background= 'radial-gradient(circle, rgb(238, 184, 7) 0%, rgb(125, 96, 2) 90%, rgba(0,0,0,1) 100%)'
        document.getElementById('boostButton').style.color = 'white'
        document.getElementById('boostButton').style.boxShadow = '0 2px 4px 0 rgba(0, 0, 0, 0.2), 0 3px 10px 0 rgba(0, 0, 0, 0.19)'
      }

      //Clearing the interval
      return () => clearInterval(interval);
  }, [boostState]);
    
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
        if(JSON.stringify(lastJsonMessage).includes('Points')){
          setPointsState(parseInt(lastJsonMessage.Points))
        }
        if(JSON.stringify(lastJsonMessage).includes('Boost')){
          setBoostState(parseInt(lastJsonMessage.Boost))
        }

        if(JSON.stringify(lastJsonMessage).includes('Team')){
          if(parseInt(lastJsonMessage.Team) == 1){
            setTeamState("Röd")
          }else{
            setTeamState("Grön")
          }
        }
      }, [lastJsonMessage])


    scrOrientation.addEventListener('change', function() { //When screen orientation is changed
        setScreenOrientation(window.screen.orientation)
        if(scrOrientation.type === 'landscape-primary' || scrOrientation.type === 'landscape-secondary'){
            document.getElementById('orientationDisclaimer').style.display = 'none'
            document.getElementById('jStick').style.display = 'flex'
            document.getElementById('fireButton').style.display = 'flex'
            document.getElementById('boostButton').style.display = 'flex'
            document.getElementById('controlPanel').style.display = 'flex'
        }else{
            document.getElementById('orientationDisclaimer').style.display = 'flex'
            document.getElementById('jStick').style.display = 'none'
            document.getElementById('fireButton').style.display = 'none'
            document.getElementById('boostButton').style.display = 'none'
            document.getElementById('controlPanel').style.display = 'none'
        }
    })

    useEffect(()=>{ // When page loads
        if(scrOrientation.type === 'landscape-primary' || scrOrientation.type === 'landscape-secondary'){
            document.getElementById('orientationDisclaimer').style.display = 'none'
            document.getElementById('jStick').style.display = 'flex'
            document.getElementById('fireButton').style.display = 'flex'
            document.getElementById('boostButton').style.display = 'flex'
            document.getElementById('controlPanel').style.display = 'flex'
        }else{
            document.getElementById('orientationDisclaimer').style.display = 'flex'
            document.getElementById('jStick').style.display = 'none'
            document.getElementById('fireButton').style.display = 'none'
            document.getElementById('boostButton').style.display = 'none'
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
                size={120}
                stickSize={70}
                baseColor={baseColor}
                baseShape='square'
                stickColor={stickColor}
                throttle={200}
                controlPlaneShape='axisX'
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
          move: (e.x*0.03),
          userID: searchparams.get('userID')
        })
        console.log(JSON.stringify(
          {move: (e.x*0.03),
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
          action: "fire",
          userID: searchparams.get('userID')
        })
        console.log(JSON.stringify(
          {action: "fire",
           userID: searchparams.get('userID')}
        ))
      }

      //Called by boostButton
      const handleBoost = (e) =>{ //Cannot be called while steering with the joystick, must be fixed
        //console.log(e.type);
        if(boostState >=25){
          setBoostState(boostState-25)
          sendJsonMessage({
            action: "boost",
            userID: searchparams.get('userID')
          })
          console.log(JSON.stringify(
            {action: "boost",
             userID: searchparams.get('userID')}
          ))
        }
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
                <p style={{marginBottom:"-0.5%"}}>Boost</p>
                  <div style={{marginBottom:"5%",
                                    boxShadow: "0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19)"}} className="boardContent" id="boardContent">
                      <div style={{height:"1.5em", width:"100%", display:"flex", alignItems: "center",justifyContent:"flexStart",
                                        boxShadow: "inset 0 4px 8px 0 rgba(0, 0, 0, 0.2),inset  0 6px 20px 0 rgba(0, 0, 0, 0.19)"}}>
                        <div style={{height:"90%", width:boostState+"%",backgroundColor:"red",display:"flex",
                                          boxShadow: "inset 1px 0.5px 0.5px 1px rgba(0, 0, 0, 0.3)"}}>
                        </div>
                      </div>
                  </div>
                  <div className="boardContent" id="boardContent">
                      <p style={{marginLeft:"1%"}}>Poäng: {pointsState}</p>
                  </div>
                  <div className="boardContent" id="boardContent">
                      <p style={{marginLeft:"1%"}}>Lag: {teamState}</p>
                  </div>
                </div>
                <div className="buttons">
                    <span id='fireButton' onTouchStart={handleShoot}>FIRE</span>
                    <span id='boostButton' onTouchStart={handleBoost}>BOOST</span>
                </div>
            </div>
            <h1 id='orientationDisclaimer'>Rotera mobilen för att spela</h1>
        </div>
    );
}

export default Controller;