#!/bin/bash

LOC=`dirname "$0"`
SCRIPT_NAME=server.py

flock -w 1 ${LOC}/server.lock nohup "${LOC}/${SCRIPT_NAME}" 5007 > ${LOC}/server.log 2>&1 &
sleep 1