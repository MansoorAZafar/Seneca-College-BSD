# Lab 6

Lab 6, Client and Server communication, 2 separate processes that communicate via sockets. Supports TCP, UDP, Stream, Dgram forms of commmunication with thread-safe logging.

## Command Line Arguments
| **Key**      | **Value**            | Required | default value |
| ------------ | ---------------------| -------- | ------------- |
| -domain      | tcp/udp/dgram/stream | No       | stream        |
| -log-level   | debug/info           | No      | info          |

# Instructions
## Build the Project
```bash
make # builds the project 
```

## Run the Project
```bash
# Running with default args
./out/server.exe 

# open another terminal
./out/client.exe 

# Customizing args
# MAKE SURE SERVER AND CLIENT MATCH -domain
./out/server.exe -domain tcp
./out/client.exe -domain tcp 
```