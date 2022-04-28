import socket
import json
import time

SERVER_ADDRESS = ('127.0.0.1', 2022)


def main():
    with socket.socket(type=socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_ADDRESS)

        signup = '20064{"username":"user1","password":"1234","email":"user1@gmail.com"}'
        sock.sendall(signup.encode())
        res = sock.recv(1024).decode()
        print(res)

        login = '10038{"username":"user1","password":"1234"}'
        sock.sendall(login.encode())
        res = sock.recv(1024).decode()
        print(res)


if __name__ == '__main__':
    main()
