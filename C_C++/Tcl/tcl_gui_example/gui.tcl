# @BAKE tclsh $@
package require Tk

# if not invoked from C tnen run in "testing" mode
if {![info exists ::WRAPPED]} {
    proc cIncrementCounter {} {}
    proc cGetCounter {} { return 0 }
}

wm title . "Tcl Banana Clicker"

# Create a terribly illustrated banana
canvas .banana -width 600 -height 600
.banana create rectangle 100 200 500 300 -fill yellow
.banana create rectangle 500 210 540 240 -fill black
bind .banana <Button-1> {cIncrementCounter}
pack .banana

# Create a score message
label .score
.score configure -font "TkDefaultFont 20"
pack .score

# Loop in an event-driven fashion to query state from C
proc updateState {} {
    .score configure -text "Your current score is: [cGetCounter]"
    after 100 updateState
}

after 100 updateState
bind . <Destroy> {exit}
