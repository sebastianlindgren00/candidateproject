import './Controller.css';
import './App'
import {useState, useEffect} from 'react'
import { useSearchParams } from 'react-router-dom';
import { Joystick } from 'react-joystick-component'; // Package source: https://www.npmjs.com/package/react-joystick-component

function Controller() {
    const [searchparams] = useSearchParams() // Used to search in the URL
    const [scrOrientation, setScreenOrientation] = useState(window.screen.orientation)

    const baseColor = 'radial-gradient(circle, rgba(0,0,0,1) 0%, rgba(70,70,70,1) 69%, rgba(101,101,101,1) 100%)'
    const stickColor = 'radial-gradient(circle, rgba(16,187,0,1) 0%, rgba(31,147,0,1) 71%, rgba(3,62,0,1) 100%)'
    

    scrOrientation.addEventListener('change', function() { //When screen orientation is changed
        setScreenOrientation(window.screen.orientation)
        if(scrOrientation.type === 'landscape-primary' || scrOrientation.type === 'landscape-secondary'){
            document.getElementById('orientationDisclaimer').style.display = 'none'
            document.getElementById('jStick').style.display = 'flex'
            document.getElementById('fireButton').style.display = 'flex'
        }else{
            document.getElementById('orientationDisclaimer').style.display = 'flex'
            document.getElementById('jStick').style.display = 'none'
            document.getElementById('fireButton').style.display = 'none'
        }
    })

    useEffect(()=>{ // When page loads
        if(scrOrientation.type === 'landscape-primary' || scrOrientation.type === 'landscape-secondary'){
            document.getElementById('orientationDisclaimer').style.display = 'none'
            document.getElementById('jStick').style.display = 'flex'
            document.getElementById('fireButton').style.display = 'flex'
        }else{
            document.getElementById('orientationDisclaimer').style.display = 'flex'
            document.getElementById('jStick').style.display = 'none'
            document.getElementById('fireButton').style.display = 'none'
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
                move={move}
                stop={stop}
                start={start}
            />
        </div>
        );
    }

    // Called by joystick
    const handleMove = (e) => { 
        console.log(e);
      };
      const handleStop = (e) => {
        console.log(e);
      };
      const handleStart = (e) => {
        console.log(e);
      };

      //Called by fireButton
      const handleShoot = (e) =>{
        console.log(e);
      }


    return(
        <div className="Controller">
            {/* Developer tools*/}
            <div className="devBox">
                <p style={{color:'white'}}>UserID: {searchparams.get('userID')}</p>
                <p style={{color:'white'}}>UserName: {searchparams.get('userName')}</p>
                <p style={{color:'white'}}>Screen orientation: {scrOrientation.type}</p> {/*Does not update, needs to be fixed*/}
            </div>
            {/**/}
            <div className="controllsContainer">
                {joystickController(handleMove, handleStart, handleStop)}
                <h1 id='orientationDisclaimer'>Rotera mobilen för att spela</h1>
                <span id='fireButton' onClick={handleShoot}>FIRE</span>
            </div>

        </div>
    );
}

export default Controller;