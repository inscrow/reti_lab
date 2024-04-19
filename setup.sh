#!/bin/bash

USAGE=`echo "Usage:\n\tsetup.sh <port>  -  Open specified port"`

if [ "$1" != "" ]; then
	sudo iptables -A INPUT -p tcp --dport ${1} -j ACCEPT
else
	echo ${USAGE}
fi
