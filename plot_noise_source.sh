#!/bin/bash
#module=$1
#cycle=$2
#option=$3
#save=$4
if [ $# -eq 0 ];then
    echo "./plot_noise_source.sh <-m:module_name> <-c:cycle_number> <option:-q> <option:-w>"
    exit
fi

save_para=0
while getopts m:c:qw OPT
do
    case $OPT in
	"m" ) module="${OPTARG}" ;;
	"c" ) cycle=${OPTARG} ;;
	"q" ) option="-q" ;;
	"w" ) save_para=1 ;;
    esac
done

mkdir -p ${module}/${cycle}c/picture
root -l ${option} 'plot_noise_source.cpp+("'${module}'",'${cycle}','${save_para}')'