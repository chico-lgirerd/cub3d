#!/bin/bash

GREEN='\e[32m'
RED='\e[31m'
BLUE='\e[34m'
DEF='\e[0m'

for mapfile in maps/errmaps/*; do
  if [ -f "$mapfile" ]; then
    result=$(valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes --show-leak-kinds=all ./cub3D "$mapfile" 2>&1)
    # result=$(./cub3D "$mapfile" 2>&1)
    line=$(echo "$result" | grep "in use at exit:")
    bytes=$(echo "$line" | sed -n 's/.*in use at exit: \([0-9]*\) bytes.*/\1/p')
    if [ "$bytes" == "0" ]; then
      color=$GREEN
    else
      color=$RED
    fi
    echo -e "$BLUE$mapfile :$DEF"
    echo
    echo "$result" | while IFS= read -r line; do
      if [[ "$line" == *"in use at exit:"* ]]; then
        echo -e "$color$line$DEF"
      else
        echo "$line"
      fi
    done
    echo
    echo "-------------------"
    echo
  fi
done
