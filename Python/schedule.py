#!/bin/python3
import heapq
import time
from dataclasses import dataclass, field

@dataclass(order=True)
class PollingTask:
	next_run : float
	interval : float
	callback : callable = field(compare=False)

heap = []

def add_polling(interval, callback):
	now = time.monotonic()
	heapq.heappush(heap, PollingTask(
		next_run=now + interval,
		interval=interval,
		callback=callback,
	))

def mainloop():
	while True:
		now = time.monotonic()
		if heap:
			if heap[0].next_run <= now:
				task = heapq.heappop(heap)
				task.callback()
				task.next_run = now + task.interval
				heapq.heappush(heap, task)
			else:
				time.sleep(0.1)

def threer_callback(): print(3)
def fiver_callback():  print(5)
def tf_callback():     print(15)

add_polling(3,  threer_callback)
add_polling(5,  fiver_callback)
add_polling(15, tf_callback)

mainloop()
