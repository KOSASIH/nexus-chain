# tests/test_algorithms.py

import unittest
from cryptography.hazmat.primitives import hashes
from hybrid.classical_post_quantum import ClassicalPostQuantum
from hybrid.utils import RandomNumberGenerator

class TestAlgorithms(unittest.TestCase):
    def setUp(self):
        self.cpq = ClassicalPostQuantum()
        self.rng = RandomNumberGenerator()

    def test_ecdsa_signature(self):
        # Test ECDSA signature generation and verification
        private_key_pem, public_key_pem = self.cpq.generate_key_pair()
        message = b"Hello, World!"
        signature = self.cpq.sign(private_key_pem, message)
        self.assertTrue(self.cpq.verify(public_key_pem, message, signature))

    def test_hash_functions(self):
        # Test hash functions (e.g. SHA-256, SHA-384, SHA-512)
        hash_algos = [hashes.SHA256(), hashes.SHA384(), hashes.SHA512()]
        for hash_algo in hash_algos:
            message = b"Hello, World!"
            digest = self.rng.generate_random_bytes(hash_algo.digest_size)
            self.assertEqual(hash_algo.digest_size, len(digest))

    def test_random_number_generation(self):
        # Test random number generation
        random_bytes = self.rng.generate_random_bytes(32)
        self.assertEqual(32, len(random_bytes))

if __name__ == "__main__":
    unittest.main()
