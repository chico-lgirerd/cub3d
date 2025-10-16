#!/bin/bash

for mapfile in maps/errmaps/*; do
  if [ -f "$mapfile" ]; then
    result=$(valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes --quiet ./cub3D "$mapfile" 2>&1)
    # result=$(./cuLb3D "$mapfile" 2>&1)
    echo "$mapfile: $result"
  fi
done
