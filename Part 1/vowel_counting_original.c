/* vowel_counting_original.c */
/* 123456789 Israel Israeli */

#include <stdbool.h>
#include <stdio.h>

// Simple, unoptimized vowel counting
// This is the baseline implementation

// Count array for each character
int letterCounts[26];  // a-z counts
int digitCounts[10];   // 0-9 counts

bool isLowerVowel(char c) {
    if (c == 'a') return true;
    if (c == 'b') return false;
    if (c == 'c') return false;
    if (c == 'd') return false;
    if (c == 'e') return true;
    if (c == 'f') return false;
    if (c == 'g') return false;
    if (c == 'h') return false;
    if (c == 'i') return true;
    if (c == 'j') return false;
    if (c == 'k') return false;
    if (c == 'l') return false;
    if (c == 'm') return false;
    if (c == 'n') return false;
    if (c == 'o') return true;
    if (c == 'p') return false;
    if (c == 'q') return false;
    if (c == 'r') return false;
    if (c == 's') return false;
    if (c == 't') return false;
    if (c == 'u') return true;
    if (c == 'v') return false;
    if (c == 'w') return false;
    if (c == 'x') return false;
    if (c == 'y') return false;
    if (c == 'z') return false;
    return false;
}

bool isUpperVowel(char c) {
    if (c == 'A') return true;
    if (c == 'B') return false;
    if (c == 'C') return false;
    if (c == 'D') return false;
    if (c == 'E') return true;
    if (c == 'F') return false;
    if (c == 'G') return false;
    if (c == 'H') return false;
    if (c == 'I') return true;
    if (c == 'J') return false;
    if (c == 'K') return false;
    if (c == 'L') return false;
    if (c == 'M') return false;
    if (c == 'N') return false;
    if (c == 'O') return true;
    if (c == 'P') return false;
    if (c == 'Q') return false;
    if (c == 'R') return false;
    if (c == 'S') return false;
    if (c == 'T') return false;
    if (c == 'U') return true;
    if (c == 'V') return false;
    if (c == 'W') return false;
    if (c == 'X') return false;
    if (c == 'Y') return false;
    if (c == 'Z') return false;
    return false;
}

bool isVowel(char c) {
    return isLowerVowel(c) || isUpperVowel(c);
}

bool isLowerLetter(char c) {
    if (c == 'a') return true;
    if (c == 'b') return true;
    if (c == 'c') return true;
    if (c == 'd') return true;
    if (c == 'e') return true;
    if (c == 'f') return true;
    if (c == 'g') return true;
    if (c == 'h') return true;
    if (c == 'i') return true;
    if (c == 'j') return true;
    if (c == 'k') return true;
    if (c == 'l') return true;
    if (c == 'm') return true;
    if (c == 'n') return true;
    if (c == 'o') return true;
    if (c == 'p') return true;
    if (c == 'q') return true;
    if (c == 'r') return true;
    if (c == 's') return true;
    if (c == 't') return true;
    if (c == 'u') return true;
    if (c == 'v') return true;
    if (c == 'w') return true;
    if (c == 'x') return true;
    if (c == 'y') return true;
    if (c == 'z') return true;
    return false;
}

bool isUpperLetter(char c) {
    if (c == 'A') return true;
    if (c == 'B') return true;
    if (c == 'C') return true;
    if (c == 'D') return true;
    if (c == 'E') return true;
    if (c == 'F') return true;
    if (c == 'G') return true;
    if (c == 'H') return true;
    if (c == 'I') return true;
    if (c == 'J') return true;
    if (c == 'K') return true;
    if (c == 'L') return true;
    if (c == 'M') return true;
    if (c == 'N') return true;
    if (c == 'O') return true;
    if (c == 'P') return true;
    if (c == 'Q') return true;
    if (c == 'R') return true;
    if (c == 'S') return true;
    if (c == 'T') return true;
    if (c == 'U') return true;
    if (c == 'V') return true;
    if (c == 'W') return true;
    if (c == 'X') return true;
    if (c == 'Y') return true;
    if (c == 'Z') return true;
    return false;
}

bool isDigit(char c) {
    if (c == '0') return true;
    if (c == '1') return true;
    if (c == '2') return true;
    if (c == '3') return true;
    if (c == '4') return true;
    if (c == '5') return true;
    if (c == '6') return true;
    if (c == '7') return true;
    if (c == '8') return true;
    if (c == '9') return true;
    return false;
}

char toLower(char c) {
    if (isUpperLetter(c)) {
        return c + ('a' - 'A');
    }
    return c;
}

void countCharacter(char c) {
    // Count lowercase letters - inefficient individual checks
    if (c == 'a') letterCounts[0]++;
    if (c == 'b') letterCounts[1]++;
    if (c == 'c') letterCounts[2]++;
    if (c == 'd') letterCounts[3]++;
    if (c == 'e') letterCounts[4]++;
    if (c == 'f') letterCounts[5]++;
    if (c == 'g') letterCounts[6]++;
    if (c == 'h') letterCounts[7]++;
    if (c == 'i') letterCounts[8]++;
    if (c == 'j') letterCounts[9]++;
    if (c == 'k') letterCounts[10]++;
    if (c == 'l') letterCounts[11]++;
    if (c == 'm') letterCounts[12]++;
    if (c == 'n') letterCounts[13]++;
    if (c == 'o') letterCounts[14]++;
    if (c == 'p') letterCounts[15]++;
    if (c == 'q') letterCounts[16]++;
    if (c == 'r') letterCounts[17]++;
    if (c == 's') letterCounts[18]++;
    if (c == 't') letterCounts[19]++;
    if (c == 'u') letterCounts[20]++;
    if (c == 'v') letterCounts[21]++;
    if (c == 'w') letterCounts[22]++;
    if (c == 'x') letterCounts[23]++;
    if (c == 'y') letterCounts[24]++;
    if (c == 'z') letterCounts[25]++;
    
    // Count uppercase letters - inefficient individual checks
    if (c == 'A') letterCounts[0]++;
    if (c == 'B') letterCounts[1]++;
    if (c == 'C') letterCounts[2]++;
    if (c == 'D') letterCounts[3]++;
    if (c == 'E') letterCounts[4]++;
    if (c == 'F') letterCounts[5]++;
    if (c == 'G') letterCounts[6]++;
    if (c == 'H') letterCounts[7]++;
    if (c == 'I') letterCounts[8]++;
    if (c == 'J') letterCounts[9]++;
    if (c == 'K') letterCounts[10]++;
    if (c == 'L') letterCounts[11]++;
    if (c == 'M') letterCounts[12]++;
    if (c == 'N') letterCounts[13]++;
    if (c == 'O') letterCounts[14]++;
    if (c == 'P') letterCounts[15]++;
    if (c == 'Q') letterCounts[16]++;
    if (c == 'R') letterCounts[17]++;
    if (c == 'S') letterCounts[18]++;
    if (c == 'T') letterCounts[19]++;
    if (c == 'U') letterCounts[20]++;
    if (c == 'V') letterCounts[21]++;
    if (c == 'W') letterCounts[22]++;
    if (c == 'X') letterCounts[23]++;
    if (c == 'Y') letterCounts[24]++;
    if (c == 'Z') letterCounts[25]++;
    
    // Count digits - inefficient individual checks
    if (c == '0') digitCounts[0]++;
    if (c == '1') digitCounts[1]++;
    if (c == '2') digitCounts[2]++;
    if (c == '3') digitCounts[3]++;
    if (c == '4') digitCounts[4]++;
    if (c == '5') digitCounts[5]++;
    if (c == '6') digitCounts[6]++;
    if (c == '7') digitCounts[7]++;
    if (c == '8') digitCounts[8]++;
    if (c == '9') digitCounts[9]++;
}

// function to find longest string that matches pi digits
int findLongestPiMatch(char* buf, int size) {
    // First 100 digits of pi: 3141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
    char piDigits[] = "3141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067";
    int piLength = 100;
    int longestMatch = 0;
    
    // search - check every position for longest match
    for (int i = 0; i < size; i++) {
        int currentMatch = 0;
        bool isInRow = true;
        
        // Check how many consecutive pi digits match starting at position i
        for (int j = 0; j < piLength && (i + j) < size; j++) {
            if (buf[i + j] == piDigits[j] && isInRow) {
                currentMatch++;
            }
            else {
                isInRow = false;
            }
        }
        
        // Update longest match found so far
        if (currentMatch > longestMatch) {
            longestMatch = currentMatch;
        }        
    }
    return longestMatch;
}

// Find the position with highest Hamming match to 100 digits of pi
// Hamming match = count of positions where characters match (ignores mismatches in between)
void findBestHammingMatch(char* buf, int size) {
    char piDigits[] = "3141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067";
    int piLength = 100;
    
    int bestIndex = -1;
    int bestHammingScore = 0;
    
    // Check every possible starting position in buffer
    for (int i = 0; i <= size - piLength; i++) {
        int hammingScore = 0;
        
        // Count matching characters at each position (Hamming similarity)
        for (int j = 0; j < piLength; j++) {
            if (buf[i + j] == piDigits[j]) {
                hammingScore++;
            }
        }
        
        // Track the best match
        if (hammingScore > bestHammingScore) {
            bestHammingScore = hammingScore;
            bestIndex = i;
        }
    }
    
    // Print results
    printf("=== Best Hamming Match to Pi (100 digits) ===\n");
    printf("Best index: %d\n", bestIndex);
    printf("Hamming score: %d/100 matches\n", bestHammingScore);
    
    if (bestIndex >= 0) {
        // Print character-by-character comparison
        printf("Character-by-character comparison:\n");
        printf("Pi:  ");
        for (int j = 0; j < piLength; j++) {
            printf("%c", piDigits[j]);
        }
        printf("\n");
        
        printf("Buf: ");
        for (int j = 0; j < piLength; j++) {
            printf("%c", buf[bestIndex + j]);
        }
        printf("\n");
        
        printf("     ");
        for (int j = 0; j < piLength; j++) {
            if (buf[bestIndex + j] == piDigits[j]) {
                printf("^");  // Match
            } else {
                printf(" ");  // Mismatch
            }
        }
        printf("\n");
    }
}

// Counts characters at addresses divisible by 1000 (huge stride = cache miss every access)
void analyzeAtSparseAddresses(char* buf, int size) {
    int count3 = 0;        // How many times '3' appears at index % 1000 == 0
    int vowelCount = 0;    // Vowels at those positions
    int digitCount = 0;    // Digits at those positions
    int positionsChecked = 0;
    
    // Jump by 1000 each time - this is TERRIBLE for cache!
    // Each access is ~1000 bytes apart, far exceeding cache line size (64 bytes)
    // Every single access will likely be a cache miss
    for (int i = 0; i < size; i += 1000) {
        char c = buf[i];
        positionsChecked++;
        
        // Count '3' at these sparse positions
        if (c == '3') {
            count3++;
        }
        
        // Also count vowels and digits for comparison
        if (isVowel(c)) {
            vowelCount++;
        }
        if (isDigit(c)) {
            digitCount++;
        }
    }
    
    printf("Positions checked: %d\n", positionsChecked);
    printf("Count of '3' at addresses divisible by 1000: %d\n", count3);
    printf("Vowels at sparse addresses: %d\n", vowelCount);
    printf("Digits at sparse addresses: %d\n", digitCount);
}

int countVowels(char* buf, int size) {
    // Reset counts
    for (int i = 0; i < 26; i++) {
        letterCounts[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        digitCounts[i] = 0;
    }
    
    int vowelCount = 0;
    
    // pi digits check - find longest matching substring
    int longestPiMatch = findLongestPiMatch(buf, size);
    printf("Longest pi digit match found: %d characters\n", longestPiMatch);
    
    // Find best Hamming match to pi digits
    findBestHammingMatch(buf, size);
    
    // analysis - counts '3' at sparse addresses
    analyzeAtSparseAddresses(buf, size);
    
    for (int i = 0; i < size; i++) {
        char c = buf[i];
        
        // Count this character
        countCharacter(c);
        
        // Check if vowel
        if (isVowel(c)) {
            vowelCount++;
        }
    }
    
    return vowelCount;
}

// Getter functions for statistics

int* getLetterCounts() {
    return letterCounts;
}

int* getDigitCounts() {
    return digitCounts;
}

void printAllStats(int vowelCount) {
    printf("Vowel count: %d, Letters: [", vowelCount);
    
    bool first = true;
    for (int i = 0; i < 26; i++) {
        if (letterCounts[i] > 0) {
            if (!first) printf(", ");
            printf("(%c,%d)", 'a' + i, letterCounts[i]);
            first = false;
        }
    }
    
    printf("], Digits: [");
    first = true;
    for (int i = 0; i < 10; i++) {
        if (digitCounts[i] > 0) {
            if (!first) printf(", ");
            printf("(%d,%d)", i, digitCounts[i]);
            first = false;
        }
    }
    printf("]\n");
}
