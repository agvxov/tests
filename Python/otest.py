#!/bin/python3


#from pynput import mouse
#
#class TrackpadTapDetector:
#    def __init__(self):
#        self.tap_positions = {'top_left': None, 'top_right': None, 'bottom_left': None, 'bottom_right': None}
#
#    def on_click(self, x, y, button, pressed):
#        if pressed:
#            # Record the position of the tap
#            self.tap_positions[button] = (x, y)
#        else:
#            # Check if it's a release and print information
#            if self.tap_positions[button]:
#                release_x, release_y = x, y
#                tap_x, tap_y = self.tap_positions[button]
#                print(f'Tap at ({tap_x}, {tap_y}) released at ({release_x}, {release_y}) with {button}')
#                # Reset the tap position
#                self.tap_positions[button] = None
#
## Create an instance of the TrackpadTapDetector
#tap_detector = TrackpadTapDetector()
#
## Create a mouse listener with the custom on_click method
#with mouse.Listener(on_click=tap_detector.on_click) as listener:
#    print('Listening to trackpad tap events...')
#    listener.join()

from pynput import mouse

def on_move(x, y):
    print(f'Mouse moved to ({x}, {y})')

def on_click(x, y, button, pressed):
    action = 'pressed' if pressed else 'released'
    print(f'Mouse {action} at ({x}, {y}) with {button}')

def on_scroll(x, y, dx, dy):
    print(f'Scrolled at ({x}, {y}) with delta ({dx}, {dy})')

# Create a mouse listener
with mouse.Listener(on_move=on_move, on_click=on_click, on_scroll=on_scroll) as listener:
    print('Listening to trackpad events...')
    listener.join()
