# qrcl/algorithms/lattice/ntru.py

import numpy as np
from typing import Tuple

class NTRU:
    def __init__(self, n: int, q: int, d: int, sigma: float):
        self.n = n
        self.q = q
        self.d = d
        self.sigma = sigma
        self.poly_modulus = np.poly1d([1] + [0]*(n-1) + [-1])

    def keygen(self) -> Tuple[np.poly1d, np.poly1d]:
        f = self._sample_poly(self.d, self.q)
        g = self._sample_poly(self.d, self.q)
        F_q = self._mod(f, self.q)
        F_p = self._mod(f, 3)
        h = self._mod(g * F_q, self.q)
        return (f, h)

    def encrypt(self, m: np.poly1d, h: np.poly1d) -> np.poly1d:
        r = self._sample_poly(self.d, self.q)
        e = self._mod(r * h + m, self.q)
        return e

    def decrypt(self, e: np.poly1d, f: np.poly1d) -> np.poly1d:
        a = self._mod(e * f, self.q)
        m = self._mod(a, 3)
        return m

    def _sample_poly(self, d: int, q: int) -> np.poly1d:
        coeffs = np.random.randint(-d, d+1, size=self.n)
        return np.poly1d(coeffs)

    def _mod(self, poly: np.poly1d, q: int) -> np.poly1d:
        return poly % self.poly_modulus % q

    def _instantiate(self, n: int, q: int, d: int, sigma: float) -> None:
        self.n = n
        self.q = q
        self.d = d
        self.sigma = sigma
        self.poly_modulus = np.poly1d([1] + [0]*(n-1) + [-1])

    def __str__(self) -> str:
        return f"NTRU(n={self.n}, q={self.q}, d={self.d}, sigma={self.sigma})"
