import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useState } from "react";
import { useNavigate } from "react-router";

import "./Answer.css";

const Answer = ({text}) => {
	const navigate = useNavigate();

	const handleAnswer = e => {
		e.preventDefault();
		let toSend = JSON.stringify({ answer: text });
		ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
	}

	return (
		<div className="answer">
			<button onClick={handleAnswer} className="answer-text">{text}</button>
		</div>			
	)
}

export default Answer;