# create-buffer.py
# 123456789 Israel Israeli

import secrets
import sys

def generate_buffer(n=5000000):
    """
    Generate a truly random buffer of n characters using cryptographic randomness.
    Uses secrets module (backed by OS entropy) for true randomness.
    """
    vowels = 'aeiouAEIOU'
    consonants = 'bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ'
    digits = '0123456789'
    
    # Build character pool based on ratios
    all_chars = (vowels +        # vowels
                 consonants +    # consonants
                 digits * 100     # digits (weighted more)
                )
    
    # Pre-compute for efficiency
    pool_size = len(all_chars)
    
    print(n)
    
    # Generate in chunks for efficiency with true randomness
    chunk_size = 65536  # 64KB chunks - optimal for OS random reads
    remaining = n
    
    while remaining > 0:
        size = min(chunk_size, remaining)
        # Get cryptographically random bytes
        random_bytes = secrets.token_bytes(size)
        # Map each byte to a character in our pool using modulo
        chunk = ''.join(all_chars[b % pool_size] for b in random_bytes)
        sys.stdout.write(chunk)
        sys.stdout.flush()
        remaining -= size


if __name__ == "__main__":
    n = 10000000
    generate_buffer(n)
