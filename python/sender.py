#!/usr/bin/env python3

import socket
import time

addr = '127.0.0.1'
port = 4321

socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

print("Sending 3 messages:")
for i in range(1, 4):
    msg = f"Hi, there {i}"
    print(f"  Sending message \"{msg}\"")
    socket.sendto(msg.encode('utf-8'), (addr, port))
    time.sleep(1)
print("Done.")
socket.close()
