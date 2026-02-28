#!/bin/bash

ffplay \
    -fflags nobuffer \
    -flags low_delay \
    -fast \
    -sync video \
    -probesize 32 \
    -analyzeduration 0 \
    -framedrop \
    -f mpegts \
    udp://10.8.0.102:5000
