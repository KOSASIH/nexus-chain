# key_agreement/frodokem.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class FrodoKEM:
    def __init__(self, n: int, q: int, sigma: float):
        self.n = n  # Dimension of the lattice
        self.q = q  # Modulus
        self.sigma = sigma  # Standard deviation of the error distribution

    def keygen(self) -> Tuple[np.array, np.array]:
        # Generate a random secret key sk of size n
        sk = np.random.randint(0, self.q, size=self.n)

        # Generate a public key pk of size n
        pk = self._generate_public_key(sk)

        return sk, pk

    def encapsulate(self, pk: np.array) -> Tuple[np.array, np.array]:
        # Generate a random error vector e of size n
        e = np.random.normal(0, self.sigma, size=self.n)

        # Compute the ciphertext c = pk * e mod q
        c = np.dot(pk, e) % self.q

        # Compute the shared secret key k = H(c)
        k = self._hash(c)

        return c, k

    def decapsulate(self, sk: np.array, c: np.array) -> np.array:
        # Compute the shared secret key k = H(c) using the secret key sk
        k = self._hash(c)

        return k

    def _generate_public_key(self, sk: np.array) -> np.array:
        # Generate a public key pk of size n
        pk = np.random.randint(0, self.q, size=self.n)
        return pk

    def _hash(self, c: np.array) -> np.array:
        # Compute the hash of the ciphertext c
        h = hashlib.sha256(c.tobytes()).digest()
        return h
