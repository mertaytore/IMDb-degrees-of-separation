#!/bin/bash
# several awk commands to get the relevant parts of the IMDb dataset.

# 1
awk -F'[\t]+'  '!/^[\t*]/ {print $1, "\n\t\t\t", $2;next} /^[\t*]/ {print $0;next }' act2.txt //modify file 

# 2
awk 'match($0, /.*\([0-9][0-9][0-9][0-9](\/(I|V|X)*)?\)/) {print substr($0, RSTART, RLENGTH);next} !/^[\t*]/ {print $0;next}!/\[.*Himself.*\]|\[.*Themselves.*\]/ {print}' d.txt  //delete lines containing himself, themsleves

# 3
awk '/^[ \t]+$/ {print ""} !/^[ \t]+$/ {print}'//remove whitespace lines

# 4
awk 'BEGIN { RS = "" ; FS = "\n" }{for( i=1; i<=NF;i++){if( !seen[$i]++){print $i}};delete seen;print""}' filename //delete duplicate entries

# 5
awk 'BEGIN {  RS = "" ; FS = "[\n][\t]*" }{out=$1 ;for( i=2; i<=NF;i++){out = out","$i};print out}' filename // turn into csv

