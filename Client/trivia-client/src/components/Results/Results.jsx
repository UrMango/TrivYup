import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect } from 'react';
import { useSelector } from 'react-redux';
import ReactConfetti from 'react-confetti';

import First from '../../assets/images/first.svg';
import Second from '../../assets/images/second.svg';
import Third from '../../assets/images/third.svg';

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

	const calcScore = (gameResult) => {
		const score = Math.floor(1000 * (gameResult?.correctAnswerCount / gameResult?.averageAnswerTime));
		if(score == score) return score;
		return "";
	}

	return (
		<div className="results">
			<ReactConfetti style={{zIndex: 5}}/>
			{isAdmin && <button className="exitBtn" onClick={closeGameHandler}>Exit</button>}
			{gameResults.length > 0 ? (<div className="users">
				<div className="user">
					<h3 className="username">{gameResults[1]?.username}</h3>
					<div className="podium" id="second">
						<section className="podiumContent">
							<img className="img" src={Second}/>
							<h3 className="score">{calcScore(gameResults[1])}</h3>
						</section>
					</div>
				</div>
				<div className="user">
					<h3 className="username" id="first">{gameResults[0]?.username}</h3>
					<div className="podium" id="first">
						<section className="podiumContent">
							<img className="img" src={First}/>
							<h3 className="score">{calcScore(gameResults[0])}</h3>
						</section>
					</div>
				</div>
				<div className="user">
					<h3 className="username">{gameResults[2]?.username}</h3>
					<div className="podium" id="third">
						<section className="podiumContent">
							<img className="img" src={Third}/>
							<h3 className="score">{calcScore(gameResults[2])}</h3>
						</section>
					</div>
				</div>
			</div>) : (<h6 className="loading">And the results... 🥁🥁🥁</h6>)}
		</div>
	);
}

export default Results;