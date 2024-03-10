
import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()  # Hide the root window

# Open the file picker dialog
file_path = filedialog.askopenfilename()

print("Selected file:", file_path)
