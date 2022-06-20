import socket from "./services/websocket";
import { Routes, Route, Navigate } from "react-router-dom";
import { useLocation, useNavigate } from "react-router";

import Home from "./pages/Home/Home";
import Play from "./pages/Play/Play";
import Game from "./pages/Game/Game";
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
  const navigate = useNavigate();
  const location = useLocation();
  
  useEffect(() => {
    socket.onopen = (e) => {
      window.addEventListener("beforeunload", function (e) {
        var confirmationMessage = 'It looks like you have been editing something. '
                    + 'If you leave before saving, your changes will be lost.';
      
        (e || window.event).returnValue = confirmationMessage; //Gecko + IE
        return confirmationMessage; //Gecko + Webkit, Safari, Chrome etc.
      });
      
      console.log("Connected to server successfuly!");
    };
  
    socket.onmessage = (e) => {
      
      const msg = JSON.parse(e.data);
      console.log(msg);
      switch (msg.id) {
        case ResponseCode.login:
          if(msg.status == LoginCode.loginSuccess) {
            dispatch(login());
          } else if(msg.status == LoginCode.loginError) {
            dispatch(logout());
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
        case ResponseCode.getRooms:
          dispatch({type: "ROOM_LIST", payload: msg});
          break;
        case ResponseCode.createRoom:
          if(msg.status == 1) {
            dispatch({type: "CURR_ROOM", payload: msg.roomData});
            navigate("/play/" + msg.roomData.id, { state: { creator: true, data: msg.roomData }});
          }
          else {
            navigate("/create");
          }
          break;
        case ResponseCode.JoinRoom:
          if(msg.status == 0) {
            dispatch({type: "CURR_ROOM", payload: msg.roomData});
          }
          else {
            navigate("/play");
          }
          break;
        case ResponseCode.PersonalStats:
          dispatch({type: "STATS", payload: msg.statistics});
          break;
        case ResponseCode.GetStatistics:
          dispatch({type: "HIGHSCORES", payload: msg.statistics});
          break;
        case ResponseCode.GetRoomState:
          dispatch({type: "CURR_ROOM", payload: msg});
          break;
        case ResponseCode.GetQuestions:
          dispatch({type: "QUESTION", payload: msg});
          break;
        // case "startgame":
        //   navigate(location.pathname + "?started");
        //   break;
        default:
          break;
      }
    };
  }, []);

  return (
    <div className="App">
        <Navbar/>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/play" element={<Play />} />
          <Route path="/play/:gameId" element={<Game />} />
          <Route path="/create" element={<Create />} />
          <Route path="/auth" element={<Navigate to="/auth/login"/>} />
          <Route path="/auth/login" element={<Auth type="login"/>} />
          <Route path="/auth/register" element={<Auth type="register"/>} />
        </Routes>
    </div>
  );
}

export default App;
