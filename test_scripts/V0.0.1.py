import socket

SERVER_ADDRESS = ('127.0.0.1', 2022)


def main():
    with socket.socket(type=socket.SOCK_STREAM) as sock:
        sock.connect(SERVER_ADDRESS)
        res = sock.recv(1024).decode()
        if (res == "hello"):
            sock.sendall("hello".encode())


if __name__ == '__main__':
    main()
