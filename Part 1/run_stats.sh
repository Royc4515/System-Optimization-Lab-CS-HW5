#!/bin/bash

# run_stats.sh - Compare original vs optimized vowel counting

# 1. Check if the user provided the mode (optional)
if [ "$#" -gt 1 ]; then
    echo "Usage: ./run_stats.sh [mode]"
    echo "  mode: 'optimized' (run optimized only) or 'both' (default: both)"
    echo "  Always runs on input.txt"
    exit 1
fi

INPUT="input.txt"
MODE=${1:-both}  # Default to 'both' if not specified

# Validate mode
if [ "$MODE" != "optimized" ] && [ "$MODE" != "both" ]; then
    echo "Error: mode must be 'optimized' or 'both'"
    exit 1
fi

# 2. Define temp file for output
OUT_FILE="temp_program_output.txt"

# Run original version only if mode is 'both'
if [ "$MODE" = "both" ]; then
    echo "Compiling with vowel_counting_original.c..."

    # 3. Compile original version
    gcc -O0 main.c vowel_counting_original.c -o original.out

    # 4. Run with nanosecond precision timing
    START_ORIG=$(date +%s%N)
    ./original.out < "$INPUT" > "$OUT_FILE"
    END_ORIG=$(date +%s%N)

    # 5. Save the program's output
    OUTPUT_ORIGINAL=$(cat "$OUT_FILE")

    # 6. Calculate elapsed time in microseconds and seconds
    ELAPSED_NS_ORIG=$((END_ORIG - START_ORIG))
    ELAPSED_US_ORIG=$((ELAPSED_NS_ORIG / 1000))
    TOTAL_ORIG=$(echo "scale=6; $ELAPSED_NS_ORIG / 1000000000" | bc -l)

    # 7. Cleanup temp file
    rm "$OUT_FILE"
fi

echo "Compiling with vowel_counting.c..."

# 8. Compile optimized version
gcc -O0 main.c vowel_counting.c -o optimized.out

# 9. Run with nanosecond precision timing
START_OPT=$(date +%s%N)
./optimized.out < "$INPUT" > "$OUT_FILE"
END_OPT=$(date +%s%N)

# 10. Save the program's output
OUTPUT_OPTIMIZED=$(cat "$OUT_FILE")

# 11. Calculate elapsed time in microseconds and seconds
ELAPSED_NS_OPT=$((END_OPT - START_OPT))
ELAPSED_US_OPT=$((ELAPSED_NS_OPT / 1000))
TOTAL_OPT=$(echo "scale=6; $ELAPSED_NS_OPT / 1000000000" | bc -l)

# 12. Cleanup temp file
rm "$OUT_FILE"

# Helper function to format output nicely
format_output() {
    local output="$1"
    local title="$2"
    
    echo "$title"
    echo "=============================="
    
    # Extract longest pi match
    if [[ $output =~ Longest\ pi\ digit\ match\ found:\ ([0-9]+) ]]; then
        echo "Longest Pi Match: ${BASH_REMATCH[1]} characters"
    fi
    
    # Extract Hamming match info
    echo ""
    echo "Best Hamming Match to Pi (100 digits):"
    echo "---------------------------------------"
    if [[ $output =~ Best\ index:\ ([0-9-]+) ]]; then
        echo "  Best index: ${BASH_REMATCH[1]}"
    fi
    if [[ $output =~ Hamming\ score:\ ([0-9]+)/100 ]]; then
        echo "  Hamming score: ${BASH_REMATCH[1]}/100 matches"
    fi
    # Extract the character-by-character comparison lines using grep/echo
    # These lines are multi-line so we need to extract them differently
    echo "  Character comparison:"
    echo "$output" | grep -E "^Pi: " | head -1
    echo "$output" | grep -E "^Buf:" | head -1
    # Get the match indicator line (starts with spaces and has ^ chars)
    echo "$output" | grep -E "^     [^ ]" | head -1
    
    # Extract cache-unfriendly analysis
    echo ""
    echo "Cache-Unfriendly Analysis (stride=1000):"
    echo "-----------------------------------------"
    if [[ $output =~ Positions\ checked:\ ([0-9]+) ]]; then
        echo "  Positions checked: ${BASH_REMATCH[1]}"
    fi
    if [[ $output =~ Count\ of\ \'3\'\ at\ addresses\ divisible\ by\ 1000:\ ([0-9]+) ]]; then
        echo "  Count of '3' at sparse addresses: ${BASH_REMATCH[1]}"
    fi
    if [[ $output =~ Vowels\ at\ sparse\ addresses:\ ([0-9]+) ]]; then
        echo "  Vowels at sparse addresses: ${BASH_REMATCH[1]}"
    fi
    if [[ $output =~ Digits\ at\ sparse\ addresses:\ ([0-9]+) ]]; then
        echo "  Digits at sparse addresses: ${BASH_REMATCH[1]}"
    fi
    
    # Extract vowel count
    echo ""
    if [[ $output =~ Vowel\ count:\ ([0-9]+) ]]; then
        echo "Vowel Count: ${BASH_REMATCH[1]}"
    fi
    
    echo ""
    echo "Letters:"
    echo "--------"
    # Extract and format letters - keep tuples on one line
    if [[ $output =~ Letters:\ \[([^\]]+)\] ]]; then
        letters_part="${BASH_REMATCH[1]}"
        echo "  [$letters_part]"
    fi
    
    echo ""
    echo "Digits:"
    echo "-------"
    # Extract and format digits - keep tuples on one line
    if [[ $output =~ Digits:\ \[([^\]]+)\] ]]; then
        digits_part="${BASH_REMATCH[1]}"
        echo "  [$digits_part]"
    fi
    
    echo ""
}

# 13. Display results
echo ""

if [ "$MODE" = "both" ]; then
    # Display detailed results for both versions
    format_output "$OUTPUT_ORIGINAL" "ORIGINAL RESULTS"
    echo ""
    format_output "$OUTPUT_OPTIMIZED" "OPTIMIZED RESULTS"
    echo ""
    
    # Summary comparison table
    echo "PERFORMANCE SUMMARY"
    echo "==================="
    WIDTH=40
    printf "%-${WIDTH}s | %-${WIDTH}s\n" "ORIGINAL" "OPTIMIZED"
    echo "---------------------------------------------------------------------------------"
    printf "%-${WIDTH}s | %-${WIDTH}s\n" "Time: ${TOTAL_ORIG}s" "Time: ${TOTAL_OPT}s"
    echo ""

    # 14. Compare outputs
    echo "COMPARISON:"
    if [[ "$OUTPUT_ORIGINAL" == "$OUTPUT_OPTIMIZED" ]]; then
        echo "✓ Outputs match - Same counts"
    else
        echo "✗ Outputs differ - Different counts!"
        echo "  Original:  $OUTPUT_ORIGINAL"
        echo "  Optimized: $OUTPUT_OPTIMIZED"
    fi

    # Calculate speedup
    SPEEDUP=$(echo "scale=2; $TOTAL_ORIG / $TOTAL_OPT" | bc -l)
    echo "Speedup: ${SPEEDUP}x"
else
    # Display optimized results only
    format_output "$OUTPUT_OPTIMIZED" "OPTIMIZED RESULTS"
    echo ""
    echo "PERFORMANCE:"
    echo "============"
    echo "Total Time: ${TOTAL_OPT}s"
fi

# 15. Cleanup executables
rm -f original.out optimized.out


cd "/Users/mayerunterberg/Documents/Tirgul CA/hw5/vowel_count" && python3 create-buffer.py 1000000 > input_1mb.txt && ./run_stats.sh input_1mb.txt