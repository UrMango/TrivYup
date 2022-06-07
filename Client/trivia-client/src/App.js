import socket from "./services/websocket";
import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";

import Home from "./pages/Home/Home";
import Play from "./pages/Play/Play";
import Create from "./pages/Create/Create";
import Auth from "./pages/Auth/Auth";
import Navbar from "./components/Navbar/Navbar";
import { useEffect, useState } from "react";

import { ResponseCode, LoginCode, RegisterCode } from "./helpers/consts";

import "./App.css"
import { useDispatch } from "react-redux";
import { login, logout } from "./actions/userActions";

const App = () => {
  const dispatch = useDispatch();

  useEffect(() => {
    socket.onopen = (e) => {
      console.log("Connected to server successfuly!");
    };
  
    socket.onmessage = (e) => {
      
      const msg = JSON.parse(e.data);

      switch (msg.id) {
        case ResponseCode.login:
          if(msg.status == LoginCode.loginSuccess) {
            dispatch(login());
          } else if(msg.status == LoginCode.loginError) {
            console.log("Login failed.");
          }
          break;
        case ResponseCode.signup:
          if(msg.status == RegisterCode.signupSuccess) {
            console.log("Register succeeded!")
          } else if(msg.status == RegisterCode.signupError) {
            console.log("Register failed.");
          }
          break;
        
        default:
          break;
      }
    };

    // return () => {
    //   socket.close()
    // }
  }, []);

  return (
    <div className="App">
      <Router>
        <Navbar/>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/play" element={<Play />} />
          <Route path="/create" element={<Create />} />
          <Route path="/auth" element={<Navigate to="/auth/login"/>} />
          <Route path="/auth/login" element={<Auth type="login"/>} />
          <Route path="/auth/register" element={<Auth type="register"/>} />
        </Routes>
      </Router>
    </div>
  );
}

export default App;
