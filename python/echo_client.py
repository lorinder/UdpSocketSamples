#!/usr/bin/env python3

import getopt
import os
import sys
import socket

addr = '127.0.0.1'
origin_port = 7713
port = 7712
msg = b"hi there"
wait = False

(opts, args) = getopt.getopt(sys.argv[1:], 'a:p:wh')
for (k, v) in opts:
    if k == '-a':
        addr = v
    elif k == '-p':
        port = int(v)
    elif k == '-w':
        wait = True
    elif k == '-h':
        print("simple single message udp sender")
        print("")
        print("usage:  echo_sender.py [ -a addr ] [ -p port ] message")
        print("")
        print("   -h                display help & exit")
        print("   -a ip_addr        specify ip addr to send to")
        print("   -p port           specify destination port")
        print("   -w                wait for response and display")
        sys.exit(0)
if len(args) > 0:
    msg = " ".join(args).encode()

socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
socket.bind( ('0.0.0.0', origin_port) )
socket.sendto(msg, (addr, port))
if wait:
    (data, addrinfo) = socket.recvfrom(8192)
    print("Response from %s: \"%s\"" % (addrinfo, data))
