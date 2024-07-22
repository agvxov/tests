#!/usr/bin/tclsh
package require Tk

frame .f -width 250 -height 250 -borderwidth 3 -background white
pack .f

.f configure -background [tk_chooseColor -initialcolor gray -title "Pick A Color"]
