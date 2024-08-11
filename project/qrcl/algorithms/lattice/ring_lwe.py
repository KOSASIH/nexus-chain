# qrcl/algorithms/lattice/ring_lwe.py

import numpy as np
from typing import Tuple

class RingLWE:
    def __init__(self, n: int, q: int, sigma: float):
        self.n = n
        self.q = q
        self.sigma = sigma
        self.poly_modulus = np.poly1d([1] + [0]*(n-1) + [-1])

    def keygen(self) -> Tuple[np.poly1d, np.poly1d]:
        s = self._sample_poly(self.sigma, self.q)
        e = self._sample_poly(self.sigma, self.q)
        a = self._mod(np.poly1d([1]), self.q)
        b = self._mod(a * s + e, self.q)
        return (a, b)

    def encrypt(self, m: np.poly1d, a: np.poly1d, b: np.poly1d) -> np.poly1d:
        e = self._sample_poly(self.sigma, self.q)
        c = self._mod(a * m + e, self.q)
        return c

    def decrypt(self, c: np.poly1d, s: np.poly1d) -> np.poly1d:
        m = self._mod(c - s * a, self.q)
        return m

    def _sample_poly(self, sigma: float, q: int) -> np.poly1d:
        coeffs = np.random.normal(0, sigma, size=self.n)
        return np.poly1d(coeffs)

    def _mod
