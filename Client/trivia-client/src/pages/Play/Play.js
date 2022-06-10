import { Navigate } from "react-router";
import { useSelector } from "react-redux";
import Logo from "../../assets/images/Logo-1150p-white.png";
import { useState } from "react";

import "./Play.css";

const Play = () => {
	const username = useSelector(state => state.user?.data?.username);

	const [gamepin, setGamePin] = useState("");
	
	const handleJoinGame = e => {
		e.preventDefault();
		// console.log(e);
		if(e.target.id.length > 0) {
			console.log("Game code is: " + e.target.id);

			//send to server
			return;
		}
		
		console.log("Game code is: " + gamepin);

		//send to server
	}

	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div className="playPage">
				<img className="logo" src={Logo}></img>
				<form className="form">
					<input className="gamePin" placeholder="Game PIN" type="text" onChange={e => setGamePin(e.target.value)} />
					<br/>
					<button className="enterBtn" onClick={handleJoinGame} type="submit">Enter</button>
				</form>
				<h3 className="or">OR</h3>
				<div className="openGames">
					<h4 className="textupper">Games you can join:</h4>
					<div className="games">
						<div className="game">
							<h2 className="gamename">Game Name</h2>
							<h4 className="gameauthor">Username</h4>
							<h3 className="gamecode">12345</h3>
							<button className="joinBtn" id="12345" onClick={handleJoinGame}>Join</button>
						</div>
					</div>
				</div>
			</div>
		</>
	)
}

export default Play;