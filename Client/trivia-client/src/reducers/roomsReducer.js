const INITIAL_STATE = {
	currentRoom: {},
	rooms: [],
	players: []
};

const roomsReducer = (state = INITIAL_STATE, action) => {
    switch(action.type) {
        case 'ROOM_LIST':
            return {...state, rooms: action.payload.rooms };
        case 'CURR_ROOM':
            return {...state, currentRoom: action.payload };
        case 'PLAYERS':
            return {...state, players: action.payload };
        default:
            return state;
    }
}

export default roomsReducer;