import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';
import Countdown from 'react-countdown';
import PlayBtn from '../../assets/images/playBtn.png';
import CreateBtn from '../../assets/images/createBtn.png';

import "./Home.css"
import Statistics from '../../components/Statistics/Statistics';
import Highscore from '../../components/Highscore/Highscore';

const Home = () => {
	const username = useSelector(state => state.user?.data?.username);


	return (
	<>
		<div className='space'></div>
		<div className="feed">
			<div className="profile-widget">
				<h2>{ username ? username : <Link to="/auth">Login / Signup to play!</Link>}</h2>
				<div className="inform">
					{ username ? <>
					<h3>Welcome back!</h3>
					<br/>
					<p>We hope you're in a quiz mood, because there will be a lot from this stuff today!
					<br/>
					Are you ready?</p>
					</> : <>
					<h3>Welcome to TrivYup!</h3>
					<br/>
					<p>The only place that gives you quizzes in the world! (Kahoot? what's that?)
					<br/>
					Get into a room or make one yourself and START PLAYING!</p>
					</>}
				</div>
			</div>
			<div className="play-widget">
				<h4 className='text'>Host a TrivYup!</h4>
				<h2 className='text'>More players - more fun! invite your class</h2>
				{/* Buttons - play, create */}
				<section className="buttons">
					<Link to="/play"><img className="playBtn" src={PlayBtn}></img></Link>
					<Link to="/create"><img className="createBtn" src={CreateBtn}></img></Link>
				</section>
			</div>
			<div className="timeto-widget">
				<h3>Time to end the project</h3>
				<h2><Countdown date={new Date("Jun 15, 2022 12:00:00")}/></h2>
			</div>
			{ username && <Statistics /> }
			{ username && <Highscore /> }
		</div>
	</>
	)
}

export default Home;