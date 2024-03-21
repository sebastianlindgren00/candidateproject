import './Controller.css';
import './App'
import {useState, useEffect} from 'react'
import { useSearchParams } from 'react-router-dom';

function Controller() {
    //TODO: Add controll buttons
    const [searchparams] = useSearchParams() // Used to search in the URL
    const [scrOrientation, setOrientation] = useState(window.screen.orientation.type)

    window.screen.orientation.addEventListener('change', function() { setOrientation(window.screen.orientation.type) })
    //window.screen.orientation.onchange = function(e) { ... }
    if(window.screen.orientation.type != 'landscape-primary' || window.screen.orientation.type != 'landscape-secondary'){
        return(
            <div className="Controller">
                <label htmlFor="devBox" style={{color:'white'}}> Developer Box
                    <div className="devBox">
                        <p style={{color:'white'}}>UserID: {searchparams.get('userID')}</p>
                        <p style={{color:'white'}}>UserName: {searchparams.get('userName')}</p>
                        <p style={{color:'white'}}>Screen orientation: {scrOrientation}</p>
                    </div>
                </label>
                <h1 id='orientationDisclaimer' style={{color:'white'}}>Rotera mobilen för att spela</h1>
            </div>
        );
    }else{
        return(
            <div className="Controller">
                <label htmlFor="devBox" style={{color:'white'}}> Developer Box
                    <div className="devBox">
                        <p style={{color:'white'}}>UserID: {searchparams.get('userID')}</p>
                        <p style={{color:'white'}}>UserName: {searchparams.get('userName')}</p>
                        <p style={{color:'white'}}>Screen orientation: {scrOrientation}</p>
                    </div>
                </label>
            </div>
        );
    }
}

export default Controller;