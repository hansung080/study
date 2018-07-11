#!/bin/bash

if [ $# -ne 1 ]; then
	echo 'Usage : calc.sh "-10*(-100+200)+(22345.678/(20-10))"'
	exit 1
fi

python3 main.py "$1"