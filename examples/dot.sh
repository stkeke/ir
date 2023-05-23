#!/usr/bin/bash

dot_file="$1"
svg_file="$(basename "$dot_file").svg"
/usr/bin/dot -T svg -o $svg_file $dot_file
ls -l $svg_file
