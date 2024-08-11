# code_based/binary_goppa.py

import numpy as np
from scipy.linalg import lu_factor, lu_solve
from typing import Tuple

class BinaryGoppa:
    def __init__(self, n: int, k: int, t: int):
        self.n = n
        self.k = k
        self.t = t

    def keygen(self) -> Tuple[np.array, np.array]:
        G = self._generate_generator_matrix()
        H = self._generate_parity_check_matrix(G)
        return (G, H)

    def encrypt(self, m: np.array, G: np.array) -> np.array:
        c = self._encrypt(m, G)
        return c

    def decrypt(self, c: np.array, H: np.array) -> np.array:
        m = self._decrypt(c, H)
        return m

    def _generate_generator_matrix(self) -> np.array:
        # Generate a random binary matrix G of size k x n
        G = np.random.randint(0, 2, size=(self.k, self.n))
        return G

    def _generate_parity_check_matrix(self, G: np.array) -> np.array:
        # Generate a parity check matrix H of size (n-k) x n
        H = np.random.randint(0, 2, size=(self.n-self.k, self.n))
        return H

    def _encrypt(self, m: np.array, G: np.array) -> np.array:
        # Encrypt the message m using the generator matrix G
        c = np.dot(m, G) % 2
        # Add random errors to the ciphertext
        e = np.random.randint(0, 2, size=self.n)
        c += e
        return c

    def _decrypt(self, c: np.array, H: np.array) -> np.array:
        # Decrypt the ciphertext c using the parity check matrix H
        # Use the LU decomposition to solve the system of linear equations
        lu, piv = lu_factor(H)
        x = lu_solve((lu, piv), c)
        m = x[:self.k]
        return m
       
