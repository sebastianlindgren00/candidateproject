import './Controller.css';

function checkOrientation(){
    window.screen.addEventListener("orientationchange", () => {
        console.log(`The orientation of the screen is: ${window.screen.orientation}`);
      });
    if(window.screen.orientation){

    }
}

function Controller() {
    if(!checkOrientation()){
        return(
            <p>please change phone orientation</p>
        );
    }else{
        window.screen.orientation.lock();
        return(
            <p>test</p>
        );
    }
}

export default Controller;