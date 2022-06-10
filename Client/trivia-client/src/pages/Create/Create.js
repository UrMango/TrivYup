import { Navigate } from "react-router";
import { useSelector } from "react-redux";

const Create = () => {
	const username = useSelector(state => state.user?.data?.username);

	return (
		<>
			{!username && <Navigate to="/auth/login"/>}
			<div>
				Create Room
			</div>
		</>
	)
}

export default Create;