import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useSelector } from "react-redux";
import Logo from "../../assets/images/Logo-1150p-white.png";
import { useEffect, useState } from "react";
import GameBox from "../../components/GameBox/GameBox";
import { Link } from "react-router-dom";
import "./Play.css";

const Play = () => {
	const username = useSelector(state => state.user?.data?.username);

	const [gamepin, setGamePin] = useState(0);

	const { rooms } = useSelector(state => state.rooms);

	const navigate = useNavigate();

	// since `todos` is an array, we can loop over it
	const roomList = rooms.filter(room => {
		if(room.isActive == 1) {
		  return false; // skip
		}
		return true;
	}).map(room => {
		return <GameBox key={room.id} username={username} gamename={room.name} maxPlayers={room.maxPlayers} gameCode={room.id} />
	});

	console.log(roomList);

	useEffect(() => {
		ws.send(ClientToServerCode.GET_ROOMS);
	}, []);

	const handleJoinGame = e => {
		e.preventDefault();
		// console.log(e);
		if(e.target.id.length > 0) {
			console.log("Game code is: " + e.target.id);

			navigate("/play/" + e.target.id);
			return;
		}
		
		console.log("Game code is: " + gamepin);
		navigate("/play/" + gamepin);
		
		// ws.send(ClientToServerCode.JOIN_ROOM + JSON.stringify({roomid: Number(gamepin)}));

		//send to server
	}

	
	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div className="playPage">
				<img className="logo" src={Logo}></img>
				<form className="form">
					<input className="gamePin" placeholder="Game PIN" type="text" onChange={e => setGamePin(Number(e.target.value))} />
					<br/>
					<button className="enterBtn" onClick={handleJoinGame} type="submit">Enter</button>
				</form>
				{/* <h3 className="or">OR</h3> */}
			</div>
			<div className="openGames">
				<h4 className="textupper">Games you can join:</h4>
				<div className="games">{roomList.length > 0 ? roomList : <h4 className="nogames" >No games open :(<br/><Link to="/create">Try to make your own!</Link></h4>}
					{/* <GameBox username="Mango" gamename="Cool game" playersLen={1} maxPlayers={20} gameCode={12023}/>
					<GameBox username="Shirel" gamename="Hello" playersLen={2} maxPlayers={10} gameCode={40239}/> */}
				</div>
			</div>
		</>
	)
}

export default Play;