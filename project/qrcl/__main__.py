# qrcl/__main__.py

from .algorithms import *
from .utils import *

def main():
    # Example usage:
    ntru = NTRU(512, 2048, 128, 3.2)
    f, h = ntru.keygen()
    m = np.poly1d([1, 2, 3, 4, 5])
    e = ntru.encrypt(m, h)
    m_decrypted = ntru.decrypt(e, f)
    print(m_decrypted)

if __name__ == "__main__":
    main()
