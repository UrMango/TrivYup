const ResponseCode = {
	error: 0,
	login: 1,
	signup: 2,
	logout: 3,
	JoinRoom: 4,
	createRoom: 5,
	getRooms: 6,
	PlayersInRoom: 7,
	HighScore: 8,
	PersonalStats: 9,
	GetStatistics: 10,
}

const LoginCode = {
	loginSuccess: 0,
	loginError: 1
}

const RegisterCode = {
	signupSuccess: 0,
	signupError: 1
}

const ClientToServerCode = {
	MT_CLIENT_LOG_IN: 200,
	MT_CLIENT_SIGN_UP: 204,
	CREATE_ROOM: 205,
	GET_ROOMS: 206,
	GET_PLAYERS_IN_ROOM: 207,
	JOIN_ROOM: 208,
	GET_STATISTICS: 209,
	LOG_OUT: 210,
}

export {
	ResponseCode,
	LoginCode,
	RegisterCode,
	ClientToServerCode
}