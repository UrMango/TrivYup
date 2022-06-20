#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, const  RoomData roomData)
{
	m_rooms.insert(std::pair<unsigned int, Room&>(roomData.id, *(new Room(user, roomData))));
}

void RoomManager::deleteRoom(const int ID)
{
	m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(const int ID)const
{
    for (auto& it : m_rooms) {
        if (it.first == ID) {
            return it.second.getRoomState();
        }
    }
}
void RoomManager::changeRoomState(const int state, const int ID)
{
    for (auto& it : m_rooms) {
        if (it.first == ID) {
            return it.second.changeRoomState(state);
        }
    }
}
std::vector<string> RoomManager::getAllUsersInRoom(const int ID)const
{
    for (auto& it : m_rooms) {
        if (it.first == ID) {
            return it.second.getAllUsers();
        }
    }
    return std::vector<string>();
}
RoomData* RoomManager::addUserInRoom(const int ID, LoggedUser user)const
{
    for (auto& it : m_rooms) {
        if (it.first == ID && it.second.getAllUsers().size() < it.second.getRoomData().maxPlayers) {
            std::vector<std::string> users = it.second.getAllUsers();
            for (auto& it2 : users) {
                if (it2 == user.getUsername())
                    return nullptr;
            }
            return it.second.addUser(user);
        }
    }
    return nullptr;
}

void RoomManager::removeUserInRoom(const int ID, LoggedUser user)const
{
    for (auto& it : m_rooms) {
        if (it.first == ID) {
            return it.second.removeUser(user);
        }
    }
}

std::vector<RoomData> RoomManager::getRooms()const
{
    std::vector<RoomData> rooms;
    for (auto& it : m_rooms) {
        if ((it.second.getAllUsers().size() > 0) || (it.second.getRoomState() != 0))
        {
            rooms.push_back(it.second.getRoomData());
        }
    }
    return rooms;
}

Room* RoomManager::getRoom(const unsigned int IDOfRoom)const
{

    auto it = this->m_rooms.find('c');
    for (auto& it : m_rooms) {
        if (it.first == IDOfRoom) {
            return &(it.second);
        }
    }
}