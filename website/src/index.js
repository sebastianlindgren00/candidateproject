import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';
import Controller from './Controller';
import reportWebVitals from './reportWebVitals';

// importing components from react-router-dom package
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Navigate,
} from "react-router-dom";


const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <Router>
    <Routes>
      <Route
        exact
        path="/"
        element={<App />}
      />
      <Route
        exact
        path="/controller"
        element={<Controller />}
      />
      <Route
        path="*"
        element={<Navigate to="/" />}
      />
    </Routes>
  </Router>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
