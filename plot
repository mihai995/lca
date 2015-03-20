#!/bin/bash

if [ -n "$1" ]; then
	SRC=$1"/"
else
	SRC="stats/"
fi

if [ -n "$2" ]; then
	DEST=$2"/"
else
	DEST="plots/"
fi

if ! [ -d $DEST ]; then
	mkdir $DEST
fi

for folder in $( ls $SRC )
do
	path=$SRC$folder
	plot=$DEST$folder.dat
	echo -e "\
	set term postscript solid color eps enhanced \"Helvetica\" 16 lw 4 \n\
	set title '"`echo $folder | tr '_' ' '`"' \n\
	set key left \n\
	set xlabel 'Number of Queries' \n\
	set ylabel 'Time (in seconds)' \n\
	set output '$DEST$folder.ps' \n\
	set grid" > $plot

	printf "plot " >> $plot
	for file in $( ls $path )
	do
		name=`echo $file | tr '_' ' '`
		echo -e "\
		'$path/$file' w l title '$name', \\" >> $plot
	done
	gnuplot $plot
done
