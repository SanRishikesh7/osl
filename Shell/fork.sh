#!/bin/bash

echo "Parent process: $$"

# Start a background process
sleep 5 &

echo "Background process started"
