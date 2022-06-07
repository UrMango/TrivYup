const ResponseCode = {
	error: 0,
	login: 1,
	signup: 2
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
	CREATE_ROOM: 1,
	GET_ROOMS: 2,
	GET_PLAYERS_IN_ROOM: 3,
	JOIN_ROOM: 4,
	GET_STATISTICS: 5,
	LOG_OUT: 6,
}

export {
	ResponseCode,
	LoginCode,
	RegisterCode,
	ClientToServerCode
}