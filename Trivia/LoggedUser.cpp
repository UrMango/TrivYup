#include "LoggedUser.h"

std::string LoggedUser::getUsername()
{
    return this->m_username;
}

time_t LoggedUser::getMsgTime()
{
    return msgTime;
}

void LoggedUser::setMsgTime(time_t time)
{
    this->msgTime = time;
}

Room* LoggedUser::getRoom()const
{
    return this->roomOfOser;
}

void LoggedUser::changeRoom(Room* Room)
{
    this->roomOfOser = Room;
}

void LoggedUser::removeRoom()
{
    this->roomOfOser = nullptr;
}