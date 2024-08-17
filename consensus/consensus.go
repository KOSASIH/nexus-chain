package consensus

import (
	"crypto/sha256"
	"encoding/json"
	"fmt"
	"log"
	"math/big"
	"sync"

	"github.com/nexus-chain/nexus-chain/chain"
)

// ConsensusAlgorithm represents a consensus algorithm
type ConsensusAlgorithm interface {
	ValidateBlock(block chain.Block) bool
	ValidateTransaction(tx chain.Transaction) bool
}

// ProofOfWork represents a proof-of-work consensus algorithm
type ProofOfWork struct {
	Target big.Int
}

// NewProofOfWork returns a new proof-of-work consensus algorithm instance
func NewProofOfWork(target big.Int) *ProofOfWork {
	return &ProofOfWork{
		Target: target,
	}
}

// ValidateBlock validates a block using proof-of-work
func (pow *ProofOfWork) ValidateBlock(block chain.Block) bool {
	hash := sha256.New()
	hash.Write([]byte(block.Header.PreviousHash))
	hash.Write([]byte(block.Header.Timestamp))
	hash.Write([]byte(block.Header.Height))

	return pow.checkProofOfWork(hash.Sum(nil))
}

// ValidateTransaction validates a transaction using proof-of-work
func (pow *ProofOfWork) ValidateTransaction(tx chain.Transaction) bool {
	hash := sha256.New()
	hash.Write([]byte(tx.From))
	hash.Write([]byte(tx.To))
	hash.Write([]byte(tx.Amount.String()))

	return pow.checkProofOfWork(hash.Sum(nil))
}

func (pow *ProofOfWork)
