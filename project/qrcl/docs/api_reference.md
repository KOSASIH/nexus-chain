**docs/api_reference.md**
```markdown
# API Reference

## QRCL

### `__init__`

Initializes the QRCL object.

### `generate_key_pair`

Generates a key pair for the specified algorithm.

* `algorithm`: The algorithm to use (e.g. "newhope", "sphincs", etc.).
* `return`: A tuple containing the private key and public key.

### `encrypt`

Encrypts data using the public key.

* `public_key`: The public key.
* `message`: The message to encrypt.
* `return`: The encrypted ciphertext.

### `decrypt`

Decrypts data using the private key.

* `private_key`: The private key.
* `ciphertext`: The ciphertext to decrypt.
* `return`: The decrypted plaintext.

### `sign`

Signs data using the private key.

* `private_key`: The private key.
* `message`: The message to sign.
* `return`: The digital signature.

### `verify`

Verifies a digital signature using the public key.

* `public_key`: The public key.
* `message`: The message to verify.
* `signature`: The digital signature.
* `return`: A boolean indicating whether the signature is valid.

### `rng`

Returns a random number generator object.

### `scm`

Returns a side-channel mitigation object.

For more information on the QRCL API, please refer to the [Usage Guide](usage_guide.md).
