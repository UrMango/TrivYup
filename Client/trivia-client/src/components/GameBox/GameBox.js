import { useState } from "react";
import { useNavigate } from "react-router";

import "./GameBox.css";

const GameBox = ({username, gamename, playersLen, maxPlayers, gameCode}) => {
	const navigate = useNavigate();

	/**
	 * Function for handling join game button click
	 * @param {Event} e 
	 * @returns 
	 */
	const handleJoinGame = e => {
		e.preventDefault();
		if(e.target.id.length > 0) {
			navigate("/play/" + e.target.id);
			return;
		}
	}

	return (
		<div className="gamebox">
			<h4 className="gameauthor">Max players: {maxPlayers}</h4>
			<h2 className="gamename">{gamename}</h2>
			<h3 className="gamecode">{gameCode}</h3>
			<button className="joinBtn" id={gameCode} onClick={handleJoinGame}>Join</button>
		</div>			
	)
}

export default GameBox;