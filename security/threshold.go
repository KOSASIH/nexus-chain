package security

import (
	"crypto/rand"
	"fmt"
	"math/big"

	"github.com/threshold-cryptography/threshold-crypto-go/threshold"
)

// ThresholdSignature represents a threshold signature
type ThresholdSignature struct {
	threshold int
	pubKeys   []*threshold.PublicKey
}

// NewThresholdSignature returns a new instance of ThresholdSignature
func NewThresholdSignature(threshold int, pubKeys []*threshold.PublicKey) (*ThresholdSignature, error) {
	// Create a new instance of the threshold signature
	sig := &ThresholdSignature{
		threshold: threshold,
		pubKeys:   pubKeys,
	}

	return sig, nil
}

// Sign signs a message with the threshold signature
func (ts *ThresholdSignature) Sign(message []byte, privKeys []*threshold.PrivateKey) ([]byte, error) {
	// Sign the message with the threshold signature
	sig, err := threshold.Sign(message, ts.threshold, ts.pubKeys, privKeys)
	if err != nil {
		return nil, err
	}

	return sig, nil
}

// Verify verifies a signature with the threshold signature
func (ts *ThresholdSignature) Verify(sig []byte, message []byte) (bool, error) {
	// Verify the signature with the threshold signature
	valid, err := threshold.Verify(sig, message, ts.threshold, ts.pubKeys)
	if err != nil {
		return false, err
	}

	return valid, nil
}
