import { combineReducers } from "redux";
import userReducer from "./userReducer";
import roomsReducer from "./roomsReducer";

const allReducers = combineReducers({
	user: userReducer,
	rooms: roomsReducer
});

export default allReducers;