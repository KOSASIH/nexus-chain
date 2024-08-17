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
	"github.com/maticnetwork/bor/v2"
)

// SecondLayerClient represents a second-layer client
type SecondLayerClient struct {
	client  *ethclient.Client
	bor     *bor.Bor
	chainID *big.Int
}

// NewSecondLayerClient returns a new instance of SecondLayerClient
func NewSecondLayerClient(url string, borURL string, chainID *big.Int) (*SecondLayerClient, error) {
	client, err := ethclient.Dial(url)
	if err != nil {
		return nil, err
	}

	borClient, err := bor.NewBor(borURL)
	if err != nil {
		return nil, err
	}

	return &SecondLayerClient{
		client:  client,
		bor:     borClient,
		chainID: chainID,
	}, nil
}

// GetSecondLayerTransactions returns the second-layer transactions
func (slc *SecondLayerClient) GetSecondLayerTransactions() ([]*types.Transaction, error) {
	return slc.bor.GetTransactions(context.Background())
}

// SendSecondLayerTransaction sends a second-layer transaction
func (slc *SecondLayerClient) SendSecondLayerTransaction(tx *types.Transaction) error {
	return slc.bor.SendTransaction(context.Background(), tx)
}

// GetSecondLayerState returns the second-layer state
func (slc *SecondLayerClient) GetSecondLayerState() (*bor.State, error) {
	return slc.bor.GetState(context.Background())
}

// GetSecondLayerValidators returns the second-layer validators
func (slc *SecondLayerClient) GetSecondLayerValidators() ([]*ecdsa.PublicKey, error) {
	return slc.bor.GetValidators(context.Background())
}
