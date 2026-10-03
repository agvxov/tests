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
		self.skip = 0

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
				if i != h:
					h.skip += 1
					h.socket.send(("\033[s\033[" + str(h.skip) + "E" + i.username + ": " + msg.decode() + "\033[u").encode())
				else:
					print(h, "skip:", h.skip, "going down:", h.skip-1)
					i.socket.send(("\033[" + str(i.skip-1) + "E" + i.username + ": " + msg.decode()).encode())
					i.skip = 0
