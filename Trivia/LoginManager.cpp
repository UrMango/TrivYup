#include "LoginManager.h"

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (!this->m_database->doesUserExist(username)) {
		this->m_database->addNewUser(username, password, email);
		return true;
	}
	return false;
}

bool LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesPasswordMatch(username, password)) {
		this->m_loggedUsers.push_back(LoggedUser(username));
		return true;
	}
	else
		return false;
}

void LoginManager::logout(std::string username)
{
	for (int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (this->m_loggedUsers[i].getUsername() == username)
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
			break;
		}
	}
}
