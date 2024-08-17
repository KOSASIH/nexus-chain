package chain

import (
	"crypto/sha256"
	"encoding/json"
	"fmt"
	"log"
	"math/big"
	"sync"

	"github.com/nexus-chain/nexus-chain/consensus"
	"github.com/nexus-chain/nexus-chain/network"
	"github.com/nexus-chain/nexus-chain/smartcontract"
	"github.com/nexus-chain/nexus-chain/wallet"
)

// Blockchain represents the blockchain data structure
type Blockchain struct {
	Chain               []Block
	Height              uint64
	CurrentBlock        Block
	PreviousBlockHash   string
	ConsensusAlgorithm  consensus.ConsensusAlgorithm
	Network             network.Network
	SmartContractEngine smartcontract.SmartContractEngine
	Wallet              wallet.Wallet
	mu                  sync.Mutex
}

// Block represents a block in the blockchain
type Block struct {
	Header       BlockHeader
	Transactions []Transaction
}

// BlockHeader represents the header of a block
type BlockHeader struct {
	Hash         string
	PreviousHash string
	Timestamp    uint64
	Height       uint64
}

// Transaction represents a transaction in the blockchain
type Transaction struct {
	From   string
	To     string
	Amount big.Int
}

// NewBlockchain returns a new blockchain instance
func NewBlockchain(consensusAlgorithm consensus.ConsensusAlgorithm, network network.Network, smartContractEngine smartcontract.SmartContractEngine, wallet wallet.Wallet) *Blockchain {
	return &Blockchain{
		Chain:               make([]Block, 0),
		Height:              0,
		CurrentBlock:        Block{},
		PreviousBlockHash:   "",
		ConsensusAlgorithm:  consensusAlgorithm,
		Network:             network,
		SmartContractEngine: smartContractEngine,
		Wallet:              wallet,
	}
}

// AddBlock adds a new block to the blockchain
func (bc *Blockchain) AddBlock(block Block) {
	bc.mu.Lock()
	defer bc.mu.Unlock()

	bc.Chain = append(bc.Chain, block)
	bc.Height++
	bc.CurrentBlock = block
	bc.PreviousBlockHash = block.Header.Hash
}

// GetBlock returns a block at a given height
func (bc *Blockchain) GetBlock(height uint64) Block {
	bc.mu.Lock()
	defer bc.mu.Unlock()

	for _, block := range bc.Chain {
		if block.Header.Height == height {
			return block
		}
	}

	return Block{}
}

// GetTransaction returns a transaction with a given hash
func (bc *Blockchain) GetTransaction(hash string) Transaction {
	bc.mu.Lock()
	defer bc.mu.Unlock()

	for _, block := range bc.Chain {
		for _, tx := range block.Transactions {
			if tx.Hash() == hash {
				return tx
			}
		}
	}

	return Transaction{}
}

// Hash returns the hash of a block
func (b *Block) Hash() string {
	hash := sha256.New()
	hash.Write([]byte(b.Header.PreviousHash))
	hash.Write([]byte(b.Header.Timestamp))
	hash.Write([]byte(b.Header.Height))

	return fmt.Sprintf("%x", hash.Sum(nil))
}

// Hash returns the hash of a transaction
func (tx *Transaction) Hash() string {
	hash := sha256.New()
	hash.Write([]byte(tx.From))
	hash.Write([]byte(tx.To))
	hash.Write([]byte(tx.Amount.String()))

	return fmt.Sprintf("%x", hash.Sum(nil))
}
