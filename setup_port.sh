#!/bin/bash

port="$1"

# Open port
if command -v "firewall-cmd" &> /dev/null; then
	firewall-cmd --add-port="$port"/tcp
else
	iptables -A INPUT -p tcp --dport "$port" -j ACCEPT
fi
