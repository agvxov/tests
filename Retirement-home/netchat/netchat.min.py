import sys,signal as S
s=__import__("socket").socket()
s.bind(("localhost",int(sys.argv[1])))
s.listen()
s.setblocking(0)
S.signal(2,lambda a,b:(s.close(),exit(0)))
print(f"Listening on {sys.argv[1]}...")
def U(i):
	i[0].settimeout(1)
	return ["anon"+str((id(i[0])%999+1)),i[0]]
u=[]
while 1:
	try:u+=[(U(s.accept()))]
	except OSError:pass
	for i in u:
		try:
			m=i[1].recv(1024)
			if m:
				for h in u:h[1].send((i[0]+": "+m.decode()).encode())
		except OSError:pass
