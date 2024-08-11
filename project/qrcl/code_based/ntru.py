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

    def decrypt(self, c: np.array, f: np.array) -> np
