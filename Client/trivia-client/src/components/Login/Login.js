import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { setUserData } from "../../actions/userActions";
import { useSelector, useDispatch } from 'react-redux';

import "./Login.css";

const Login = () => {
	const [username, setUsername] = useState("");
	const [password, setPassword] = useState("");

	const dispatch = useDispatch();

	const isLogged = useSelector(state => state.user.isLogged);
	
	const navigate = useNavigate();

	const handleLogin = (e) => {
		e.preventDefault();
		if(e.target.id == "yes") {
			dispatch(setUserData({ username }));
			ws.send(ClientToServerCode.MT_CLIENT_LOG_IN + JSON.stringify({username, password}));
		}
	}

	useEffect(() => {
		if(isLogged) {
			navigate("/");
		}
	}, [isLogged]);

	return (
	<>
	<div className='space'></div>
		<div className="login">
			<h2>Log in</h2>
			<form className="form">
				<label className="username">Username</label>
				<input className="usernameInput" type="text" onChange={e => {
					if(e.target.value.length > 0) {
						e.target.id = "yes";
						if(document.getElementsByClassName("passwordInput")[0]?.id == "yes") {
							document.getElementsByClassName("submitBtn")[0].attributes.getNamedItem("style").textContent = "background-color: rgb(38, 137, 12); cursor: pointer;";
							document.getElementsByClassName("submitBtn")[0].id = "yes";
						}
					} else {
						e.target.id = "no";
						document.getElementsByClassName("submitBtn")[0].attributes.getNamedItem("style").textContent = "display: 'block'";
						document.getElementsByClassName("submitBtn")[0].id = "no";
					}
					setUsername(e.target.value);
				}}/>
				<br/>
				<label className="password">Password</label>
				<input className="passwordInput" type="password" onChange={e => {
					if(e.target.value.length > 0) {
						e.target.id = "yes";
						if(document.getElementsByClassName("usernameInput")[0]?.id == "yes") {
							document.getElementsByClassName("submitBtn")[0].attributes.getNamedItem("style").textContent = "background-color: rgb(38, 137, 12); cursor: pointer;";
							document.getElementsByClassName("submitBtn")[0].id = "yes";
						}
					} else {
						e.target.id = "no";
						document.getElementsByClassName("submitBtn")[0].attributes.getNamedItem("style").textContent = "display: 'block'";
						document.getElementsByClassName("submitBtn")[0].id = "no";
					}
					setPassword(e.target.value)
				}} id="pwd" name="pwd"/>
				<br/>
				<button className="submitBtn" onClick={handleLogin} type="submit" style={{display: "block"}}>Log in</button>
			</form>
		</div>
	</>
	)
}

export default Login;