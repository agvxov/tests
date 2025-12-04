#!/bin/python

# sockets.py

import asyncio
import websockets
import json

async def send_data(ws):
	while True:
		j = {}
		with open('data.txt', 'r') as f:
			for line in f:
				key, value = map(str.strip, line.split(':', 1))
				j[key] = value
		await ws.send(json.dumps(j, indent=4))
		await asyncio.sleep(2)

asyncio.get_event_loop().run_until_complete(websockets.serve(send_data, 'localhost', 8765))
asyncio.get_event_loop().run_forever()
