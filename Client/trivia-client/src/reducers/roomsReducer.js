const INITIAL_STATE = [];

const roomsReducer = (state = INITIAL_STATE, action) => {
    switch(action.type) {
        case 'ROOM_LIST':
            return state.concat([action.payload.rooms[0]]);
        default:
            return state;
    }
}

export default roomsReducer;