#!/bin/python3
import socket
from sys import argv
from signal import signal, SIGINT

socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.bind(('localhost', int(argv[1])))
socket.listen(100)
socket.setblocking(False)

signal(SIGINT, lambda a, b: (socket.close(), exit(0)))

print(f"Listening on {argv[1]}...")

class User:
	def __init__(self, i):
		self.username = "anon" + str((id(self) % 999 + 1))
		self.socket, _ = i
		self.socket.settimeout(1)

users = []

while True:
	try:
		users.append(User(socket.accept()))
	except BlockingIOError:
		pass
	for i in users:
		try:
			msg = i.socket.recv(1024)
		except TimeoutError:
			continue
		if msg:
		   for h in users:
			   h.socket.send((i.username + ": " + msg.decode()).encode())
