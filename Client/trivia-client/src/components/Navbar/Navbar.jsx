import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';

import Logo from "../../assets/images/Logo-1150p.png";
import "./Navbar.css";

const Navbar = () => {
    const user = useSelector(state => state.user);
    
	return (
        <>
            <img className="logo" src={Logo} width={80}/>
            <div className="navbar">
                <nav className="nav">
                    <ul className="nav-links">
                        <li><Link to="/">Home</Link></li>
                        { user.isLogged && <><li><Link to="/create">Create Room</Link></li><li><Link to="/play">Play</Link></li></> }
                        { !user.isLogged && <><li><Link to="/auth">Login</Link></li><li><Link className='registerBtn' to="/auth/register">Sign up</Link></li></> }
                        
                    </ul>
                    { user.isLogged && <li><p>Good evening, {user.data?.username}!</p></li>}
                </nav>
            </div>
            <div className='space'></div>
        </>
	)
}

export default Navbar;