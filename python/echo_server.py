#!/usr/bin/env python

import os
import sys
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
sock.bind( ('0.0.0.0', 7712) )

while True:
    (data, addrinfo) = sock.recvfrom(8192)
    print("From %s: \"%s\"" % (addrinfo, data))

    # echo.
    sock.sendto(data, addrinfo)

    # quit if requested.
    if data == b'quit':
        print("quit packet received, exiting.")
        sys.exit(0)
