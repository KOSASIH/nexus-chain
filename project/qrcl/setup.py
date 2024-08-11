# setup.py

import os
import sys
from setuptools import setup, find_packages

# QRCL metadata
NAME = "qrcl"
VERSION = "1.0.0"
DESCRIPTION = "Quantum-Resistant Cryptography Library"
AUTHOR = "NexusChain"
AUTHOR_EMAIL = "qrcl@nexus-chain.com"
URL = "https://github.com/nexus-chain/qrcl"

# Dependencies
INSTALL_REQUIRES = [
    "cryptography==3.4.7",
    "pycryptodome==3.10.1",
    "hashlib==1.0.4",
    "ntru==1.2.3",
    "ring-lwe==1.1.2",
    "mceliece==1.0.2",
    "reed-solomon==1.3.1",
    "rainbow==1.2.1",
    "sidh==1.1.1",
    "sphincs==1.0.1",
    "xmss==1.2.2",
    "new-hope==1.1.2",
    "frodokem==1.2.1",
    "sidh==1.1.1",
    "dilithium==1.2.1",
    "falcon==1.1.2",
    "classical-post-quantum==1.1.1",
]

TEST_REQUIRES = [
    "pytest==6.2.4",
    "hypothesis==6.2.0",
]

DOC_REQUIRES = [
    "sphinx==3.5.3",
    "sphinx-rtd-theme==0.5.2",
]

DEV_REQUIRES = [
    "pre-commit==2.13.0",
    "black==21.6b0",
    "isort==5.9.3",
]

# Setup
setup(
    name=NAME,
    version=VERSION,
    description=DESCRIPTION,
    author=AUTHOR,
    author_email=AUTHOR_EMAIL,
    url=URL,
    packages=find_packages(),
    install_requires=INSTALL_REQUIRES,
    tests_require=TEST_REQUIRES,
    doc_requires=DOC_REQUIRES,
    dev_requires=DEV_REQUIRES,
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: OS Independent",
    ],
)
