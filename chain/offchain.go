package scalability

import (
	"context"
	"crypto/ecdsa"
	"encoding/hex"
	"fmt"
	"math/big"

	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/ethclient"
	"github.com/optimism-io/optimism-go/optimism"
)

// OffchainClient represents an off-chain client
type OffchainClient struct {
	client  *ethclient.Client
	optimism *optimism.Optimism
}

// NewOffchainClient returns a new instance of OffchainClient
func NewOffchainClient(url string, optimismURL string) (*OffchainClient, error) {
	client, err := ethclient.Dial(url)
	if err != nil {
		return nil, err
	}

	optimismClient, err := optimism.NewOptimism(optimismURL)
	if err != nil {
		return nil, err
	}

	return &OffchainClient{
		client:  client,
		optimism: optimismClient,
	}, nil
}

// GetOffchainTransactions returns the off-chain transactions
func (oc *OffchainClient) GetOffchainTransactions() ([]*types.Transaction, error) {
	return oc.optimism.GetTransactions(context.Background())
}

// SendOffchainTransaction sends an off-chain transaction
func (oc *OffchainClient) SendOffchainTransaction(tx *types.Transaction) error {
	return oc.optimism.SendTransaction(context.Background(), tx)
}

// GetOffchainState returns the off-chain state
func (oc *OffchainClient) GetOffchainState() (*optimism.State, error) {
	return oc.optimism.GetState(context.Background())
}

// GetOffchainValidators returns the off-chain validators
func (oc *OffchainClient) GetOffchainValidators() ([]*ecdsa.PublicKey, error) {
	return oc.optimism.GetValidators(context.Background())
}
