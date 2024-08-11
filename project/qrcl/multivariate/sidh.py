# multivariate/sidh.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class SIDH:
    def __init__(self, n: int, e: int, d: int):
        self.n = n
        self.e = e
        self.d = d

    def keygen(self) -> Tuple[np.array, np.array]:
        A = self._generate_secret_key()
        B = self._generate_public_key(A)
        return (A, B)

    def encrypt(self, m: np.array, B: np.array) -> np.array:
        c = self._encrypt(m, B)
        return c

    def decrypt(self, c: np.array, A: np.array) -> np.array:
        m = self._decrypt(c, A)
        return m

    def _generate_secret_key(self) -> np.array:
        # Generate a random secret key A of size e x n
        A = np.random.randint(0, 2, size=(self.e, self.n))
        return A

    def _generate_public_key(self, A: np.array) -> np.array:
        # Generate a public key B of size d x n
        B = np.random.randint(0, 2, size=(self.d, self.n))
        return B

    def _encrypt(self, m: np.array, B: np.array) -> np.array:
        # Encrypt the message m using the public key B
        c = np.dot(m, B) % 2
        # Add random errors to the ciphertext
        e = np.random.randint(0, 2, size=self.n)
        c += e
        return c

    def _decrypt(self, c: np.array, A: np.array) -> np.array:
        # Decrypt the ciphertext c using the secret key A
        # Use the LU decomposition to solve the system of linear equations
        lu, piv = lu_factor(A)
        x = lu_solve((lu, piv), c)
        m = x[:self.e]
        return m
