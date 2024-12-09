#!/usr/bin/python3

from socket import socket, AF_INET, SOCK_STREAM, SOMAXCONN, SHUT_RDWR
import sys

def process_connection(conn):
    num = 0
    while num > -1:
        data = conn.recv(4)
        if len(data)==0: break
        num = int.from_bytes(data, byteorder='little', signed=True)
        res = (num+1).to_bytes(4, byteorder='little', signed=True)
        if 0 == num: break
        conn.send(res)
    conn.shutdown(SHUT_RDWR)
    conn.close()


if __name__ == "__main__":
    ip = "0.0.0.0"
    port = int(sys.argv[1])
    sock = socket(AF_INET, SOCK_STREAM)
    sock.bind((ip, port))
    sock.listen(SOMAXCONN)

    conn, _ = sock.accept()
    process_connection(conn)
    sock.close()
