# qrcl/utils/errors.py

class QRCLException(Exception):
    pass

class KeyGenerationError(QRCLException):
    pass

class EncryptionError(QRCLException):
    pass

class DecryptionError(QRCLException):
   
class InvalidKeyError(QRCLException):
    pass

class InvalidMessageError(QRCLException):
    pass

class CryptographyError(QRCLException):
    pass
