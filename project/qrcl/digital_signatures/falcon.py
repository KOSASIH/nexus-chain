# digital_signatures/falcon.py

import os
import random
import hashlib
from typing import Tuple

class Falcon:
    def __init__(self, n: int, q: int, t: int, d: int, k: int):
        self.n = n  # Dimension of the lattice
        self.q = q  # Coefficient modulus for the lattice
        self.t = t  # Degree of the polynomials
        self.d = d  # Number of polynomials in the secret key
        self.k = k  # Number of repetitions

    def keygen(self) -> Tuple[Tuple[np.array, ...], Tuple[np.array, ...]]:
        # Generate a random secret key sk of size d * t
        sk = [np.random.randint(0, self.q, size=self.t) for _ in range(self.d)]

        # Generate a public key pk of size t * k
        pk = self._generate_public_key(sk)

        return sk, pk

    def sign(self, sk: Tuple[np.array, ...], m: bytes) -> Tuple[bytes, bytes]:
        # Generate a random nonce r of size t * k
        r = [np.random.randint(0, self.q, size=self.t) for _ in range(self.k)]

        # Compute the signature (c, z)
        c = self._compute_challenge(sk, r, m)
        z = self._compute_response(sk, r, c)

        # Serialize the signature (c, z)
        c_bytes = c.tobytes()
        z_bytes = z.tobytes()
        signature = c_bytes + z_bytes

        return signature, m

    def verify(self, pk: Tuple[np.array, ...], signature: bytes, m: bytes) -> bool:
        # Deserialize the signature (c, z)
        c_bytes = signature[:self.k * self.t]
        z_bytes = signature[self.k * self.t:]
        c = np.frombuffer(c_bytes, dtype=np.int64)
        z = np.frombuffer(z_bytes, dtype=np.int64)

        # Compute the verification key vk
        vk = self._compute_verification_key(pk, c)

        # Verify the signature (c, z) using the verification key vk
        return self._verify_signature(vk, z, c, m)

    def _generate_public_key(self, sk: Tuple[np.array, ...]) -> Tuple[np.array, ...]:
        # Generate a public key pk of size t * k
        pk = [self._compute_public_key(s) for s in sk]
        return pk

    def _compute_public_key(self, s: np.array) -> np.array:
        # Compute the public key pk from the secret key s
        pk = self._lattice_reduce(s * self.q)
        return pk

    def _compute_challenge(self, sk: Tuple[np.array, ...], r: Tuple[np.array, ...], m: bytes) -> np.array:
        # Compute the challenge c
        c = np.concatenate([self._hash(s) for s in sk])
        c = np.concatenate([c, self._hash(r)])
        c = np.concatenate([c, self._hash(m)])
        return c

    def _compute_response(self, sk: Tuple[np.array, ...], r: Tuple[np.array, ...], c: np.array) -> np.array:
        # Compute the response z
        z = [self._lattice_reduce(s * c[i] + r[i]) for i, s in enumerate(sk)]
        return z

    def _compute_verification_key(self, pk: Tuple[np.array, ...], c: np.array) -> np.array:
        # Compute the verification key vk
        vk = [self._compute_public_key(pk[i] * c[i]) for i in range(self.k)]
        return vk

    def _verify_signature(self, vk: np.array, z: np.array, c: np.array, m: bytes) -> bool:
        # Verify the signature (c, z) using the verification key vk
        for i in range(self.k):
            if not self._verify_component(vk[i], z[i], c[i], m):
                return False
        return True

    def _verify_component(self, vk: np.array, z: np.array, c: np.array, m: bytes) -> bool:
        # Verify a single component of the signature
        h = self._hash(vk * z + c + m)
        return h == c

    def _lattice_reduce(self, x: np.array) -> np.array:
        # Reduce the lattice vector x modulo the lattice
        return x % self.q

    def _hash(self, x: np.array) -> np.array:
        # Compute the hash of the lattice vector x
        h = hashlib.sha256(x.tobytes()).digest()
        return np.frombuffer(h, dtype=np.int64)
