# utils/random_number_generator.py

import os
import hashlib
from typing import List

class RandomNumberGenerator:
    def __init__(self, seed: bytes = os.urandom(32), hash_func: str = "sha256"):
        self.seed = seed
        self.hash_func = hash_func

    def generate_random_bytes(self, length: int) -> bytes:
        # Generate a sequence of random bytes using a cryptographically secure hash function
        random_bytes = b""
        while len(random_bytes) < length:
            self.seed = hashlib.new(self.hash_func, self.seed).digest()
            random_bytes += self.seed
        return random_bytes[:length]

    def generate_random_int(self, min_value: int, max_value: int) -> int:
        # Generate a random integer within a specified range
        random_bytes = self.generate_random_bytes(4)
        random_int = int.from_bytes(random_bytes, byteorder="big")
        return min_value + (random_int % (max_value - min_value + 1))

    def generate_random_list(self, length: int, min_value: int, max_value: int) -> List[int]:
        # Generate a list of random integers within a specified range
        return [self.generate_random_int(min_value, max_value) for _ in range(length)]
