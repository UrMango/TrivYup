import { useState } from "react";

import "./GameBox.css";

const GameBox = ({username, gamename, playersLen, maxPlayers, gameCode}) => {
	
	const handleJoinGame = e => {
		e.preventDefault();
		// console.log(e);
		if(e.target.id.length > 0) {
			console.log("Game code is: " + e.target.id);

			//send to server
			return;
		}
	}

	return (
		<div className="gamebox">
			<h4 className="gameauthor">{username}</h4>
			<h2 className="gamename">{gamename}</h2>
			<h5 className="gameplayers">{playersLen}/{maxPlayers}</h5>
			<h3 className="gamecode">{gameCode}</h3>
			<button className="joinBtn" id={gameCode} onClick={handleJoinGame}>Join</button>
		</div>			
	)
}

export default GameBox;