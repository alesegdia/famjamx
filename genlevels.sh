#!/usr/bin/env bash

function createmapfile {
	echo "#include \"levels.h\""
	echo ""
	echo "Levels::Levels()"
	echo "{"
	find assets/ -type f -name *.bmp | xargs -I % bin/bmptomap.exe %
	echo ""
	echo "}"
}

createmapfile > src/core/levels.cpp
