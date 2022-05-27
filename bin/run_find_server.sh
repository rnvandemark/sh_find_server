#!/bin/bash

# Run a FIND3 server
# Three arguments are required:
# - The path for the database to inhabit (e.g. '/home/$USER/FIND_DATA')
# - The database admin username
# - The database admin password
# The docker container name can be overridden (default is 'find3server')
# The address of the server can be overridden (default is the first IP of this host)
# The port of the server can be overridden (default is '8005')

CONTAINER_NAME="${CONTAINER_NAME:-"find3server"}"
FIND3_SERVER_ADDRESS="${FIND3_SERVER_ADDRESS:-"http://$(hostname -I | awk '{print $1}')"}"
FIND3_SERVER_PORT="${FIND3_SERVER_PORT:-8005}"

if [ 3 -ne $# ]; then echo "Incorrect number of arguments given, expected 3." >&2; exit 1; fi

echo "Starting server in container '$CONTAINER_NAME' at '$FIND3_SERVER_ADDRESS'"
docker run \
    -p "1884:1883" -p "$FIND3_SERVER_PORT:8003" \
    -v "$1:/data" \
    -e MQTT_ADMIN="$2" \
    -e MQTT_PASS="$3" \
    -e MQTT_SERVER='localhost:1883' \
    -e MQTT_EXTERNAL="$FIND3_SERVER_ADDRESS" \
    -e MQTT_PORT=1884 \
    --name "$CONTAINER_NAME" \
    -d -t schollz/find3
