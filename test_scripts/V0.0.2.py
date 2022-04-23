import socket
import json
import time

SERVER_ADDRESS = ('127.0.0.1', 2022)


def main():
    with socket.socket(type=socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_ADDRESS)

        signup = json.loads({"username": "user1", "password": "1234", "mail": "user1@gmail.com"})
        sock.sendall(signup)
        time.sleep(30)
        res = sock.recv(1024).decode()

        login = json.loads({"username": "user1", "password": "1234"})
        sock.sendall(login)
        res = sock.recv(1024).decode()


if __name__ == '__main__':
    main()
