import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { setUserData } from "../../actions/userActions";
import { useSelector } from 'react-redux';

import "./Login.css"
import { useDispatch } from "react-redux";

const Login = () => {
	const [username, setUsername] = useState("");
	const [password, setPassword] = useState("");

	const dispatch = useDispatch();

	const isLogged = useSelector(state => state.user.isLogged);
	
	const navigate = useNavigate();

	const handleLogin = (e) => {
		e.preventDefault();
		dispatch(setUserData({ username }));
		ws.send(ClientToServerCode.MT_CLIENT_LOG_IN + JSON.stringify({username, password}));
	}

	useEffect(() => {
		if(isLogged) {
			navigate("/");
		}
	}, [isLogged]);

	return (
		<div className="login">
			<h2>Log in</h2>
			<form className="form">
				<label className="username">Username</label>
				<input className="usernameInput" type="text" onChange={e => setUsername(e.target.value)} id="username" name="username"/>
				<br/>
				<label className="password">Password</label>
				<input className="passwordInput" type="password" onChange={e => setPassword(e.target.value)} id="pwd" name="pwd"/>
				<br/>
				<button className="submitBtn" onClick={handleLogin} type="submit">Log in</button>
			</form>
		</div>
	)
}

export default Login;