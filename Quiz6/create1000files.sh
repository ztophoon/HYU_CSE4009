#!/bin/sh

for i in $(seq 1 1000)
do
	touch "${i}".txt
done
exit 0
