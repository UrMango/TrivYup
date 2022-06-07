import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';
import "./Navbar.css";


const Navbar = () => {
    const user = useSelector(state => state.user);
    
	return (
        <>
            <div className="navbar">
                <nav className="nav">
                    <ul className="nav-links">
                        <li><Link to="/">Home</Link></li>
                        { user.isLogged && <><li><Link to="/create">Create Room</Link></li><li><Link to="/play">Play</Link></li></> }
                        { !user.isLogged && <><li><Link to="/auth">Login</Link></li><li><Link to="/auth/register">Register</Link></li></> }
                        { user.isLogged && <li><p>Good evening, {user.data?.username}!</p></li>}
                    </ul>
                </nav>
            </div>
            <div className='space'></div>
        </>
	)
}

export default Navbar;