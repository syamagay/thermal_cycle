#!/bin/bash
mod_id=$1
cycle_num=$2

if [ $# -lt 2 ];then
    echo "Usage:./filecopy.sh <mod_id> <cycle_num>"
    exit
fi

mkdir -p ${mod_id}/${cycle_num}c/picture
sftp atlas-q@192.168.10.76 <<EOF
cd work/KC705/working_fusy/thermal_cycle_analysis

get copylog/${mod_id}_copylog.xlsx ${mod_id}

cd ${mod_id}/${cycle_num}c
get data.root ${mod_id}/${cycle_num}c/
get *png ${mod_id}/${cycle_num}c/
get *pdf ${mod_id}/${cycle_num}c/
exit
EOF
