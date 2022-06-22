import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useState } from "react";

import "./Register.css";
import { useDispatch } from "react-redux";
import Alert from "../Alert/Alert";

const Register = () => {
	const [username, setUsername] = useState("");
	const [password, setPassword] = useState("");
	const [email, setEmail] = useState("");

	const dispatch = useDispatch();

	const handleRegister = (e) => {
		e.preventDefault();
		if(username.length == 0 || password.length == 0 || email.length == 0) {
			dispatch({type: "ALERT", payload: <Alert text={"Fill all the inputs."} type="Error"/>});
			return;
		}

		ws.send(ClientToServerCode.MT_CLIENT_SIGN_UP + JSON.stringify({username, password, email}));
	}

	return (
	<>
	<div className='space'></div>
		<div className="register">
			<h2>Register</h2>
			<form className="form">
				<label className="username">Username</label>
				<input className="usernameInput" type="text" onChange={e => setUsername(e.target.value)} id="username" name="username"/>
				<br/>
				<label className="email">Email</label>
				<input className="emailInput" type="text" onChange={e => setEmail(e.target.value)} id="email" name="email"/>
				<br/>
				<label className="password">Password</label>
				<input className="passwordInput" type="password" onChange={e => setPassword(e.target.value)} id="pwd" name="pwd"/>
				<br/>
				<button className="submitBtn" onClick={handleRegister} type="submit">Sign up</button>
			</form>
		</div>
	</>
	)
}

export default Register;