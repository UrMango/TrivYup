import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useSelector } from "react-redux";
import Logo from "../../assets/images/Logo-1150p-white.png";
import UserIcon from "../../assets/images/user.png";
import LeaveIcon from "../../assets/images/exit.png";
import PlayingIcon from "../../assets/images/volume.png";
import MutedIcon from "../../assets/images/mute.png";
import { useEffect, useState } from "react";
import "./Lobby.css";

import lobbyMusic from "../../assets/music/Lobby.mp3";
import { useRef } from "react";

const Lobby = ({id, creator, data}) => {
	const [audio] = useState(new Audio(lobbyMusic));
	const [mute, setMute] = useState(false);
	const toggle = () => setMute(!mute);

	const username = useSelector(state => state.user?.data?.username);

	/**@type {Array} */
	const players = useSelector(state => state.rooms?.currentRoom?.players);

	const navigate = useNavigate();
	
	const loadingRef = useRef();

	/**@type {Array} */
	const playersList = players?.map(player => {
		return <div key={player} className="playername"><h3>{player}</h3></div>
	});

	if(players?.length > 0 && players[0] == username) creator = true;
	playersList?.splice(0, 1);

	useEffect(() => {
		if(!creator) {	
			id = Number(id);
			let toSend = JSON.stringify({ roomid: Number(id) });
			ws.send(ClientToServerCode.JOIN_ROOM + toSend);
		}
		id = Number(id);
		let toSend = JSON.stringify({ roomid: Number(id) });

		ws.send(ClientToServerCode.GET_ROOM_STATE + toSend);
		const getPlayers = setInterval(() => {
			ws.send(ClientToServerCode.GET_ROOM_STATE + toSend);
		}, 2500);

		return () => {
			clearInterval(getPlayers);

			ws.send(ClientToServerCode.CLOSE_ROOM);
			ws.send(ClientToServerCode.LEAVE_ROOM);
        }
	}, []);
	
	useEffect(() => {
		audio.volume = 0.2;
		if(mute) audio.pause();
		else {
			audio.loop = true;
			audio.play();
		}

		return () => {
            audio.pause();
        }
	}, [mute]);

	const handleStartGame = e => {
		e.preventDefault();

		// start - disable
		// loadingGame - enable
		console.log(loadingRef.current);
		loadingRef.current.style.display = "flex";
		loadingRef.current.style.position = "fixed";
		loadingRef.current.style.justifyContent = "center";
		loadingRef.current.style.alignItems = "center";
		loadingRef.current.style.width = "100%";
		loadingRef.current.style.height = "100vh";
		loadingRef.current.style.color = "white";
		loadingRef.current.style.backgroundColor = "rgb(0 0 0 / 24%)";
		loadingRef.current.style.fontWeight = "bold";
		loadingRef.current.style.fontSize = "20px";

		ws.send(ClientToServerCode.START_GAME);
		//send to server
	}
	
	const handleExitRoom = e => {
		e.preventDefault();
		
		//send to server
		if(username == players[0]) {
			ws.send(ClientToServerCode.CLOSE_ROOM);
		} else {
			ws.send(ClientToServerCode.LEAVE_ROOM);
		}
	}

	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div ref={loadingRef} style={{display: "none"}} className="loadingGame"><center>Starting Game...</center></div>
			<div className="joinCode">
				<div className="side-options">
					<button className="muteBtn" onClick={toggle}><img src={ mute ? MutedIcon : PlayingIcon } /></button>
					<button className="leaveRoomBtn" onClick={handleExitRoom}><img src={LeaveIcon} /></button>
				</div>
				<div className="joinCodePlace">
					<h3 className="text">Game PIN:</h3>
					<h1 className="pin">{id}</h1>
				</div>
			</div>
			<div className="lobby">
				<div className="upper">
					<div className="playerCount">
						<img className="userIcon" src={UserIcon} alt="" />
						<h3>{playersList?.length || 0}</h3>
					</div>
					<img className="logo" src={Logo}></img>
					{players && ( creator ? <button className="startBtn" onClick={handleStartGame} type="submit">Start</button> : <div style={{textAlign: "center", fontWeight: 500, marginTop: 20}}>Creator: {players[0]}</div> )}
				</div>
				<div className="players">{playersList?.length > 0 ? playersList : <h4 className="noplayers">Waiting for players...</h4>}</div>
			</div>
		</>
	)
}

export default Lobby;