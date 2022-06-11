import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { useState } from "react";
import { Navigate } from "react-router";
import { useSelector } from "react-redux";

import "./Create.css";

const Create = () => {
	const username = useSelector(state => state.user?.data?.username);
	const [roomName, setRoomName] = useState("");
	const [maxUsers, setMaxUsers] = useState(0);
	const [questionCount, setQuestionCount] = useState(0);
	const [answerTimeout, setAnswerTimeout] = useState(0);

	const handleCreateGame = (e) => {
		e.preventDefault();
		setMaxUsers(Number(maxUsers));
		setQuestionCount(Number(questionCount));
		setAnswerTimeout(Number(answerTimeout));

		const toSend = {roomName, maxUsers, questionCount, answerTimeout};
		let toSendString = JSON.stringify(toSend);
		console.log(toSendString);
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