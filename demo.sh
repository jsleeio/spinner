#!/bin/bash

# lazy way of generating a bunch of input lines
cat /usr/share/dict/{w,w}{o,o}{r,r}{d,d}{s,s}		\
	| ./spinner "reading all the dictionaries "	\
	| wc -l
