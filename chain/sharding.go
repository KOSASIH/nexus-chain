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
	"github.com/ethereum/go-ethereum/sharding"
)

// ShardingClient represents a sharding client
type ShardingClient struct {
	client  *ethclient.Client
	shardID uint64
}

// NewShardingClient returns a new instance of ShardingClient
func NewShardingClient(url string, shardID uint64) (*ShardingClient, error) {
	client, err := ethclient.Dial(url)
	if err != nil {
		return nil, err
	}

	return &ShardingClient{
		client:  client,
		shardID: shardID,
	}, nil
}

// GetShardID returns the shard ID
func (sc *ShardingClient) GetShardID() uint64 {
	return sc.shardID
}

// GetShardHash returns the shard hash
func (sc *ShardingClient) GetShardHash() common.Hash {
	return sc.client.BlockChain().CurrentBlock().Hash()
}

// GetShardTransactions returns the transactions in the shard
func (sc *ShardingClient) GetShardTransactions() ([]*types.Transaction, error) {
	block, err := sc.client.BlockByNumber(context.Background(), nil)
	if err != nil {
		return nil, err
	}

	var txs []*types.Transaction
	for _, tx := range block.Transactions() {
		if sharding.IsShardTransaction(tx, sc.shardID) {
			txs = append(txs, tx)
		}
	}

	return txs, nil
}

// SendShardTransaction sends a transaction to the shard
func (sc *ShardingClient) SendShardTransaction(tx *types.Transaction) error {
	return sc.client.SendTransaction(context.Background(), tx)
}

// GetShardState returns the shard state
func (sc *ShardingClient) GetShardState() (*sharding.ShardState, error) {
	return sc.client.ShardState(context.Background(), sc.shardID)
}

// GetShardValidators returns the shard validators
func (sc *ShardingClient) GetShardValidators() ([]*ecdsa.PublicKey, error) {
	return sc.client.ShardValidators(context.Background(), sc.shardID)
}
