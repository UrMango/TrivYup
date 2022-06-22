#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser* user, const  RoomData roomData)
{
    _roomsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	    m_rooms.insert(std::pair<unsigned int, Room&>(roomData.id, *(new Room(user, roomData))));
    _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}

void RoomManager::deleteRoom(const int ID)
{
    _roomsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	    m_rooms.erase(ID);
    _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}

unsigned int RoomManager::getRoomState(const int ID)
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
std::vector<string> RoomManager::getAllUsersInRoom(const int ID)
{
    for (auto& it : m_rooms) {
        if (it.first == ID) {
            return it.second.getAllUsers();
        }
    }
    return std::vector<string>();
}
RoomData* RoomManager::addUserInRoom(const int ID, LoggedUser* user)
{
    _roomsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        for (auto& it : m_rooms) {
            if (it.first == ID && it.second.getAllUsers().size() < it.second.getRoomData().maxPlayers) {
                std::vector<std::string> users = it.second.getAllUsers();
                for (auto& it2 : users) {
                    if (it2 == user->getUsername())
                        _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
                        return nullptr;
                }
                _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
                return it.second.addUser(user);
            }
        }
    _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
    return nullptr;
}

void RoomManager::removeUserInRoom(const int ID, LoggedUser* user)
{
    _roomsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        for (auto& it : m_rooms) {
            if (it.first == ID) {
                _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
                return it.second.removeUser(user);
            }
        }
    _roomsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}

std::vector<RoomData> RoomManager::getRooms()
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

Room* RoomManager::getRoom(const unsigned int idOfRoom)
{
    for (auto it : m_rooms) {
        if (it.first == idOfRoom) {
            return &(it.second);
        }
    }
}