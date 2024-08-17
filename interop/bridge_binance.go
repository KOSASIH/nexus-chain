package interop

import (
	"context"
	"encoding/json"
	"fmt"

	"github.com/binance-chain/go-sdk/client"
	"github.com/binance-chain/go-sdk/common"
	"github.com/binance-chain/go-sdk/types"
)

// BinanceBridge represents a bridge to the Binance Smart Chain
type BinanceBridge struct {
	client *client.Client
}

// NewBinanceBridge returns a new instance of BinanceBridge
func NewBinanceBridge(url string) (*BinanceBridge, error) {
	client, err := client.NewClient(url)
	if err != nil {
		return nil, err
	}

	return &BinanceBridge{client: client}, nil
}

// Initialize initializes the Binance bridge
func (bb *BinanceBridge) Initialize(ctx context.Context) error {
	// Initialize the Binance client
	err := bb.client.Initialize(ctx)
	if err != nil {
		return err
	}

	return nil
}

// SendTransaction sends a transaction to the Binance Smart Chain
func (bb *BinanceBridge) SendTransaction(ctx context.Context, tx []byte) error {
	// Unmarshal the transaction bytes into a Binance transaction
	var binTx types.Transaction
	err := json.Unmarshal(tx, &binTx)
	if err != nil {
		return err
	}

	// Send the transaction to the Binance Smart Chain
	err = bb.client.BroadcastTransaction(ctx, &binTx)
	if err != nil {
		return err
	}

	return nil
}

// ReceiveTransaction receives a transaction from the Binance Smart Chain
func (bb *BinanceBridge) ReceiveTransaction(ctx context.Context, tx []byte) error {
	// Unmarshal the transaction bytes into a Binance transaction
	var binTx types.Transaction
	err := json.Unmarshal(tx, &binTx)
	if err != nil {
		return err
	}

	// Receive the transaction from the Binance Smart Chain
	err = bb.client.GetTransaction(ctx, binTx.Hash)
	if err != nil {
		return err
	}

	return nil
}

// GetAccountBalance returns the balance of a Binance account
func (bb *BinanceBridge) GetAccountBalance(ctx context.Context, account common.Address) (*big.Int, error) {
	// Get the balance of the Binance account
	balance, err := bb.client.GetBalance(ctx, account)
	if err != nil {
		return nil, err
	}

	return balance, nil
}

// GetTransactionByHash returns a Binance transaction by its hash
func (bb *BinanceBridge) GetTransactionByHash(ctx context.Context, hash common.Hash) (*types.Transaction, error) {
	// Get the transaction by its hash
	tx, err := bb.client.GetTransaction(ctx, hash)
	if err != nil {
		return nil, err
	}

	return tx, nil
}
