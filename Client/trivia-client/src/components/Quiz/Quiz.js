import ws from "../../services/websocket";
import { ClientToServerCode } from "../../helpers/consts";
import { Navigate, useNavigate } from "react-router";
import { useDispatch, useSelector } from "react-redux";
import { createRef, useEffect, useState } from "react";
import "./Quiz.css";
import Answer from "../../components/Answer/Answer";
import Results from "../../components/Results/Results";

import battleMusic from "../../assets/music/Battle.mp3";
import loadingSVG from "../../assets/images/Loading.svg";
import PlayingIcon from "../../assets/images/volume.png";
import MutedIcon from "../../assets/images/mute.png";
import { htmlDecode } from "../../helpers/functions";

const randomAnswers = {
	correct: [
		"When the honor is honor, honor 🙏",
		"That was very correct of you",
		"SHEEESSSHHHHHHHHHHHHH",
		"Nice!! Very good job",
		"You're smart :)",
		"Your'e welcomed to the cooler people group",
		"WOW MAN!! You're so good!",
		"No way you did it!",
	],
	incorrect: [
		"No one said it would be easy 😉",
		"HAHAHAHAHAHHAHA YOU'RE SO NOOB",
		"Shame on you!",
		"I was already out now...",
		"Think next time.",
		"You were right by being wrong.",
		"Yes. You were just wrong",
		"Don't answer next time...",
		"Get out of here!",
		"Jokes aside, you are just bad.",
		"Even a 3 years old would have known the answer 👶",
		"You didn't even try...",
		"😐",
	]
}

const Quiz = () => {

	const [audio] = useState(new Audio(battleMusic));
	
	const resultsRef = createRef();
	
	const username = useSelector(state => state.user?.data?.username);
	const question = useSelector(state => state?.rooms?.currQuestion);
	const roomData = useSelector(state => state.rooms?.currentRoom);
	const isEveryoneAnswered = useSelector(state => state?.rooms?.isEveryoneAnswered);
	
	const [mute, setMute] = useState(false);
	const toggle = () => setMute(!mute);
	
	const [qCount, setQCount] = useState(1);
	const [endTime, setEndTime] = useState(0);
	const [timer, setTimer] = useState(roomData?.answerTimeout);
	
	
	const [questionTimeout, setQuestionTimeout] = useState(null);
	
	const [randomAnswer, setRandomAnswer] = useState("");

	/**  answering result - status 1 - yes, 0 - no
	 * @type {object} */
	let questionRes = useSelector(state => state?.rooms?.questionRes);

	let colors = ["#e21b3c", "#1368ce", "#d89e00", "#26890c"];
	let colorCount = -1;
	const answers = question?.answers?.map(answer => { 
		colorCount++;
		return <Answer key={answer[0]} color={colors[colorCount]} text={htmlDecode(answer[1])}/>
	});

	const dispatch = useDispatch();

	// const navigate = useNavigate();

	useEffect(() => {
		const interval = setInterval(() => {
			setTimer(prev => prev - 1);
		}, 1000);

		return () => {
			clearInterval(interval);

			if(username == roomData.players[0]) {
				ws.send(ClientToServerCode.CLOSE_GAME);
			} else {
				ws.send(ClientToServerCode.LEAVE_GAME);
			}
		}
	}, []);
	
	useEffect(() => {
		ws.send(ClientToServerCode.GET_QUESTION);

		setQuestionTimeout(setTimeout(() => {
			let toSend = JSON.stringify({ answer: "" });
			ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
		}, roomData.answerTimeout * 1000));
	}, []);
	
	useEffect(() => {
		audio.volume = 0.2;
		if(mute) audio.pause();
		else {
			audio.loop = true;
			audio.play(); 
		}

		return () => {
            audio.pause();
        }
	}, [mute]);

	/**
	 * Function for deleting the question answer timeout
	 */
	const deleteTimeout = () => {		
		clearTimeout(questionTimeout);
		setQuestionTimeout(null);
	}

	/**
	 * Function that is called when the next question should be loaded
	 */
	const handleNextQuestion = () => {
		// 6 seconds of viewing results
		setTimeout(() => {
			deleteTimeout();
			setQCount(qCount + 1);
			if(qCount < roomData.questionCount){
				ws.send(ClientToServerCode.GET_QUESTION);
			} else {
				audio.pause();
			}
			// reset question
			dispatch({type: "QUESTION", payload: {}});
		}, 6000);
	}

	useEffect(() => {
		if(isEveryoneAnswered) {
			handleNextQuestion();
		}
	}, [isEveryoneAnswered]);

	useEffect(() => {
		if(questionRes.status != null) {
			deleteTimeout();
			if(questionRes.status == 0)
				setRandomAnswer(getRandomSentence("incorrect"));
			else 
				setRandomAnswer(getRandomSentence("correct"));
		}
	}, [questionRes.status]);
	
	useEffect(() => {
		if(question.question != null) {
			deleteTimeout();
			setEndTime(Date.now() + roomData.answerTimeout * 1000);
			setTimer(roomData?.answerTimeout);

			// get to quiz back
			dispatch({type: "EVERYONE_ANSWERED", payload: false});
			dispatch({type: "QUESTION_RES", payload: {}});

			setQuestionTimeout(setTimeout(() => {
				let toSend = JSON.stringify({ answer: "" });
				ws.send(ClientToServerCode.SUBMIT_ANSWER + toSend);
			}, roomData.answerTimeout * 1000));
		}
	}, [question]);

	/**
	 * Function for getting a random sentence when question results are shown 
	 * @param {String} type 
	 * @returns 
	 */
	const getRandomSentence = (type) => {
		const answerArr = randomAnswers[type];
		const id = Math.floor(Math.random() * answerArr.length);
		return answerArr[id];
	}

	/**incorrect svg */
	const incorrect = () => {
		return <svg xmlns="http://www.w3.org/2000/svg" width="80" height="80" viewBox="0 0 80 80"><g fill="none" fill-rule="evenodd"><g><g><g><g transform="translate(-257 -1827) translate(90 1581) translate(47 190) translate(120 56)"><circle cx="40" cy="40" r="37.895" fill="#F35" stroke="#FFF" stroke-width="4.211"></circle><g fill="#FFF" fill-rule="nonzero" stroke="#000" stroke-opacity="0.15" stroke-width="2.105"><path d="M39.99 12.621v14.736l14.736.001V39.99H39.99v14.736H27.359V39.99H12.62V27.359h14.736l.001-14.737H39.99z" transform="translate(6.316 6.316) rotate(-135 33.674 33.674)"></path></g></g></g></g></g></g></svg>;
	}
	
	/**correct svg */
	const correct = () => {
		return <svg xmlns="http://www.w3.org/2000/svg" width="80" height="80" viewBox="0 0 80 80"><g fill="none" fill-rule="evenodd"><g><g><g><g transform="translate(-703 -1807) translate(536 1581) translate(46 170) translate(121 56)"><circle cx="40" cy="40" r="37.895" fill="#66BF39" stroke="#FFF" stroke-width="4.211"></circle><g fill="#FFF" fill-rule="nonzero" stroke="#000" stroke-opacity="0.15" stroke-width="2.105"><path d="M46.244 15.355l8.127 7.393-25.623 28.184-15.526-14.483 7.743-7.747 7.333 6.396 17.946-19.743z" transform="translate(6.316 6.316) rotate(-3 33.81 33.138)"></path></g></g></g></g></g></g></svg>;
	}


	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			{ (qCount <= roomData.questionCount) ? (questionRes.status != null ? (isEveryoneAnswered ? (questionRes?.status == 1 ? <div className="question-result"><h2 className="text">Correct!</h2>{correct()}<p className="randomText">{randomAnswer}</p></div> : <div className="question-result"><h2 className="text">YOU'RE A NOOB!</h2>{incorrect()}<p className="randomText">{randomAnswer}</p></div>) : <div className="question-result"><h2 className="text">Waiting for everyone to answer...</h2><img className="loadingSVG" src={loadingSVG}></img></div>) : <div className="quiz">
				<div className="side-options">
					<button className="muteBtn" onClick={toggle}><img src={ mute ? MutedIcon : PlayingIcon } /></button>
				</div>
				<div className="questionSection">
					<h3 className="timer">{timer}</h3>
					<h3 className="question">{htmlDecode(question?.question)}</h3>
					<div></div>
				</div>
				<div className="answers">{answers}</div>
				<div className="footer">
					<h3>{qCount} of {roomData.questionCount}</h3>
					<h3>{roomData.gamePin}</h3>
				</div>
			</div>) : roomData?.players?.length > 0 && <Results isAdmin={username == roomData.players[0]} /> }
		</>
	)
}

export default Quiz;