#!/bin/bash
module=$1

if [ $# -lt 1 ];then
    echo "Usage : ./bump_crush_number.sh <module>"
fi
cycle_max=0;
while [ -e ${module}/${cycle_max}c/data.root ]
do
    echo ${cycle_max}
    cycle_max=`expr ${cycle_max} + 5`
done
cycle_max=`expr ${cycle_max} - 5`
root -l 'bump_crush_number.cpp("'${module}'",'${cycle_max}')'