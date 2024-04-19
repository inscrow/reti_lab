# Networking

## Dependencies

`iptables` is required at least for the server part, as it is used to open a
port for listening.

Some useful programs for this course are:

- a terminal emulator 
- `nc` (netcat package)
- `netstat`
- `telnet`

## Setup

Before running the server, run the `setup.sh` script to open ports for
listening, otherwise only local connection is usable.

## Running

### Server

To run the server simply run:

```sh
./setup.sh <port>
./server <port>
```

in your terminal.

For example, if you want to use port 8080 (make sure it's unused before doing
this):

```sh
./setup.sh 8080
./server 8080
```

### Client

To run the client simply run:

```sh
./client <ip_addr> <port>
```

For example, to run locally, at port 8080:

```sh
./client 127.0.0.1 8080
```
