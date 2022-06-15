import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useSelector } from "react-redux";
import { useEffect, useState } from "react";
import "./Quiz.css";
import Question from "../../components/Question/Question";

const Quiz = ({id, creator, data}) => {
	const [audio] = useState(new Audio("https://assets-cdn.kahoot.it/player/v2/assets/lobby-fantasy.8bc91bd4.webm"));
	const [mute, setMute] = useState(false);

	const username = useSelector(state => state.user?.data?.username);
	const question = useSelector(state => state.question);
	const roomData = useSelector(state => state.rooms.currentRoom);

	let questionCount = 1;

	const questions = question.answers.map(answer => {
		return <Question text={answer}/>
	});

	const toggle = () => setMute(!mute);

	// const navigate = useNavigate();

	useEffect(() => {
		if(mute) audio.pause();
		else {
			audio.loop = true;
			audio.play();
		}

		// let toSend = JSON.stringify({ roomid: Number(id) });

		// ws.send(ClientToServerCode.GET_PLAYERS_IN_ROOM + toSend);

		return () => {
            audio.pause();
			ws.send(ClientToServerCode.LEAVE_ROOM);
        }
	}, [mute]);

	const handleStartGame = e => {
		e.preventDefault();
		
		//send to server
	}
	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div className="quiz">
				<div className="questionSection"><h3>{question.title}</h3></div>
				<div className="answers"><h3>{questions}</h3></div>
				<div className="answers"><h3>{questionCount}/{roomData.questionNum}</h3><h3>{roomData.gamePin}</h3></div>
			</div>
		</>
	)
}

export default Quiz;