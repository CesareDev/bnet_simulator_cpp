#! /usr/bin/env bash

set -e

BUILD_DIR="build"

CONF_FILE="bnet.conf"

CONF_FILE_STR="\
SIM_DURATION = 600

BUOYS_COUNT = 50

MOBILE_BUOY_PERC = 0.10

IDEAL_CHANNEL = 1

BIT_RATE = 1000000

SPEED_OF_LIGHT = 300000000

COMM_RANGE_HIGH_PROB = 70.0

COMM_RANGE_MAX = 120.0

DELIVERY_PROB_HIGH = 0.90

DELIVERY_PROB_LOW = 0.15"

if [ ! -f "$CONF_FILE" ]; then
    echo "No configuration file found, creating one..."
    echo "$CONF_FILE_STR" > bnet.conf
fi

cmake -B "$BUILD_DIR" -S .

echo "Builind the project..."
cd "$BUILD_DIR"
make -j8
