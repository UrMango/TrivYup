import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useState } from "react";

const Register = () => {
	const [username, setUsername] = useState("");
	const [password, setPassword] = useState("");
	const [email, setEmail] = useState("");

	const handleRegister = (e) => {
		e.preventDefault();
		ws.send(ClientToServerCode.MT_CLIENT_SIGN_UP + JSON.stringify({username, password, email}));
	}

	return (
		<div>
			<p>Register</p>
			<form>
				<label>Username: </label>
				<input type="text" onChange={e => setUsername(e.target.value)} id="username" name="username"/>
				<br/>
				<label>Password: </label>
				<input type="password" onChange={e => setPassword(e.target.value)} id="pwd" name="pwd"/>
				<br/>
				<label>Email: </label>
				<input type="text"  onChange={e => setEmail(e.target.value)} id="email" name="email"/>
				<br/>
				<button onClick={handleRegister} type="submit">Register</button>
			</form>
		</div>
	)
}

export default Register;