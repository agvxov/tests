#!/bin/python3
from sys import argv
from tensorflow import keras

my_activation = ( # declared like this to ease commenting/uncommenting
	#'sigmoid'
	# performs like absolute trash
	# requires ~x4 more epochs than relu

	#'relu'
	# has the tendency to produce such probabilities:
	#  white.png - 0.00% black : 100.00% white 
	#  black.png - 51.10% black : 48.90% white
	# requires roughly 50 epochs and slight luck

	'tanh'
	# easily adjusts under 10 epochs
	# produces reasonable divided probabilites
)

HEIGHT, WIDTH = 20, 20

dataset = keras.utils.image_dataset_from_directory(
	"dataset/",
	image_size=(HEIGHT, WIDTH),
)

model = keras.Sequential([
    keras.layers.Flatten(),
    keras.layers.Dense(8, activation=my_activation),
    keras.layers.Dense(8, activation=my_activation),
    keras.layers.Dense(1, activation='sigmoid')
])

model.compile(
	'adam',
    loss='binary_crossentropy',
    metrics=['accuracy']
)

model.fit(dataset, epochs=10)

img = keras.preprocessing.image.load_img(argv[1], target_size=(HEIGHT, WIDTH))
img = keras.utils.img_to_array(img)
img = keras.ops.expand_dims(img, 0)

score = model.predict(img)[0][0]
print(f"{100 * (1 - score):.2f}% black : {100 * score:.2f}% white")
