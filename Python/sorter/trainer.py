#!/bin/python3
import os
os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
from config import *

batch_size = 64

dataset = tf.keras.preprocessing.image_dataset_from_directory(
    'dataset/',
    image_size=(img_height, img_width),
    batch_size=batch_size,
    label_mode='binary',
	validation_split=.2,
	subset='both',
	seed=42,
)

model = keras.Sequential([
    layers.Rescaling(1/255, input_shape=(img_height, img_width, 3)),
    layers.Conv2D(32, (3, 3), activation='relu'),
    layers.MaxPooling2D(),
    layers.Conv2D(64, (3, 3), activation='relu'),
    layers.MaxPooling2D(),
    layers.Conv2D(128, (3, 3), activation='relu'),
    layers.MaxPooling2D(),
    layers.Flatten(),
    layers.Dense(128, activation='relu'),
    layers.Dense(128, activation='relu'),
    layers.Dense(128, activation='relu'),
    layers.Dense(1, activation='sigmoid')
])

model.compile(
	#optimizer='adam',
	optimizer=keras.optimizers.Adam(learning_rate=.002),
    loss='binary_crossentropy',
    metrics=['accuracy'],
)

history = model.fit(
	dataset[0],
	validation_data=dataset[1],
	epochs=12,
)

model.save('my_model.keras')

# --- Plotting ---

import matplotlib.pyplot as plt

# Plot training & validation accuracy values
plt.figure(figsize=(12, 4))
plt.subplot(1, 2, 1)
plt.plot(history.history['accuracy'],     label='Training Accuracy')
plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
plt.title('Model accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')
plt.ylim([0, 1])

# Plot training & validation loss values
plt.subplot(1, 2, 2)
plt.plot(history.history['loss'],     label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.title('Model loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.ylim([0, 5])

plt.show()
