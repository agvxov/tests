#!/bin/python3
import os
os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"

from sys import argv
from tensorflow import keras
from tensorflow.keras.preprocessing import image
import numpy as np

from config import *

model = keras.models.load_model(model_path)

def classify_image(img_path):
	img = image.load_img(img_path, target_size=(img_height, img_width))
	img_array = image.img_to_array(img)
	img_array = np.expand_dims(img_array, axis=0)

	score = model.predict(img_array)[0][0]

	print(f"{100 * score:.2f}% Thing : {100 * (1 - score):.2f}% Not Thing")
	return score > .5

if __name__ == "__main__":
	if len(argv) != 2:
		print(f"Usage: {argv[0]} <image_path>")
		exit(2)
	exit(classify_image(argv[1]))
