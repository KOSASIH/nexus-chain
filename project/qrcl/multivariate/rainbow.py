# multivariate/rainbow.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class Rainbow:
    def __init__(self, n: int, v: int, o: int):
        self.n = n
        self.v = v
        self.o = o

    def keygen(self) -> Tuple[np.array, np.array]:
        S = self._generate_secret_key()
        P = self._generate_public_key(S)
        return (S, P)

    def encrypt(self, m: np.array, P: np.array) -> np.array:
        c = self._encrypt(m, P)
        return c

    def decrypt(self, c: np.array, S: np.array) -> np.array:
        m = self._decrypt(c, S)
        return m

    def _generate_secret_key(self) -> np.array:
        # Generate a random secret key S of size v x n
        S = np.random.randint(0, 2, size=(self.v, self.n))
        return S

    def _generate_public_key(self, S: np.array) -> np.array:
        # Generate a public key P of size o x n
        P = np.random.randint(0, 2, size=(self.o, self.n))
        return P

    def _encrypt(self, m: np.array, P: np.array) -> np.array:
        # Encrypt the message m using the public key P
        c = np.dot(m, P) % 2
        # Add random errors to the ciphertext
        e = np.random.randint(0, 2, size=self.n)
        c += e
        return c

    def _decrypt(self, c: np.array, S: np.array) -> np.array:
        # Decrypt the ciphertext c using the secret key S
        # Use the LU decomposition to solve the system of linear equations
        lu, piv = lu_factor(S)
        x = lu_solve((lu, piv), c)
        m = x[:self.v]
        return m