#include "LoggedUser.h"

std::string LoggedUser::getUsername()
{
    return this->m_username;
}

int LoggedUser::getRoomId()const
{
    return this->roodIdOfOser;
}

void LoggedUser::changeRoomId(const int newId)
{
    this->roodIdOfOser = newId;
}