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

    def encapsulate(self,
