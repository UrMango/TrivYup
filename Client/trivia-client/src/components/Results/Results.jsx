import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect } from 'react';
import { useSelector } from 'react-redux';

import "./Results.css";

const Results = ({isAdmin}) => {
	const gameResults = useSelector(state => state?.rooms?.gameResults);
	
	useEffect(() => {
		ws.send(ClientToServerCode.GET_GAME_RESULT);
	}, []);

	const closeGameHandler = e => {
		e.preventDefault();
		ws.send(ClientToServerCode.CLOSE_GAME);
	};

	return (
		<div className="results">
			{isAdmin && <button onClick={closeGameHandler}>Exit</button>}
			{gameResults.length > 0 ? <div className="users">
				<div className="user"><h3 className="username">{gameResults[1]?.username}</h3><div className="podium" id="second">2</div></div>
				<div className="user"><h3 className="username">{gameResults[0]?.username}</h3><div className="podium" id="first">1</div></div>
				<div className="user"><h3 className="username">{gameResults[2]?.username}</h3><div className="podium" id="third">3</div></div>
			</div> : <h6 className="loading">And the results... 🥁🥁🥁</h6>}
		</div>
	)
}

export default Results;