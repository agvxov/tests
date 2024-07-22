#!/bin/python3
import numpy as np
from tensorflow import keras

# ---------------
# --- Dataset ---
# ---------------
def gen_data():
	# Addition in the finite field of 0..10
	r = {'in': [], 'out': []}
	for i in range(10):
		for h in range(10):
			r['in'].append((i, h))
			r['out'].append((i + h) % 10)
	r['in'] = np.array(r['in'])
	r['out'] = np.array(r['out'])
	return r
dataset = gen_data()

# -------------
# --- Model ---
# -------------
model = keras.Sequential()	# Stock feedforward network

hidden_layers = [2, 8, 4, 10, 8] # Overkill is the best kind of kill
for i in hidden_layers: model.add(keras.layers.Dense(i, activation='relu'))
model.add(keras.layers.Dense(1))	# output layer

model.compile(
	optimizer='adam',
	loss='mse',
	metrics=['accuracy']
)

# Training
model.fit(dataset['in'], dataset['out'],
	verbose=2,
	batch_size=10,
	epochs=1000,	# Repetition count on the whole dataset
	shuffle=True,
)

# ------------------------------
# --- Interactive playground ---
# ------------------------------
#NOTE: importing will work too
def main():
	while True:
		try:
			a = int(input("Enter the first integer (a): "))
			b = int(input("Enter the second integer (b): "))
			
			r1 = model.predict(np.array([(a, b)]))[0][0]
			r2 = np.round(r1)
			print(f"The sum of {a} and {b} is {r2} ({r1})")
		except ValueError:
			pass

if __name__ == '__main__':
	main()
