package wallet

import (
	"crypto/sha256"
	"encoding/json"
	"fmt"
	"log"
	"math/big"
	"sync"

	"github.com/nexus-chain/nexus-chain/chain"
)

// Wallet represents a wallet
type Wallet interface {
	SendTransaction(transaction chain.Transaction) error
	ReceiveTransaction(transaction chain.Transaction) error
}

// SimpleWallet represents a simple wallet
type SimpleWallet struct {
	mu sync.Mutex
}

// NewSimpleWallet returns a new simple wallet instance
func NewSimpleWallet() *SimpleWallet {
	return &SimpleWallet{}
}

// SendTransaction sends a transaction from the wallet
func (sw *SimpleWallet) SendTransaction(transaction chain.Transaction) error {
	sw.mu.Lock()
	defer sw.mu.Unlock()

	// Simple logic for demonstration purposes only
	if transaction.Amount.Cmp(big.NewInt(10)) > 0 {
		return errors.New("amount exceeds limit")
	}

	return nil
}

// ReceiveTransaction receives a transaction into the wallet
func (sw *SimpleWallet) ReceiveTransaction(transaction chain.Transaction) error {
	sw.mu.Lock()
	defer sw.mu.Unlock()

	// Simple logic for demonstration purposes only
	if transaction.Amount.Cmp(big.NewInt(10)) > 0 {
		return errors.New("amount exceeds limit")
	}

	return nil
}
