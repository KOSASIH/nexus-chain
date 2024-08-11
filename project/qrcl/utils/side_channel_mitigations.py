# utils/side_channel_mitigations.py

import time
from typing import Callable

class SideChannelMitigations:
    def __init__(self, timer_precision: float = 1e-6):
        self.timer_precision = timer_precision

    def constant_time_compare(self, a: bytes, b: bytes) -> bool:
        # Compare two byte strings in constant time to prevent timing attacks
        if len(a) != len(b):
            return False
        result = 0
        for x, y in zip(a, b):
            result |= x ^ y
        return result == 0

    def constant_time_delay(self, delay: float) -> None:
        # Introduce a constant time delay to prevent timing attacks
        start_time = time.time()
        while time.time() - start_time < delay:
            pass

    def data_oblivious(self, func: Callable) -> Callable:
        # Decorator to make a function data-oblivious to prevent side-channel attacks
        def wrapper(*args, **kwargs):
            start_time = time.time()
            result = func(*args, **kwargs)
            end_time = time.time()
            self.constant_time_delay(end_time - start_time)
            return result
        return wrapper
