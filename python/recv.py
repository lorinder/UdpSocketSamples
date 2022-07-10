#!/usr/bin/env python3

import os
import sys
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
sock.bind( ('0.0.0.0', 4321) )

print("Awaiting 3 messages:")
for i in range(3):
    data = sock.recv(8192)
    print(f"  Received \"{data.decode('utf-8')}\"")
sock.close()
