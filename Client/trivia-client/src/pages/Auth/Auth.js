import Register from "../../components/Register/Register";
import Login from "../../components/Login/Login";

const Auth = ({ type }) => {
	return (
		<div>
			{ type == "login" && <Login /> }
			{ type == "register" && <Register /> }
		</div>
	)
}

export default Auth;