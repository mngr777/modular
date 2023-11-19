#!/bin/bash

mkdir -p m4
aclocal

libtoolize

touch AUTHORS ChangeLog NEWS README

mkdir -p autoconf-aux
automake --add-missing

autoconf
