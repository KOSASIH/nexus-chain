# code_based/ntru.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class NTRU:
    def __init__(self, n: int, p: int, q: int):
        self.n = n
        self.p = p
        self.q = q

    def keygen(self) -> Tuple[np.array, np.array]:
        f = self._generate_secret_key()
        h = self._generate_public_key(f)
        return (f, h)

    def encrypt(self, m: np.array, h: np.array) -> np.array:
        c = self._encrypt(m, h)
        return c

    def decrypt(self, c: np.array, f: np.array) -> np.array:
        m = self._decrypt(c, f)
        return m

    def _generate_secret_key(self) -> np.array:
        # Generate a random secret key f of size n
        f = np.random.randint(0, self.p, size=self.n)
        return f

    def _generate_public_key(self, f: np.array) -> np.array:
        # Generate a public key h of size n
        h = np.random.randint(0, self.q, size=self.n)
        return h

    def _encrypt(self, m: np.array, h: np.array) -> np.array:
        # Encrypt the message m using the public key h
        c = np.convolve(m, h) % self.q
        # Add random errors to the ciphertext
        e = np.random.randint(0, self.q, size=self.n)
        c += e
        return c

    def _decrypt(self, c: np.array, f: np.array) -> np.array:
        # Decrypt the ciphertext c using the secret key f
        # Use the convolution theorem to recover the message
        m = np.convolve(c, f) % self.p
        return m
