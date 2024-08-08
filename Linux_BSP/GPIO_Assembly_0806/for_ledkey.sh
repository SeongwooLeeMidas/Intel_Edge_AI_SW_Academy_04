#!/bin/bash

echo "led0 ~ led7 Test" 
for ((i=518 ; i<526 ; i++))
do
	echo "$i" > /sys/class/gpio/export 
	echo "out" > /sys/class/gpio/gpio${i}/direction 
	echo "1" > /sys/class/gpio/gpio${i}/value 
	echo -n "gpio$((i-512)) led$((i-518)) : "
	cat /sys/class/gpio/gpio${i}/value 
	sleep 1
	echo -n "gpio$((i-512)) led$((i-518)) : "
	echo "0" > /sys/class/gpio/gpio${i}/value 
	cat /sys/class/gpio/gpio${i}/value
	sleep 1
	echo "$i" > /sys/class/gpio/unexport 
done
echo ""
echo "key0 ~ key7 Test" 
for ((i=528 ; i<536 ; i++))
do
	echo "$i" > /sys/class/gpio/export 
	echo "in" > /sys/class/gpio/gpio${i}/direction 
	echo -n "gpio$((i-512)) key$((i-528)) : "
	cat /sys/class/gpio/gpio${i}/value 
	sleep 1
	echo -n "gpio$((i-512)) key$((i-528)) : "
	cat /sys/class/gpio/gpio${i}/value
	sleep 1
	echo "$i" > /sys/class/gpio/unexport 
done
