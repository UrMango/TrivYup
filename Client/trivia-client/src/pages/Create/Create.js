import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useEffect, useState } from "react";
import { Navigate } from "react-router";
import { useDispatch, useSelector } from "react-redux";
import Alert from "../../components/Alert/Alert";

import "./Create.css";

const Create = () => {
	const username = useSelector(state => state.user?.data?.username);
	const [roomName, setRoomName] = useState("");
	const [maxUsers, setMaxUsers] = useState("");
	const [questionCount, setQuestionCount] = useState("");
	const [answerTimeout, setAnswerTimeout] = useState("");

	const dispatch = useDispatch();

	/**
	 * Function for handling create game button click
	 * @param {Event} e 
	 * @returns 
	 */
	const handleCreateGame = (e) => {
		e.preventDefault();

		if(maxUsers.length == 0 || questionCount.length == 0 || answerTimeout.length == 0) {
			dispatch({type: "ALERT", payload: <Alert text={"Fill all the inputs."} type="Error"/>});
			return;
		}

		setMaxUsers(Number(maxUsers));
		setQuestionCount(Number(questionCount));
		setAnswerTimeout(Number(answerTimeout));
		
		if(maxUsers <= 0 || maxUsers != Math.trunc(maxUsers)) {
			dispatch({type: "ALERT", payload: <Alert text={"Max users should be a number bigger than 0"} type="Error"/>});
			return;
		}
		if(questionCount <= 0 || questionCount != Math.trunc(questionCount)) {
			dispatch({type: "ALERT", payload: <Alert text={"Question count should be a number bigger than 0"} type="Error"/>});
			return;
		}
		if(answerTimeout <= 0 || answerTimeout != Math.trunc(answerTimeout)) {
			dispatch({type: "ALERT", payload: <Alert text={"Answer timeout should be a number bigger than 0"} type="Error"/>});
			return;
		}

		const toSend = {roomName, maxUsers, questionCount, answerTimeout};
		let toSendString = JSON.stringify(toSend);
		ws.send(ClientToServerCode.CREATE_ROOM + toSendString);
	}

	return (
	<>
	{!username && <Navigate to="/auth/login"/>}
	<div className='space'></div>
		<div className="createRoom">
			<h2>Create Room</h2>
			<form className="form">
				<label className="gameName">Game Name</label>
				<input className="gameNameInput" type="text" onChange={e => setRoomName(e.target.value)}/>
				<br/>
				<label className="maxPlayers">Max Players</label>
				<input className="maxPlayersInput" type="text" onChange={e => setMaxUsers(Number(e.target.value))}/>
				<br/>
				<label className="questionCount">Question Count</label>
				<input className="questionCountInput" type="text" onChange={e => setQuestionCount(Number(e.target.value))}/>
				<br/>
				<label className="answerTimeout">Answer Timeout</label>
				<input className="answerTimeoutInput" type="text" onChange={e => setAnswerTimeout(Number(e.target.value))}/>
				<br/>
				<button className="submitBtn" onClick={handleCreateGame} type="submit">Create</button>
			</form>
		</div>
	</>
	)
}

export default Create;