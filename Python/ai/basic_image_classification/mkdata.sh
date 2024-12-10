#!/bin/bash
mkdir dataset
mkdir dataset/white
mkdir dataset/black
convert -size 100x100 xc:white dataset/white/white.png
convert -size 100x100 xc:black dataset/black/black.png
