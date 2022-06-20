import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useLocation, useParams } from "react-router";
import { useSelector } from "react-redux";
import Logo from "../../assets/images/Logo-1150p-white.png";
import { useEffect, useState } from "react";
import GameBox from "../../components/GameBox/GameBox";


import "./Game.css";
import Lobby from "../../components/Lobby/Lobby";
import Quiz from "../../components/Quiz/Quiz";

const Game = (props) => {
	const username = useSelector(state => state.user?.data?.username);
	const gameBegun = useSelector(state => state?.rooms?.gameBegun);
	
	const { gameId } = useParams();
	const state = useLocation().state;
	
	useEffect(() => {
		console.log("sdsad");
	}, []);
	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			{gameBegun ? <Quiz /> : <Lobby id={gameId} creator={state?.creator} data={state?.data}/>}
		</>
	)
}

export default Game;