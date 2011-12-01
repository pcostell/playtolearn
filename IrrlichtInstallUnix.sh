#!/bin/bash

echo "Installing irrlicht version $2 into $1" 
mkdir ../../lib 2> /dev/null;
cp $1/lib/Linux/libIrrlicht.so.$2-SVN $1/../../lib/libIrrlicht.so.$2-SVN 2> /dev/null;
ln -s $1/../../lib/libIrrlicht.so.$2-SVN $1/../../lib/libIrrlicht.so 2> /dev/null;
ldconfig -n $1/../../lib;
cp -r $1/include $1/../../include 2> /dev/null;

true