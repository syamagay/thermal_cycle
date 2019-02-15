#!/bin/bash
module=$1
cycle=$2

if [ $# -eq 0 ];then
    echo "./plot_noise_source.sh <module_name> <cycle_number>"
    exit
fi
mkdir -p ${module}/${cycle}c/picture
root -l 'plot_noise_source.cpp("'${module}'",'${cycle}')'