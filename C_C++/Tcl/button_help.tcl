package require Tk

wm title . "Button example"
frame .main
pack .main
button .mybutton -text "press me" -command baah
pack .mybutton
