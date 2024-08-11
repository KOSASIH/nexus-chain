# qrcl/utils/errors.py

class QRCLException(Exception):
    pass

class KeyGenerationError(QRCLException):
    pass

class EncryptionError(QRCLException):
    pass

class DecryptionError(QRCLException):
   
