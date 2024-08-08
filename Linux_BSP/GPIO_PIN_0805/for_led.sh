#!/bin/bash

for ((i=518 ; i<526; i++))
do
	echo "$i" > /sys/class/gpio/export 
	echo "out" > /sys/class/gpio/gpio${i}/direction 
	echo "1" > /sys/class/gpio/gpio${i}/value 
	echo -n "gpio$i : "
	cat /sys/class/gpio/gpio${i}/value 
	sleep 1
	echo -n "gpio$i : "
	echo "0" > /sys/class/gpio/gpio${i}/value 
	cat /sys/class/gpio/gpio${i}/value
	sleep 1
	echo "$i" > /sys/class/gpio/unexport 
done

