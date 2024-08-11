# tests/test_key_agreement.py

import unittest
from hybrid.hybrid_key_exchange import HybridKeyExchange

class TestKeyAgreement(unittest.TestCase):
    def setUp(self):
        self.hke = HybridKeyExchange()

    def test_key_exchange(self):
        # Test hybrid key exchange protocol
        alice_private_key, alice_public_key = self.hke.generate_key_pair()
        bob_private_key, bob_public_key = self.hke.generate_key_pair()
        alice_shared_secret = self.hke.compute_shared_secret(alice_private_key, bob_public_key)
        bob_shared_secret = self.hke.compute_shared_secret(bob_private_key, alice_public_key)
        self.assertEqual(alice_shared_secret, bob_shared_secret)

if __name__ == "__main__":
    unittest.main()
