#!/bin/bash
module=$1

if [ $# -lt 1 ];then
    echo "Usage : ./bump_crush_number.sh <module>"
    exit
fi
cycle_max=0
measure_num=0
while [ -e ${module}/${cycle_max}c/data.root ]
do
    echo ${cycle_max}
    if [ ${cycle_max} -gt 99 ];then
	cycle_max=`expr ${cycle_max} + 20`
    elif [ ${cycle_max} -eq 85 ];then
	cycle_max=`expr ${cycle_max} + 15`
    else
	cycle_max=`expr ${cycle_max} + 5`
    fi
    measure_num=`expr ${measure_num} + 1`
done
cycle_max=`expr ${cycle_max} - 5`
root -l 'bump_crush_number.cpp("'${module}'",'${measure_num}')'
#root -l 'diff_of_cycles.cpp("'${module}'",'${cycle_max}')'
#root -l 'pixels_of_cycles.cpp+("'${module}'",'${measure_num}')'