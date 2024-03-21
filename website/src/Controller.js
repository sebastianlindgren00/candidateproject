import './Controller.css';
import './App'
import {useState, useEffect} from 'react'
import { useSearchParams } from 'react-router-dom';
import { Joystick } from 'react-joystick-component'; // Package source: https://www.npmjs.com/package/react-joystick-component

function Controller() {
    const [searchparams] = useSearchParams() // Used to search in the URL
    var scrOrientation = window.screen.orientation // Simplification
    console.log(scrOrientation)

    // Bugs while loading page is present and must be fixed

    scrOrientation.addEventListener('change', function() {console.log(scrOrientation)})

    scrOrientation.onchange = function() {
        if(document.getElementById("jStick") != null){
            if(scrOrientation.type =='portrait-primary'){
                document.getElementById("jStick").style.display = 'none'
                document.getElementById("orientationDisclaimer").style.display ='flex'
            }else if(scrOrientation.type =='landscape-primary'){
                document.getElementById("jStick").style.display = 'flex'
                document.getElementById("orientationDisclaimer").style.display ='none'
            }
        }
    }
    
    function joystickController({
        move,
        start,
        stop
    }){
        return(
        <div id = 'jStick'>
            <Joystick
                size={100}
                baseColor={'green'}
                stickColor={'red'}
                throttle={200}
                move={move}
                stop={stop}
                start={start}
            />
        </div>
        );
    }

    const handleMove = (e) => {
        console.log(e);
      };
      const handleStop = (e) => {
        console.log(e);
      };
      const handleStart = (e) => {
        console.log(e);
      };
      const handleShoot = (e) =>{

      }


    return(
        <div className="Controller">
            {/* Developer tools
            <label htmlFor="devBox" style={{color:'white'}}> Developer Box
                <div className="devBox">
                    <p style={{color:'white'}}>UserID: {searchparams.get('userID')}</p>
                    <p style={{color:'white'}}>UserName: {searchparams.get('userName')}</p>
                    <p style={{color:'white'}}>Screen orientation: {scrOrientation}</p>
                </div>
            </label>
            */}
            {joystickController(handleMove, handleStart, handleStop)}
            <h1 id='orientationDisclaimer'>Rotera mobilen för att spela</h1>

        </div>
    );
}

export default Controller;