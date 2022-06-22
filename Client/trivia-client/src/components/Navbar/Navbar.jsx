import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';

import Logo from "../../assets/images/Logo-1150p.png";
import "./Navbar.css";

const Navbar = () => {
    const user = useSelector(state => state.user);
    
    var today = new Date();
    var curHr = today.getHours();
    
    let msg = "";
    // calculate time
    if (curHr >= 5 && curHr < 12) {
        msg = 'Good morning';
    } else if (curHr >= 12 && curHr < 18) {
        msg = 'Good afternoon';
    } else if (curHr >= 18 && curHr <= 10) {
        msg = 'Good evening';
    } else {
        msg = 'Good night';
    }

	return (
        <>
            <img className="logo-navbar" src={Logo} width={80}/>
            <div className="navbar">
                <nav className="nav">
                    <ul className="nav-links">
                        <li><Link to="/">Home</Link></li>
                        { user.isLogged && <><li><Link to="/play">Play</Link></li><li><Link to="/create">Create Room</Link></li></> }
                        { !user.isLogged && <><li><Link to="/auth">Login</Link></li><li><Link className='registerBtn' to="/auth/register">Sign up</Link></li></> }  
                    </ul>
                    { user.isLogged && <p>{msg}, {user.data?.username}!</p>}
                </nav>
            </div>
        </>
	)
}

export default Navbar;