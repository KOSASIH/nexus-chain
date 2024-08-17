package security

import (
	"crypto/ecdsa"
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"math/big"

	"github.com/btcsuite/btcd/btcec"
	"github.com/btcsuite/btcd/chaincfg"
	"github.com/btcsuite/btcd/txscript"
)

// MultiSigWallet represents a multi-signature wallet
type MultiSigWallet struct {
	threshold int
	pubKeys     []*ecdsa.PublicKey
	script      []byte
}

// NewMultiSigWallet returns a new instance of MultiSigWallet
func NewMultiSigWallet(threshold int, pubKeys []*ecdsa.PublicKey) (*MultiSigWallet, error) {
	// Create a new instance of the multi-signature wallet
	wallet := &MultiSigWallet{
		threshold: threshold,
		pubKeys:   pubKeys,
	}

	// Create the script for the multi-signature wallet
	script, err := txscript.NewScriptBuilder().AddOp(txscript.OP_1).AddData(pubKeys[0].SerializeCompressed()).AddOp(txscript.OP_CHECKSIG).AddOp(txscript.OP_DROP).AddOp(txscript.OP_1).AddData(pubKeys[1].SerializeCompressed()).AddOp(txscript.OP_CHECKSIG).AddOp(txscript.OP_DROP).AddOp(txscript.OP_2).AddOp(txscript.OP_CHECKMULTISIG).Build()
	if err != nil {
		return nil, err
	}

	wallet.script = script

	return wallet, nil
}

// Sign signs a transaction with the multi-signature wallet
func (msw *MultiSigWallet) Sign(tx *types.Transaction, privKeys []*ecdsa.PrivateKey) ([]byte, error) {
	// Sign the transaction with the multi-signature wallet
	sig, err := txscript.SignTxOutput(msw.script, tx, privKeys)
	if err != nil {
		return nil, err
	}

	return sig, nil
}

// Verify verifies a signature with the multi-signature wallet
func (msw *MultiSigWallet) Verify(sig []byte, tx *types.Transaction) (bool, error) {
	// Verify the signature with the multi-signature wallet
	valid, err := txscript.VerifyScript(msw.script, tx, sig)
	if err != nil {
		return false, err
	}

	return valid, nil
}
