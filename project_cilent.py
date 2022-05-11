
from websocket import create_connection
import socket
ip = "127.0.0.1"

def receive(ws): #msg from server
    msg = ws.recv()
    print(msg)

def sendMsg(ws): #msg to server
    snd = str(input("Enter msg: "))
    ws.send(snd.encode())

def getPort(): #get port from the user
    port = int(input("Enter port: "))
    while port < 1024 or port > 65535:
        port = int(input("Enter port: "))
    return port

def main():
    try:
        print("searching for server")
        url = "ws://localhost:" + str(getPort())
        ws = create_connection(url)
        receive(ws)
        sendMsg(ws)
        ws.close()
    except Exception as e:
        print(str(e))

if __name__=="__main__":
    main()