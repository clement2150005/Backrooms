#!/bin/bash

OUTPUT_FILE="prototypes.h"

# Clear the output file
> "$OUTPUT_FILE"

# Loop through all .c files, sorted by directory
for file in $(find . -type f -name "*.c" | sort); do
	# Get the directory name in uppercase
	DIR_NAME=$(dirname "$file" | tr '[:lower:]' '[:upper:]')
	BASE_NAME=$(basename "$file")

	# Print the directory name if it's the first occurrence
	if [[ "$LAST_DIR" != "$DIR_NAME" ]]; then
		echo "" >> "$OUTPUT_FILE"
		echo "/* $DIR_NAME */" >> "$OUTPUT_FILE"
		echo "" >> "$OUTPUT_FILE"
		LAST_DIR="$DIR_NAME"
	fi

	# Print the file name
	echo "// $BASE_NAME" >> "$OUTPUT_FILE"

	# Use awk to extract non-static function prototypes and add a semicolon
	awk '
		/^[a-zA-Z_].*\)[ \t]*$/ && !/^static/ {
			sub(/[ \t]*{[ \t]*$/, "", $0);
			print $0 ";"
		}
	' "$file" >> "$OUTPUT_FILE"

	echo "" >> "$OUTPUT_FILE"
done

echo "Prototypes extracted to $OUTPUT_FILE"
