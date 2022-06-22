import { useState } from "react";
import { useDispatch, useSelector } from "react-redux";
import { useNavigate } from "react-router";

import "./Alert.css";

const Alert = ({text, type}) => {
    const dispatch = useDispatch();

    /**
     * Function that closes the alert with redux
     */
    const handleCloseAlert = () => {
        dispatch({type: "ALERT", payload: null});
    };

	return (
        <div className="alertContainer">
            <div className="alert">
                <div className="upper">
                    <button className="x" onClick={handleCloseAlert}>X</button>
                    <h2 className="type">{type}</h2>
                    <div></div>
                </div>
                <h4>{text}</h4>
            </div>
        </div>
    )
}

export default Alert;