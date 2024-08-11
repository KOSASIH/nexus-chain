# multivariate/rainbow_band_sigs.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class RainbowBandSigs:
    def __init__(self, n: int, v: int, o: int):
        self.n = n
        self.v = v
        self.o = o

    def keygen(self) -> Tuple[np.array, np.array]:
        S = self._generate_secret_key()
        P = self._generate_public_key(S)
        return (S, P)

    def sign(self, m: np.array, S: np.array) -> np.array:
        s = self._sign(m, S)
        return s

    def verify(self, m: np.array, s: np.array, P: np.array) -> bool:
        return self._verify(m, s, P)

    def _generate_secret_key(self) -> np.array:
        # Generate a random secret key S of size v x n
        S = np.random.randint(0, 2, size=(self.v, self.n))
        return S

    def _generate_public_key(self, S: np.array) -> np.array:
        # Generate a public key P of size o x n
        P = np.random.randint(0, 2, size=(self.o, self.n))
        return P

    def _sign(self, m: np.array, S: np.array) -> np.array:
        # Sign the message m using the secret key S
        s = np.dot(m, S) % 2
        return s

    def _verify(self, m: np.array, s: np.array, P: np.array) -> bool:
        # Verify the signature s using the public key P
        return np.array_equal(s, np.dot(m, P) % 2)
