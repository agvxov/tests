(claw-raylib:with-window (800 450 "test")
  (loop until (claw-raylib:window-should-close)
        do
           (claw-raylib:begin-drawing)
           (claw-raylib:clear-background claw-raylib:+raywhite+)
           (claw-raylib:draw-text "it works" 300 200 20 claw-raylib:+black+)
           (claw-raylib:end-drawing)))
