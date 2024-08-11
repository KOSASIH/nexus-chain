# key_agreement/sidh.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class SIDH:
    def __init__(self, p: int, n: int, e: int):
        self.p = p  # Prime modulus
        self.n = n  # Dimension of the supersingular isogeny graph
        self.e = e  # Exponent of the isogeny

    def keygen(self) -> Tuple[np.array, np.array]:
        # Generate a random secret key sk of size n
        sk = np.random.randint(0, self.p, size=self.n)

        # Generate a public key pk of size n
        pk = self._generate_public_key(sk)

        return sk, pk

    def encapsulate(self, pk: np.array) -> Tuple[np.array, np.array]:
        # Generate a random point R on the elliptic curve
        R = self._generate_random_point()

        # Compute the isogeny φ: E → E/⟨R⟩
        φ = self._compute_isogeny(R, pk)

        # Compute the ciphertext c = φ(pk)
        c = self._evaluate_isogeny(φ, pk)

        # Compute the shared secret key k = H(c)
        k = self._hash(c)

        return c, k

    def decapsulate(self, sk: np.array, c: np.array) -> np.array:
        # Compute the isogeny φ: E → E/⟨R⟩ using the secret key sk
        φ = self._compute_isogeny(sk, c)

        # Compute the shared secret key k = H(c) using the isogeny φ
        k = self._hash(c)

        return k

    def _generate_random_point(self) -> np.array:
        # Generate a random point R on the elliptic curve
        x, y = np.random.randint(0, self.p, size=2)
        return np.array([x, y])

    def _compute_isogeny(self, R: np.array, pk: np.array) -> np.array:
        # Compute the isogeny φ: E → E/⟨R⟩
        φ = np.array([[R[0], R[1]], [pk[0], pk[1]]])
        return φ

    def _evaluate_isogeny(self, φ: np.array, pk: np.array) -> np.array:
        # Compute the ciphertext c = φ(pk)
        c = np.dot(φ, pk) % self.p
        return c

    def _hash(self, c: np.array) -> np.array:
        # Compute the hash of the ciphertext c
        h = hashlib.sha256(c.tobytes()).digest()
        return h
