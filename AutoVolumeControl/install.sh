#!/bin/sh

# Shared library for ALSA apps
if [ -x "$(command dpkg -s libasound2)" ]; then
    sudo apt-get install libasound2-dev
fi

#make 
#run
#gpd11  main.c -o out/main.o -pthread -lasound