/* vowel_counting.c */
/* 123456789 Israel Israeli */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h> // for fork()
#include <sys/wait.h> // for wait()
#include <stdlib.h> // for exit()
#include <string.h> // for memchr, memset

// ==========================================
// DATA & LUT SETUP
// ==========================================
unsigned char charProps[256] = {0}; 
bool tableInitialized = false;

// Global Histogram
int globalCounts[256];

// Legacy counters
int letterCounts[26];  
int digitCounts[10];   

// Flags  
#define FLAG_DIGIT  4   
#define FLAG_VOWEL  8 

void initCharTable() {
    if (tableInitialized) return;
    // Unrolled digit initialization
    charProps['0'] = FLAG_DIGIT; charProps['1'] = FLAG_DIGIT;
    charProps['2'] = FLAG_DIGIT; charProps['3'] = FLAG_DIGIT;
    charProps['4'] = FLAG_DIGIT; charProps['5'] = FLAG_DIGIT;
    charProps['6'] = FLAG_DIGIT; charProps['7'] = FLAG_DIGIT;
    charProps['8'] = FLAG_DIGIT; charProps['9'] = FLAG_DIGIT;
    
    // Unrolled vowel initialization
    charProps['a'] = FLAG_VOWEL; charProps['e'] = FLAG_VOWEL;
    charProps['i'] = FLAG_VOWEL; charProps['o'] = FLAG_VOWEL;
    charProps['u'] = FLAG_VOWEL; charProps['A'] = FLAG_VOWEL;
    charProps['E'] = FLAG_VOWEL; charProps['I'] = FLAG_VOWEL;
    charProps['O'] = FLAG_VOWEL; charProps['U'] = FLAG_VOWEL;
    
    tableInitialized = true;
}

// ==========================================
// HEAVY ANALYSIS (Child Process)
// ==========================================

int findLongestPiMatch(char* buf, int size) {
    static const char piDigits[] = "3141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067";
    register int longestMatch = 0;
    register char* ptr = buf;
    char* endPtr = buf + size - 100; // Subtract piLength directly
    
    while(ptr < endPtr){
        ptr = (char*)memchr(ptr, '3', endPtr - ptr + 100);
        if (ptr == NULL) break;
        if (ptr > endPtr) break; // Guard against overflow

        register int currentMatch = 0;
        register char* scanBuf = ptr;
        register const char* scanPi = piDigits;

        // Unrolled comparison loop (10x unroll for 100 digits)
        while (scanPi < piDigits + 100) {
            if (*scanBuf++ != *scanPi++) break;
            currentMatch++;
            if (*scanBuf++ != *scanPi++) break;
            currentMatch++;
            if (*scanBuf++ != *scanPi++) break;
            currentMatch++;
            if (*scanBuf++ != *scanPi++) break;
            currentMatch++;
            if (*scanBuf++ != *scanPi++) break;
            currentMatch++;
        }
        
        if(currentMatch > longestMatch) longestMatch = currentMatch;
        ptr++; 
    }
    return longestMatch;
}
void findBestHammingMatch(char* buf, int size) {
    static const char piDigits[] = "3141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067";
    int piLength = 100;
    int bestIndex = -1;
    int bestHammingScore = 0;

    char* p = buf;
    char* endPtr = buf + size - piLength;
    int i = 0;

    // Iterate through each possible starting position
    for (; p <= endPtr; p++, i++) {
        int s = 0;

        // --- BLOCK 1: 0-19 (Manual unroll in groups of 4) ---
        s += (p[0] == piDigits[0]) + (p[1] == piDigits[1]) + (p[2] == piDigits[2]) + (p[3] == piDigits[3]) + (p[4] == piDigits[4]);
        s += (p[5] == piDigits[5]) + (p[6] == piDigits[6]) + (p[7] == piDigits[7]) + (p[8] == piDigits[8]) + (p[9] == piDigits[9]);
        s += (p[10] == piDigits[10]) + (p[11] == piDigits[11]) + (p[12] == piDigits[12]) + (p[13] == piDigits[13]) + (p[14] == piDigits[14]);
        s += (p[15] == piDigits[15]) + (p[16] == piDigits[16]) + (p[17] == piDigits[17]) + (p[18] == piDigits[18]) + (p[19] == piDigits[19]);

        // ORIGINAL PRUNING LOGIC (Must be kept for output compatibility)
        if (s + 80 <= bestHammingScore) continue;

        // --- BLOCK 2: 20-39 ---
        s += (p[20] == piDigits[20]) + (p[21] == piDigits[21]) + (p[22] == piDigits[22]) + (p[23] == piDigits[23]) + (p[24] == piDigits[24]);
        s += (p[25] == piDigits[25]) + (p[26] == piDigits[26]) + (p[27] == piDigits[27]) + (p[28] == piDigits[28]) + (p[29] == piDigits[29]);
        s += (p[30] == piDigits[30]) + (p[31] == piDigits[31]) + (p[32] == piDigits[32]) + (p[33] == piDigits[33]) + (p[34] == piDigits[34]);
        s += (p[35] == piDigits[35]) + (p[36] == piDigits[36]) + (p[37] == piDigits[37]) + (p[38] == piDigits[38]) + (p[39] == piDigits[39]);
        
        if (s + 60 <= bestHammingScore) continue;

        // --- BLOCK 3: 40-59 ---
        s += (p[40] == piDigits[40]) + (p[41] == piDigits[41]) + (p[42] == piDigits[42]) + (p[43] == piDigits[43]) + (p[44] == piDigits[44]);
        s += (p[45] == piDigits[45]) + (p[46] == piDigits[46]) + (p[47] == piDigits[47]) + (p[48] == piDigits[48]) + (p[49] == piDigits[49]);
        s += (p[50] == piDigits[50]) + (p[51] == piDigits[51]) + (p[52] == piDigits[52]) + (p[53] == piDigits[53]) + (p[54] == piDigits[54]);
        s += (p[55] == piDigits[55]) + (p[56] == piDigits[56]) + (p[57] == piDigits[57]) + (p[58] == piDigits[58]) + (p[59] == piDigits[59]);
        if (s + 40 <= bestHammingScore) continue;

        // --- BLOCK 4: 60-79 ---
        s += (p[60] == piDigits[60]) + (p[61] == piDigits[61]) + (p[62] == piDigits[62]) + (p[63] == piDigits[63]) + (p[64] == piDigits[64]);
        s += (p[65] == piDigits[65]) + (p[66] == piDigits[66]) + (p[67] == piDigits[67]) + (p[68] == piDigits[68]) + (p[69] == piDigits[69]);
        s += (p[70] == piDigits[70]) + (p[71] == piDigits[71]) + (p[72] == piDigits[72]) + (p[73] == piDigits[73]) + (p[74] == piDigits[74]);
        s += (p[75] == piDigits[75]) + (p[76] == piDigits[76]) + (p[77] == piDigits[77]) + (p[78] == piDigits[78]) + (p[79] == piDigits[79]);
        if (s + 20 <= bestHammingScore) continue;

        // --- BLOCK 5: 80-99 ---
        s += (p[80] == piDigits[80]) + (p[81] == piDigits[81]) + (p[82] == piDigits[82]) + (p[83] == piDigits[83]) + (p[84] == piDigits[84]);
        s += (p[85] == piDigits[85]) + (p[86] == piDigits[86]) + (p[87] == piDigits[87]) + (p[88] == piDigits[88]) + (p[89] == piDigits[89]);
        s += (p[90] == piDigits[90]) + (p[91] == piDigits[91]) + (p[92] == piDigits[92]) + (p[93] == piDigits[93]) + (p[94] == piDigits[94]);
        s += (p[95] == piDigits[95]) + (p[96] == piDigits[96]) + (p[97] == piDigits[97]) + (p[98] == piDigits[98]) + (p[99] == piDigits[99]);
        if (s > bestHammingScore) {
            bestHammingScore = s;
            bestIndex = i;
            if (bestHammingScore == 100) break;
        }
    }

    printf("=== Best Hamming Match to Pi (100 digits) ===\n");
    printf("Best index: %d\n", bestIndex);
    printf("Hamming score: %d/100 matches\n", bestHammingScore);

    if (bestIndex >= 0) {
        const char *bestPtr = buf + bestIndex;
        printf("Character-by-character comparison:\n");
        printf("Pi:  ");
        for (int j = 0; j < piLength; j++) printf("%c", piDigits[j]);
        printf("\nBuf: ");
        for (int j = 0; j < piLength; j++) printf("%c", bestPtr[j]);
        printf("\n     ");
        for (int j = 0; j < piLength; j++) {
            printf("%c", (bestPtr[j] == piDigits[j]) ? '^' : ' ');
        }
        printf("\n");
    }
}

void analyzeAtSparseAddresses(char* buf, int size) {
    register int count3 = 0;        
    register int vowelCount = 0;    
    register int digitCount = 0;    
    register int positionsChecked = 0;
    
    register char* ptr = buf;
    char* end = buf + size;
    
    // Calculate directly addresses divisible by 1000
    while (ptr < end) {
        register unsigned char c = (unsigned char)*ptr;
        register unsigned char props = charProps[c]; 
        
        positionsChecked++;
        count3 += (c == '3');
        vowelCount += ((props & FLAG_VOWEL) >> 3);
        digitCount += ((props & FLAG_DIGIT) >> 2);
        
        ptr += 1000; 
    }
    
    printf("Positions checked: %d\n", positionsChecked);
    printf("Count of '3' at addresses divisible by 1000: %d\n", count3);
    printf("Vowels at sparse addresses: %d\n", vowelCount);
    printf("Digits at sparse addresses: %d\n", digitCount);
}

// ==========================================
// CORE OPTIMIZATION: Main Entry + Fork
// ==========================================

int countVowels(char* buf, int size) {
    initCharTable();
    
    // Clear Histogram
    memset(globalCounts, 0, 256 * sizeof(int));
    
    // PARALLELISM: Fork to handle Pi logic on a separate CPU core
    pid_t pid = fork();
    if (pid == 0) {
        // Child Process: Do heavy lifting
        int longestPiMatch = findLongestPiMatch(buf, size);
        printf("Longest pi digit match found: %d characters\n", longestPiMatch);
        findBestHammingMatch(buf, size);
        analyzeAtSparseAddresses(buf, size);
        exit(0); 
    }

    // Parent Process: Count vowels (CPU Bound)
    int vowelCount = 0;
    register char* ptr = buf;
    register char* endPtr = buf + size;

// 16x Unrolled Loop
while (ptr <= endPtr - 16) {
    register unsigned char c0  = ptr[0],  c1  = ptr[1],  c2  = ptr[2],  c3  = ptr[3];
    register unsigned char c4  = ptr[4],  c5  = ptr[5],  c6  = ptr[6],  c7  = ptr[7];
    register unsigned char c8  = ptr[8],  c9  = ptr[9],  c10 = ptr[10], c11 = ptr[11];
    register unsigned char c12 = ptr[12], c13 = ptr[13], c14 = ptr[14], c15 = ptr[15];
    
    globalCounts[c0]++; globalCounts[c1]++; globalCounts[c2]++; globalCounts[c3]++;
    globalCounts[c4]++; globalCounts[c5]++; globalCounts[c6]++; globalCounts[c7]++;
    globalCounts[c8]++; globalCounts[c9]++; globalCounts[c10]++; globalCounts[c11]++;
    globalCounts[c12]++; globalCounts[c13]++; globalCounts[c14]++; globalCounts[c15]++;
    
    vowelCount += ((charProps[c0] & FLAG_VOWEL) >> 3) + ((charProps[c1] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c2] & FLAG_VOWEL) >> 3) + ((charProps[c3] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c4] & FLAG_VOWEL) >> 3) + ((charProps[c5] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c6] & FLAG_VOWEL) >> 3) + ((charProps[c7] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c8] & FLAG_VOWEL) >> 3) + ((charProps[c9] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c10] & FLAG_VOWEL) >> 3) + ((charProps[c11] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c12] & FLAG_VOWEL) >> 3) + ((charProps[c13] & FLAG_VOWEL) >> 3);
    vowelCount += ((charProps[c14] & FLAG_VOWEL) >> 3) + ((charProps[c15] & FLAG_VOWEL) >> 3);
    
    ptr += 16;
}

    // Handle tail
    while (ptr < endPtr) {
        unsigned char c = (unsigned char)(*ptr);
        globalCounts[c]++;
        vowelCount += ((charProps[c] & FLAG_VOWEL) >> 3);
        ptr++;
    }
    
    // Consolidate Results - unrolled
letterCounts[0] = globalCounts['a'] + globalCounts['A'];
letterCounts[1] = globalCounts['b'] + globalCounts['B'];
letterCounts[2] = globalCounts['c'] + globalCounts['C'];
letterCounts[3] = globalCounts['d'] + globalCounts['D'];
letterCounts[4] = globalCounts['e'] + globalCounts['E'];
letterCounts[5] = globalCounts['f'] + globalCounts['F'];
letterCounts[6] = globalCounts['g'] + globalCounts['G'];
letterCounts[7] = globalCounts['h'] + globalCounts['H'];
letterCounts[8] = globalCounts['i'] + globalCounts['I'];
letterCounts[9] = globalCounts['j'] + globalCounts['J'];
letterCounts[10] = globalCounts['k'] + globalCounts['K'];
letterCounts[11] = globalCounts['l'] + globalCounts['L'];
letterCounts[12] = globalCounts['m'] + globalCounts['M'];
letterCounts[13] = globalCounts['n'] + globalCounts['N'];
letterCounts[14] = globalCounts['o'] + globalCounts['O'];
letterCounts[15] = globalCounts['p'] + globalCounts['P'];
letterCounts[16] = globalCounts['q'] + globalCounts['Q'];
letterCounts[17] = globalCounts['r'] + globalCounts['R'];
letterCounts[18] = globalCounts['s'] + globalCounts['S'];
letterCounts[19] = globalCounts['t'] + globalCounts['T'];
letterCounts[20] = globalCounts['u'] + globalCounts['U'];
letterCounts[21] = globalCounts['v'] + globalCounts['V'];
letterCounts[22] = globalCounts['w'] + globalCounts['W'];
letterCounts[23] = globalCounts['x'] + globalCounts['X'];
letterCounts[24] = globalCounts['y'] + globalCounts['Y'];
letterCounts[25] = globalCounts['z'] + globalCounts['Z'];

digitCounts[0] = globalCounts['0'];
digitCounts[1] = globalCounts['1'];
digitCounts[2] = globalCounts['2'];
digitCounts[3] = globalCounts['3'];
digitCounts[4] = globalCounts['4'];
digitCounts[5] = globalCounts['5'];
digitCounts[6] = globalCounts['6'];
digitCounts[7] = globalCounts['7'];
digitCounts[8] = globalCounts['8'];
digitCounts[9] = globalCounts['9'];

    wait(NULL); 
    return vowelCount;
}

// Getters (Required by Main)
int* getLetterCounts() { return letterCounts; }
int* getDigitCounts() { return digitCounts; }

void printAllStats(int vowelCount) {
    printf("Vowel count: %d, Letters: [", vowelCount);
    
    bool first = true;
    for (register int i = 0; i < 26; i++) {
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