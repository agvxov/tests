#package require Tk
#
#canvas .board -width 50 -height 50
#.board create line 0 0 0 50 -fill black -width 10

package require Tk

set a "-width 10"

canvas .board -width 50 -height 50
#.board create line 0 0 0 50 -fill black $a
.board create line 0 0 0 50 -fill black {*}[set a]
