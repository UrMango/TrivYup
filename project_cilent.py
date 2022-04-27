import socket
ip = "127.0.0.1"

def receive(): #msg from server
    msg = client.recv(1024)
    print(msg.decode())

def sendMsg(): #msg to server
    snd = str(input("Enter msg: "))
    client.send(snd.encode())

def getPort(): #get port from the user
    port = int(input("Enter port: "))
    while port < 1024 or port > 65535:
        port = int(input("Enter port: "))
    return port

def main():
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("searching for server")
        client.connect((ip, getPort()))

        sendMsg()
        receive()
    except Exception as e:
        print(str(e))

if __name__=="__main__":
    main()
