#!/bin/bash
module=$1

if [ $# -lt 1 ];then
    echo "Usage : ./bump_crush_number.sh <module>"
fi
cycle_max=0
measure_num=0
while [ -e ${module}/${cycle_max}c/data.root ]
do
    echo ${cycle_max}
    cycle_max=`expr ${cycle_max} + 5`
    measure_num=`expr ${measure_num} + 1`
done
cycle_max=`expr ${cycle_max} - 5`
#root -l 'bump_crush_number.cpp("'${module}'",'${cycle_max}')'
root -l 'diff_of_cycles.cpp("'${module}'",'${cycle_max}')'
#root -l 'pixels_of_cycles.cpp+("'${module}'",'${measure_num}')'