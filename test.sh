#!/bin/bash

make re

./ft_containers > ft_out
./std_containers > std_out

diff ft_out std_out > /dev/null 2>&1
error=$?
if [ $error -eq 0 ]
then
	echo "ft_out and std_out have no difference"
elif [ $error -eq 1 ]
then
	echo "ft_out and std_out differ"
	read -p "Look side by side (1) or simple (0): " details
	if [ $details -eq 1 ]
	then
		diff -y ft_out std_out
	else
		diff ft_out std_out
	fi
else
	echo "There was something wrong with the diff command"
fi

make fclean
rm ft_out
rm std_out