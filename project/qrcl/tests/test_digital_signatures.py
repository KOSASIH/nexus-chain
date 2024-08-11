# tests/test_digital_signatures.py

import unittest
from hybrid.classical_post_quantum import ClassicalPostQuantum

class TestDigitalSignatures(unittest.TestCase):
    def setUp(self):
        self.cpq = ClassicalPostQuantum()

    def test_digital_signature(self):
        # Test digital signature generation and verification
        private_key_pem, public_key_pem = self.cpq.generate_key_pair()
        message = b"Hello, World!"
        signature = self.cpq.sign(private_key_pem, message)
        self.assertTrue(self.cpq.verify(public_key_pem, message, signature))

    def test_signature_replay_attack(self):
        # Test resistance to signature replay attacks
        private_key_pem, public_key_pem = self.cpq.generate_key_pair()
        message1 = b"Hello, World!"
        message2 = b"Goodbye, World!"
        signature1 = self.cpq.sign(private_key_pem, message1)
        self.assertFalse(self.cpq.verify(public_key_pem, message2, signature1))

if __name__ == "__main__":
    unittest.main()
