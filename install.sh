#!/bin/bash

# Script installs required dependencies, then builds and installs the SDK.
# NOTE: must be run as root/admin
# NOTE: only Linux currently implemented 

if [[ "$OSTYPE" == "linux-gnu"* ]]; then

    # Make sure everything is up to date
    apt-get update --yes
    apt-get upgrade --yes
    # Dependencies
    DEBIAN_FRONTEND="noninteractive" apt-get install --yes build-essential cmake libboost-all-dev
    echo "Starting build..."
    if [ -d "build" ]
    then
        echo "build folder already exists, will be overwritten"
    else
        mkdir build 
    fi    
    cd build
    echo "Build directory: " $PWD
    cmake ..
    cmake --build . --target install

    # TODO: Add docs setup

elif [[ "$OSTYPE" == "msys" ]]; then
    # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
    # NOT IMPLEMENTED
    echo "Windows install not yet supported. Contact smccarthy@oxts.com"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # Mac OSX
    # NOT IMPLEMENTED
    echo "Mac OSX install not yet supported. Contact smccarthy@oxts.com"

else 
    echo "OS not identified - install cancelled. Contact smccarthy@oxts.com"
fi