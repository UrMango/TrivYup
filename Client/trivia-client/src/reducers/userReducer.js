const INITIAL_STATE = {
    isLogged: false,
    data: null
}

const userReducer = (state = INITIAL_STATE, action) => {
    switch(action.type) {
        case 'LOGIN':
            return { ...state, isLogged: true };
        case 'LOGOUT':
            return { ...state, ...INITIAL_STATE }
        case 'SET_USER_DATA':
            return { ...state, data: action.payload }
        default:
            return state;
    }
}

export default userReducer;