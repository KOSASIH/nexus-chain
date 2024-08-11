# qrcl/utils/helper_functions.py

import numpy as np

def poly_to_bytes(poly: np.poly1d) -> bytes:
    coeffs = poly.c
    return bytes(coeffs)

def bytes_to_poly(b: bytes) -> np.poly1d:
    coeffs = np.frombuffer(b, dtype=np.int8)
    return np.poly1d(coeffs)

def int_to_bytes(n: int) -> bytes:
    return n.to_bytes((n.bit_length() + 7) // 8, 'big')

def bytes_to_int(b: bytes) -> int:
    return int.from_bytes(b, 'big')
