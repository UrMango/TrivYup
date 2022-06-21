import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useDispatch, useSelector } from "react-redux";
// import Countdown from 'react-countdown';
import CountdownTimer from '../../components/CountdownTimer/CountdownTimer.js';
import { createRef, useEffect, useState } from "react";
import "./Quiz.css";
import Answer from "../../components/Answer/Answer";

import battleMusic from "../../assets/music/Battle.mp3";

const Quiz = () => {
	const [audio] = useState(new Audio(battleMusic));
	
	const resultsRef = createRef();
	
	const username = useSelector(state => state.user?.data?.username);
	const question = useSelector(state => state?.rooms?.currQuestion);
	const roomData = useSelector(state => state.rooms?.currentRoom);
	const isEveryoneAnswered = useSelector(state => state?.rooms?.isEveryoneAnswered);
	
	const [mute, setMute] = useState(false);
	const [qCount, setQCount] = useState(1);
	const [endTime, setEndTime] = useState(Date.now() + roomData.answerTimeout * 1000);
	
	const [questionTimeout, setQuestionTimeout] = useState(null);
	const [deleteTimeoutCallerId, setDeleteTimeoutCallerId] = useState(null);

	/**  answering result - status 1 - yes, 0 - no
	 * @type {object} */
	let questionRes = useSelector(state => state?.rooms?.questionRes);

	const answers = question?.answers?.map(answer => { 
		return <Answer text={answer[1]}/>
	});

	const toggle = () => setMute(!mute);

	const dispatch = useDispatch();

	// const navigate = useNavigate();
	
	useEffect(() => {
		audio.volume = 0.2;
		if(mute) audio.pause();
		else {
			audio.loop = true;
			audio.play(); 
		}

		ws.send(ClientToServerCode.GET_QUESTION);

		setQuestionTimeout(setTimeout(() => {
			console.log("Time's up!");
			let toSend = JSON.stringify({ answer: "" });
			ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
		}, roomData.answerTimeout * 1000));

		return () => {
            audio.pause();
        }
	}, [mute]);

	const deleteTimeout = (callerId) => {
		if(deleteTimeoutCallerId == callerId) {
			return;
		}
		setDeleteTimeoutCallerId(callerId);
		console.log("Deleted timeout");
		clearTimeout(questionTimeout);
		console.log(questionTimeout);
		setQuestionTimeout(null);
	}

	const handleNextQuestion = () => {
		console.log("handlenext");
		setTimeout(() => {
			console.log("handled");
			deleteTimeout(1);
			
			ws.send(ClientToServerCode.GET_QUESTION);
			dispatch({type: "EVERYONE_ANSWERED", payload: false});
			dispatch({type: "QUESTION_RES", payload: {}});
			setQCount(qCount + 1);
			setEndTime(Date.now() + roomData.answerTimeout * 1000);
			
			setQuestionTimeout(setTimeout(() => {
				console.log("Time's up!");
				let toSend = JSON.stringify({ answer: "" });
				ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
			}, roomData.answerTimeout * 1000));
		}, 5000);
	}

	// const countdownRefHandle = r => {
	// 	console.log("start");
	// 	r.start();
	// }

	const handleGameResults = () => {
		ws.send(ClientToServerCode.GET_GAME_RESULT);
	}

	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			{questionRes.status != null && <div>{deleteTimeout(0)}</div>}
			{ (qCount <= roomData.questionCount) ? (questionRes.status != null ? (isEveryoneAnswered ? ( <div>{handleNextQuestion()}</div> && (questionRes?.status == 1 ? <h2>YOU'RE RIGHT</h2> : <h2>YOU'RE A NOOB</h2>)) : <h2>Waiting for everyone to answer...</h2>) : <div className="quiz">
				<div className="questionSection"><h3>{question?.question}</h3></div>
				<div className="answers">{answers}</div>
				{/* <Countdown controlled={false} onMount={() => console.log("mounted")} onStart={() => console.log("started")} onPause={() => console.log("paused")} onTick={() => console.log("tick")} onComplete={() => console.log("finished")} ref={countdownRef} date={startTime + roomData.answerTimeout * 1000} renderer={props => <div>{Math.floor(props.total / 1000)}  </div>} /> */}
				<CountdownTimer targetDate={endTime} />
				<div className="answers"><h3>{qCount}/{roomData.questionCount}</h3><h3>{roomData.gamePin}</h3></div>
			</div>) : ( handleGameResults() ) }
		</>
	)
}

export default Quiz;