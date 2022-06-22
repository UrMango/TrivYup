import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect } from 'react';
import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';
import GraphIcon from '../../assets/images/graph.png';

import "./Statistics.css";

const Statistics = () => {

	const statistics = useSelector(state => state?.user?.statistics);
	
	useEffect(() => {
		ws.send(ClientToServerCode.GET_PERSONAL_STATS);
	}, []);

	return (
		<div className="statistics">
			<h4 className="title"><img className="icon" src={GraphIcon}/>Personal Statistics</h4>
			{statistics ? <>
			<h6 className="statistic">Average answer time: {Number(statistics[0]).toFixed(2)} secs</h6>
			<h6 className="statistic">Correct answers: {Number(statistics[1])}</h6>
			<h6 className="statistic">Total answers: {Number(statistics[2])}</h6>
			<h6 className="statistic">Games played: {Number(statistics[3])}</h6>
			</> : <h6 className="loading">Loading statistics...</h6>}
		</div>
	)
}

export default Statistics;