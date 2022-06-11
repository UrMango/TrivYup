import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useParams } from "react-router";
import { useSelector } from "react-redux";
import Logo from "../../assets/images/Logo-1150p-white.png";
import { useEffect, useState } from "react";
import GameBox from "../../components/GameBox/GameBox";


import "./Game.css";

const Game = () => {
	const username = useSelector(state => state.user?.data?.username);

	const { gameId } = useParams();

	useEffect(() => {
		ws.send(ClientToServerCode.JOIN_ROOM + JSON.stringify({}));
	}, []);

	
	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			{}
			<div className="gamePage">
				<img className="logo" src={Logo}></img>
				
				{/* <h3 className="or">OR</h3> */}
			</div>
		</>
	)
}

export default Game;