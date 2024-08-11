# hybrid/classical_post_quantum.py

import os
import random
import hashlib
from typing import Tuple
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa, ec
from cryptography.hazmat.backends import default_backend

class ClassicalPostQuantum:
    def __init__(self, curve: str = "secp256r1", hash_func: str = "sha256"):
        self.curve = curve
        self.hash_func = hash_func
        self.backend = default_backend()

    def generate_key_pair(self) -> Tuple[bytes, bytes]:
        # Generate a classical key pair (private key, public key)
        private_key = ec.generate_private_key(
            curve=ec.SECP256R1(),
            backend=self.backend
        )
        public_key = private_key.public_key()
        private_key_pem = private_key.private_bytes(
            encoding=serialization.Encoding.PEM,
            format=serialization.PrivateFormat.TraditionalOpenSSL,
            encryption_algorithm=serialization.NoEncryption()
        )
        public_key_pem = public_key.public_bytes(
            encoding=serialization.Encoding.OpenSSH,
            format=serialization.PublicFormat.OpenSSH
        )
        return private_key_pem, public_key_pem

    def sign(self, private_key_pem: bytes, message: bytes) -> bytes:
        # Sign a message using the classical private key
        private_key = serialization.load_pem_private_key(
            private_key_pem,
            password=None,
            backend=self.backend
        )
        signature = private_key.sign(
            message,
            padding=ec.ECDSA(self.hash_func),
            algorithm=ec.ECDSA(self.hash_func)
        )
        return signature

    def verify(self, public_key_pem: bytes, message: bytes, signature: bytes) -> bool:
        # Verify a signature using the classical public key
        public_key = serialization.load_ssh_public_key(
            public_key_pem,
            backend=self.backend
        )
        try:
            public_key.verify(
                signature,
                message,
                padding=ec.ECDSA(self.hash_func),
                algorithm=ec.ECDSA(self.hash_func)
            )
            return True
        except ValueError:
            return False
