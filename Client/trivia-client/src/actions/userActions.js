const login = () => ({
	type: "LOGIN"
});

const logout = (payload) => ({
	type: "LOGOUT",
	payload
});

const setUserData = (payload) => ({
	type: "SET_USER_DATA",
	payload
});

export { login, logout, setUserData };