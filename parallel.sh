#!/bin/bash

# Set the number of parallel runs
N=$1

if [ -z "$N" ] || [ -z "$2" ]; then
  echo "Usage: $0 <parallel_runs> <program> [args...]"
  exit 1
fi

PROGRAM=$2
shift 2

# Handle Ctrl+C and terminate all running processes
cleanup() {
  echo "Interrupt received. Terminating all processes..."
  kill $(jobs -p) 2>/dev/null
  exit 1
}

trap cleanup SIGINT

for ((i=1; i<=N; i++)); do
  $PROGRAM "$@" & 
done

wait

echo "All $N instances have finished."

