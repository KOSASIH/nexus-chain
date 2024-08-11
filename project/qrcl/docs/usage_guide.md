# QRCL Usage Guide

## Installation

`pip install qrcl`

## Importing the Library

`import qrcl`

## Key Pair Generation

`qrcl_obj = qrcl.QRCL(); private_key, public_key = qrcl_obj.generate_key_pair("newhope")`

## Encrypt and Decrypt

`ciphertext = qrcl_obj.encrypt(public_key, b"Hello, World!"); plaintext = qrcl_obj.decrypt(private_key, ciphertext)`

## Sign and Verify

`signature = qrcl_obj.sign(private_key, b"Hello, World!"); verified = qrcl_obj.verify(public_key, b"Hello, World!", signature)`

## Random Number Generation

`rng = qrcl.QRCL().rng; random_bytes = rng.generate_random_bytes(32)`

## Side-Channel Mitigations

`scm = qrcl.QRCL().scm; scm.constant_time_delay(1.0)`

For more information, please refer to the [API Reference](api_reference.md).
