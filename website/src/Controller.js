import './Controller.css';
import './App'
import { useSearchParams } from 'react-router-dom';

function Controller() {
    //TODO: Add function to check screen orientation, alt. force screen into landscape
    //TODO: Add controll buttons
    const [searchparams] = useSearchParams()

    return(
        <div className="Controller">
            <p style={{color:'white'}}>UserID: {searchparams.get('userID')}</p>
            <p style={{color:'white'}}>UserName: {searchparams.get('userName')}</p>
        </div>
    );
}

export default Controller;