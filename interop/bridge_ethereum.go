package interop

import (
	"context"
	"encoding/json"
	"fmt"
	"math/big"

	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/ethclient"
)

// EthereumBridge represents a bridge to the Ethereum blockchain
type EthereumBridge struct {
	client *ethclient.Client
}

// NewEthereumBridge returns a new instance of EthereumBridge
func NewEthereumBridge(url string) (*EthereumBridge, error) {
	client, err := ethclient.Dial(url)
	if err != nil {
		return nil, err
	}

	return &EthereumBridge{client: client}, nil
}

// Initialize initializes the Ethereum bridge
func (eb *EthereumBridge) Initialize(ctx context.Context) error {
	// Initialize the Ethereum client
	err := eb.client.Initialize(ctx)
	if err != nil {
		return err
	}

	return nil
}

// SendTransaction sends a transaction to the Ethereum blockchain
func (eb *EthereumBridge) SendTransaction(ctx context.Context, tx []byte) error {
	// Unmarshal the transaction bytes into an Ethereum transaction
	var ethTx types.Transaction
	err := json.Unmarshal(tx, &ethTx)
	if err != nil {
		return err
	}

	// Send the transaction to the Ethereum blockchain
	err = eb.client.SendTransaction(ctx, &ethTx)
	if err != nil {
		return err
	}

	return nil
}

// ReceiveTransaction receives a transaction from the Ethereum blockchain
func (eb *EthereumBridge) ReceiveTransaction(ctx context.Context, tx []byte) error {
	// Unmarshal the transaction bytes into an Ethereum transaction
	var ethTx types.Transaction
	err := json.Unmarshal(tx, &ethTx)
	if err != nil {
		return err
	}

	// Receive the transaction from the Ethereum blockchain
	err = eb.client.ReceiveTransaction(ctx, &ethTx)
	if err != nil {
		return err
	}

	return nil
}

// GetAccountBalance returns the balance of an Ethereum account
func (eb *EthereumBridge) GetAccountBalance(ctx context.Context, account common.Address) (*big.Int, error) {
	// Get the balance of the Ethereum account
	balance, err := eb.client.BalanceAt(ctx, account, nil)
	if err != nil {
		return nil, err
	}

	return balance, nil
}

// GetTransactionByHash returns an Ethereum transaction by its hash
func (eb *EthereumBridge) GetTransactionByHash(ctx context.Context, hash common.Hash) (*types.Transaction, error) {
	// Get the transaction by its hash
	tx, _, err := eb.client.TransactionByHash(ctx, hash)
	if err != nil {
		return nil, err
	}

	return tx, nil
}
