import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";
import Home from "./pages/Home/Home";
import Play from "./pages/Play/Play";
import Create from "./pages/Create/Create";
import Auth from "./pages/Auth/Auth";

const App = () => {
  return (
    <div className="App">
      <Router>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/play" element={<Play />} />
          <Route path="/create" element={<Create />} />
          <Route path="/auth" element={<Navigate to="/auth/login"/>} />
          <Route path="/auth/login" element={<Auth type="login"/>} />
          <Route path="/auth/register" element={<Auth type="register"/>} />
        </Routes>
      </Router>
    </div>
  );
}

export default App;
