# hash_based/sphincs.py

import hashlib
import hmac
import os
from typing import Tuple, List

class SPHINCS:
    def __init__(self, n: int, h: int, d: int, k: int, w: int):
        self.n = n  # Number of bits in the hash output
        self.h = h  # Number of bits in the hash input
        self.d = d  # Number of layers in the hypertree
        self.k = k  # Number of bits in the key
        self.w = w  # Number of bits in the Winternitz parameter

        self.H = hashlib.sha256  # Hash function
        self.Hmac = hmac.HMAC  # HMAC function

    def keygen(self) -> Tuple[bytes, bytes]:
        # Generate a random secret key SK of size k
        SK = os.urandom(self.k // 8)

        # Generate a public key PK of size n
        PK = self._generate_public_key(SK)

        return SK, PK

    def sign(self, M: bytes, SK: bytes) -> bytes:
        # Sign the message M using the secret key SK
        σ = self._sign(M, SK)
        return σ

    def verify(self, M: bytes, σ: bytes, PK: bytes) -> bool:
        # Verify the signature σ using the public key PK
        return self._verify(M, σ, PK)

    def _generate_public_key(self, SK: bytes) -> bytes:
        # Generate a public key PK of size n
        PK = self.Hmac(SK, b'', digestmod=self.H).digest()
        return PK

    def _sign(self, M: bytes, SK: bytes) -> bytes:
        # Sign the message M using the secret key SK
        θ = self._compute_theta(M, SK)
        σ = self._compute_sigma(θ, SK)
        return σ

    def _compute_theta(self, M: bytes, SK: bytes) -> List[bytes]:
        # Compute the theta values for the message M
        θ = []
        for i in range(self.d):
            θ_i = self.Hmac(SK, M + bytes([i]), digestmod=self.H).digest()
            θ.append(θ_i)
        return θ

    def _compute_sigma(self, θ: List[bytes], SK: bytes) -> bytes:
        # Compute the sigma value for the theta values
        σ = b''
        for i in range(self.d):
            σ_i = self.Hmac(SK, θ[i], digestmod=self.H).digest()
            σ += σ_i
        return σ

    def _verify(self, M: bytes, σ: bytes, PK: bytes) -> bool:
        # Verify the signature σ using the public key PK
        θ = self._compute_theta(M, PK)
        σ_prime = self._compute_sigma(θ, PK)
        return hmac.compare_digest(σ, σ_prime)
