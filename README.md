RTCGateway
==========

RT-Component Gateway for MAX/MSP


#1.HOW TO BUILD

#1.1 MacOSX Mountain Lion

needs: Xcode 4.1.6, MAX/MSP6

First, submodule must be downloaded. Input...

# git submodule init
# git submodule update

Then, execute shell script...

# ./build.sh

Then, you can get RTCGateway.mxo

This file is the RT-component communication plugin for MAX/MSP (usually, the pluging binaries are called EXTERNAL OBJECT by MAX/MSP users and developers.)
You must plate the external object in the directory where the MAX/MSP's search path. Usually, you can find Max directory in your default document directory that is automatically generated by the MAX/MSP when it is launched at first time.