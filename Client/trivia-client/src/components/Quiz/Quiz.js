import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useSelector } from "react-redux";
import { useEffect, useState } from "react";
import "./Quiz.css";
import Answer from "../../components/Answer/Answer";

const Quiz = () => {
	const [audio] = useState(new Audio("https://assets-cdn.kahoot.it/player/v2/assets/lobby-fantasy.8bc91bd4.webm"));
	const [mute, setMute] = useState(false);

	const username = useSelector(state => state.user?.data?.username);
	const question = useSelector(state => state.currQuestion);
	const roomData = useSelector(state => state.rooms.currentRoom);

	let questionCount = 1;

	const answers = question?.answers?.map(answer => { 
		return <Answer text={answer}/>
	});

	const toggle = () => setMute(!mute);

	// const navigate = useNavigate();

	useEffect(() => {
		audio.volume = 0.3;
		if(mute) audio.pause();
		else {
			audio.loop = true;
			audio.play(); 
		}

		ws.send(ClientToServerCode.GET_QUESTION);

		return () => {
            audio.pause();
        }
	}, [mute]);

	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div className="quiz">
				<div className="questionSection"><h3>{question?.title}</h3></div>
				<div className="answers"><h3>{answers}</h3></div>
				<div className="answers"><h3>{questionCount}/{roomData.questionNum}</h3><h3>{roomData.gamePin}</h3></div>
			</div>
		</>
	)
}

export default Quiz;