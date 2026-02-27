#! /usr/bin/env bash

set -e

BUILD_DIR="build"

CONF_FILE="bnet.conf"

CONF_FILE_STR="\
# Simulation duration in seconds
SIM_DURATION = 600

# Number of buoys
BUOYS_COUNT = 50

# Percentage of mobile buoys
MOBILE_BUOY_PERC = 0.10"

if [ ! -f "$CONF_FILE" ]; then
    echo "No configuration file found, creating one..."
    echo "$CONF_FILE_STR" > bnet.conf
fi

cmake -B "$BUILD_DIR" -S .

echo "Builind the project..."
cd "$BUILD_DIR"
make -j8
