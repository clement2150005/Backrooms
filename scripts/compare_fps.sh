#!/bin/bash

# Ensure two program paths and a string argument are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <path_to_program_1> <path_to_program_2> <string_argument>"
    exit 1
fi

PROGRAM1="$1"
PROGRAM2="$2"
ARGUMENT="$3"

RUNS=20
TOTAL_FPS1=0
TOTAL_FPS2=0

echo "Running programs $RUNS times each (alternating) with argument: \"$ARGUMENT\""
echo ""

# Run the programs alternately
for ((i = 1; i <= RUNS; i++)); do
    echo "Run #$i"

    # Run Program 1 and capture output
    OUTPUT1=$($PROGRAM1 "$ARGUMENT")
    FPS1=$(echo "$OUTPUT1" | grep -oE '[0-9]+\.[0-9]+')  # Extract FPS
    echo "$PROGRAM1 -> FPS: $FPS1"
    TOTAL_FPS1=$(echo "$TOTAL_FPS1 + $FPS1" | bc)

    # Run Program 2 and capture output
    OUTPUT2=$($PROGRAM2 "$ARGUMENT")
    FPS2=$(echo "$OUTPUT2" | grep -oE '[0-9]+\.[0-9]+')  # Extract FPS
    echo "$PROGRAM2 -> FPS: $FPS2"
    TOTAL_FPS2=$(echo "$TOTAL_FPS2 + $FPS2" | bc)

    echo ""
done

# Calculate average FPS
AVG_FPS1=$(echo "scale=2; $TOTAL_FPS1 / $RUNS" | bc)
AVG_FPS2=$(echo "scale=2; $TOTAL_FPS2 / $RUNS" | bc)

echo "Final Results:"
echo "$PROGRAM1 -> Average FPS: $AVG_FPS1"
echo "$PROGRAM2 -> Average FPS: $AVG_FPS2"

# Determine which program is faster and calculate difference
if (( $(echo "$AVG_FPS1 > $AVG_FPS2" | bc -l) )); then
    FASTER_PROGRAM=$PROGRAM1
    SLOWER_PROGRAM=$PROGRAM2
    FPS_DIFF=$(echo "$AVG_FPS1 - $AVG_FPS2" | bc)
    PERCENT_DIFF=$(echo "scale=2; ($FPS_DIFF / $AVG_FPS2) * 100" | bc)
elif (( $(echo "$AVG_FPS2 > $AVG_FPS1" | bc -l) )); then
    FASTER_PROGRAM=$PROGRAM2
    SLOWER_PROGRAM=$PROGRAM1
    FPS_DIFF=$(echo "$AVG_FPS2 - $AVG_FPS1" | bc)
    PERCENT_DIFF=$(echo "scale=2; ($FPS_DIFF / $AVG_FPS1) * 100" | bc)
else
    echo "Both programs have the same average FPS."
    exit 0
fi

echo ""
echo "🏆 $FASTER_PROGRAM is faster than $SLOWER_PROGRAM by:"
echo "   📈 $FPS_DIFF FPS"
echo "   📊 $PERCENT_DIFF% faster"
