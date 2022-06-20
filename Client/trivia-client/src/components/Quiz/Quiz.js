import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useDispatch, useSelector } from "react-redux";
import Countdown from 'react-countdown';
import { createRef, useEffect, useState } from "react";
import "./Quiz.css";
import Answer from "../../components/Answer/Answer";

const Quiz = () => {
	const [audio] = useState(new Audio("https://assets-cdn.kahoot.it/player/v2/assets/lobby-fantasy.8bc91bd4.webm"));
	const [mute, setMute] = useState(false);
	const [qCount, setQCount] = useState(1);
	const [startTime, setStartTime] = useState(Date.now());
	const [questionTimeout, setQuestionTimeout] = useState(null);
	
	const [countdownRef, setCountdownRef] = useState(createRef());

	const username = useSelector(state => state.user?.data?.username);
	const question = useSelector(state => state?.rooms?.currQuestion);
	const roomData = useSelector(state => state.rooms?.currentRoom);
	const isEveryoneAnswered = useSelector(state => state?.rooms?.isEveryoneAnswered);

	/**  answering result - status 1 - yes, 0 - no
	 * @type {object} */
	const questionRes = useSelector(state => state?.rooms?.questionRes);

	const answers = question?.answers?.map(answer => { 
		return <Answer text={answer[1]}/>
	});

	const toggle = () => setMute(!mute);

	const dispatch = useDispatch();

	// const navigate = useNavigate();

	useEffect(() => {
		audio.volume = 0.3;
		if(mute) audio.pause();
		else {
			audio.loop = true;
			audio.play(); 
		}

		ws.send(ClientToServerCode.GET_QUESTION);

		setQuestionTimeout(setTimeout(() => {
			console.log("Time's up!");
			if(questionRes.status == null) {
				let toSend = JSON.stringify({ answer: "" });
				ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
			}
		}, roomData.answerTimeout * 1000));

		return () => {
            audio.pause();
        }
	}, [mute]);

	const deleteTimeout = () => {
		clearTimeout(questionTimeout);
		console.log(questionTimeout);
		setQuestionTimeout(null);
	}

	const handleNextQuestion = () => {
		console.log("handlenext");
		setTimeout(() => {
			console.log("handled");

			deleteTimeout();
			
			ws.send(ClientToServerCode.GET_QUESTION);
			dispatch({type: "EVERYONE_ANSWERED", payload: false});
			dispatch({type: "QUESTION_RES", payload: {}});
			setQCount(qCount + 1);
			setStartTime(Date.now());
			countdownRef?.current?.start();

			setQuestionTimeout(setTimeout(() => {
				console.log("Time's up!");
				if(questionRes.status == null) {
					let toSend = JSON.stringify({ answer: "" });
					ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
				}
			}, roomData.answerTimeout * 1000));
		}, 5000);
	}

	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			{questionRes.status != null ? <div>{deleteTimeout()}</div> && (isEveryoneAnswered ? ( <div>{handleNextQuestion()}</div> && (questionRes?.status == 1 ? <h2>YOU'RE RIGHT</h2> : <h2>YOU'RE A NOOB</h2>)) : <h2>Waiting for everyone to answer...</h2>) : <div className="quiz">
				<div className="questionSection"><h3>{question?.question}</h3></div>
				<div className="answers">{answers}</div>
				<Countdown ref={countdownRef} date={startTime + roomData.answerTimeout * 1000} renderer={props => <div>{Math.floor(props.total / 1000)}</div>} />
				<div className="answers"><h3>{qCount}/{roomData.questionCount}</h3><h3>{roomData.gamePin}</h3></div>
			</div>
			}
		</>
	)
}

export default Quiz;