#include "LoginManager.h"

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	_loggedUsersMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		if (!this->m_database->doesUserExist(username)) {
			this->m_database->addNewUser(username, password, email);
			return true;
		}
	_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	return false;
}

bool LoginManager::login(std::string username, std::string password)
{
	_loggedUsersMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		if (this->m_database->doesPasswordMatch(username, password)) {
			this->m_loggedUsers.push_back(LoggedUser(username));
			return true;
		}
	_loggedUsersMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	return false;
}

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

