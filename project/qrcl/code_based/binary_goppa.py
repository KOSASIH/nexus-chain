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
       
