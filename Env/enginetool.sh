#!/bin/bash
set -e

if [ $# -eq 0 ];
  then
    echo "No arguments supplied. Add some."
fi

if [ "$1" == 'build' ];
then
    echo "building..."
    cd '../Source/' 
    make -f makefile
    if [ "$2" == '-rd' ];
    then
        #cd '../Output/Debug/'
        ../Output/Debug/Engine.out
        echo "run"
    fi
fi

if [ "$1" == 'run' ];
    then ../Output/Debug/Engine.out
fi


