import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useSelector } from "react-redux";
import Logo from "../../assets/images/Logo-1150p-white.png";
import UserIcon from "../../assets/images/user.png";
import { useEffect, useState } from "react";
import PlayerBox from "../PlayerBox/PlayerBox";
import "./Lobby.css";

const Lobby = ({id, creator, data}) => {
	const username = useSelector(state => state.user?.data?.username);

	const players = useSelector(state => state.currentRoom?.players);

	const navigate = useNavigate();

	/**@type {Array} */
	const playersList = players?.map(player => {
		return <PlayerBox key={player.id} username={player.username} />
	});

	if(players > 0 && players[0]?.username == username) creator = true;
	if(creator) playersList?.splice(0, 1);

	useEffect(() => {
		if(!creator) {	
			id = Number(id);
			let toSend = JSON.stringify({ roomid: Number(id) });
			ws.send(ClientToServerCode.JOIN_ROOM + toSend);
		}
		
		// id = Number(id);
		// let toSend = JSON.stringify({ roomid: Number(id) });
		// ws.send(ClientToServerCode.GET_PLAYERS_IN_ROOM + JSON.stringify());
	}, []);

	const handleStartGame = e => {
		e.preventDefault();
		
		//send to server
	}
	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div className="joinCode">
				<div className="joinCodePlace">
					<h3 className="text">Game PIN:</h3>
					<h1 className="pin">{id}</h1>
				</div>
			</div>
			<div className="lobby">
				<div className="upper">
					<div className="playerCount">
						<img className="userIcon" src={UserIcon} alt="" />
						<h3>{playersList?.length}0</h3>
					</div>
					<img className="logo" src={Logo}></img>
					<button className="startBtn" onClick={handleStartGame} type="submit">Start</button>
				</div>
				<div className="players">{playersList?.length > 0 ? playersList : <h4 className="noplayers">Waiting for players...</h4>}</div>
			</div>
		</>
	)
}

export default Lobby;