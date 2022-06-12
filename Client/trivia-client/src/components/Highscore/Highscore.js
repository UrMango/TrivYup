import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect } from 'react';
import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';
import PodiumIcon from '../../assets/images/podium.png';

import "./Highscore.css";

const Highscore = () => {

	const highscores = useSelector(state => state?.user?.highscores);
	
	useEffect(() => {
		ws.send(ClientToServerCode.HIGH_SCORE);
	}, []);

	return (
		<div className="highscore">
			<h4 className="title"><img className="icon" src={PodiumIcon}/>Highscores</h4>
			{highscores.length > 0 ? <div className="users">
				<div className="user"><h3 className="username">{highscores[1]}</h3><div className="podium" id="second">2</div></div>
				<div className="user"><h3 className="username">{highscores[0]}</h3><div className="podium" id="first">1</div></div>
				<div className="user"><h3 className="username">{highscores[2]}</h3><div className="podium" id="third">3</div></div>
			</div> : <h6 className="loading">Loading highscores...</h6>}
		</div>
	)
}

export default Highscore;