const INITIAL_STATE = [];

const roomsReducer = (state = INITIAL_STATE, action) => {
    switch(action.type) {
        case 'ROOM_LIST':
            return action.payload.rooms;
        default:
            return state;
    }
}

export default roomsReducer;