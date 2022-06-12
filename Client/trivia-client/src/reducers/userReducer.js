const INITIAL_STATE = {
    isLogged: false,
    data: null,
    statistics: [],
    highscores: []
}

const userReducer = (state = INITIAL_STATE, action) => {
    switch(action.type) {
        case 'LOGIN':
            return { ...state, isLogged: true };
        case 'LOGOUT':
            return { ...state, ...INITIAL_STATE }
        case 'SET_USER_DATA':
            return { ...state, data: action.payload }
        case 'STATS':
            return { ...state, statistics: action.payload }
        case 'HIGHSCORES':
            return { ...state, highscores: action.payload }
        default:
            return state;
    }
}

export default userReducer;