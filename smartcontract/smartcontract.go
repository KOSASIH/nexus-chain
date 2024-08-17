package smartcontract

import (
	"crypto/sha256"
	"encoding/json"
	"fmt"
	"log"
	"math/big"
	"sync"

	"github.com/nexus-chain/nexus-chain/chain"
)

// SmartContract represents a smart contract
type SmartContract interface {
	Execute(transaction chain.Transaction) error
}

// SimpleSmartContract represents a simple smart contract
type SimpleSmartContract struct {
	mu sync.Mutex
}

// NewSimpleSmartContract returns a new simple smart contract instance
func NewSimpleSmartContract() *SimpleSmartContract {
	return &SimpleSmartContract{}
}

// Execute executes a transaction on the smart contract
func (ssc *SimpleSmartContract) Execute(transaction chain.Transaction) error {
	ssc.mu.Lock()
	defer ssc.mu.Unlock()

	// Simple logic for demonstration purposes only
	if transaction.Amount.Cmp(big.NewInt(10)) > 0 {
		return errors.New("amount exceeds limit")
	}

	return nil
}
