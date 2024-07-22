package require Tk
set tileWidth 50
set wallWidth 10

canvas .c11 -width $::tileWidth -height $::tileWidth
.c11 create line 0 0 0 $::tileWidth -fill black -width $::wallWidth

#canvas .c12 -width $::wallWidth -height $::tileWidth -bg black
canvas .c12 -width $::tileWidth -height $::tileWidth
.c12 create line 0 0 0 $::tileWidth -fill black -width $::wallWidth

grid .c11 -row 1 -column 1
grid .c12 -row 1 -column 2
