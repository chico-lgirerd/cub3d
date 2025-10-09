#!/bin/bash

for mapfile in maps/errmaps/*; do
  if [ -f "$mapfile" ]; then
    result=$(./cub3D "$mapfile" 2>&1 | grep -E "Valid|Invalid map")
    echo "$mapfile: $result"
  fi
done
