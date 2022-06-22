#include "LoginManager.h"

//***********************************************************************************************
//The function adds a user to database
//***********************************************************************************************
bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	_loggedUsersMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		if (!this->m_database->doesUserExist(username)) {
			this->m_database->addNewUser(username, password, email);
			_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
			return true;
		}
	_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	return false;
}

//***********************************************************************************************
//The function Connects the user to the system
//***********************************************************************************************
bool LoginManager::login(std::string username, std::string password)
{
	_loggedUsersMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		if (this->m_database->doesPasswordMatch(username, password)) {
			this->m_loggedUsers.push_back(LoggedUser(username));
			_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
			return true;
		}
	_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	return false;
}


//***********************************************************************************************
//The function logout the user to the system
//***********************************************************************************************
void LoginManager::logout(std::string username)
{
	_loggedUsersMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		for (int i = 0; i < this->m_loggedUsers.size(); i++)
		{
			if (this->m_loggedUsers[i].getUsername() == username)
			{
				this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
				break;
			}
		}
	_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}

