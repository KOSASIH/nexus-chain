package analytics

import (
	"context"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"

	"github.com/etherscan/etherscan-go"
	"github.com/binance-chain/bscscan-go"
)

// ExplorerClient represents a blockchain explorer client
type ExplorerClient struct {
	etherscan *etherscan.Client
	bscscan   *bscscan.Client
}

// NewExplorerClient returns a new instance of ExplorerClient
func NewExplorerClient(etherscanAPIKey string, bscscanAPIKey string) (*ExplorerClient, error) {
	etherscanClient, err := etherscan.NewClient(etherscanAPIKey)
	if err != nil {
		return nil, err
	}

	bscscanClient, err := bscscan.NewClient(bscscanAPIKey)
	if err != nil {
		return nil, err
	}

	return &ExplorerClient{
		etherscan: etherscanClient,
		bscscan:   bscscanClient,
	}, nil
}

// GetTransactionByHash returns a transaction by hash
func (ec *ExplorerClient) GetTransactionByHash(hash string, chain string) (*Transaction, error) {
	var tx *Transaction
	var err error

	if chain == "eth" {
		tx, err = ec.etherscan.GetTransactionByHash(context.Background(), hash)
	} else if chain == "bsc" {
		tx, err = ec.bscscan.GetTransactionByHash(context.Background(), hash)
	} else {
		return nil, fmt.Errorf("unsupported chain: %s", chain)
	}

	return tx, err
}

// GetBlockByNumber returns a block by number
func (ec *ExplorerClient) GetBlockByNumber(number int64, chain string) (*Block, error) {
	var block *Block
	var err error

	if chain == "eth" {
		block, err = ec.etherscan.GetBlockByNumber(context.Background(), number)
	} else if chain == "bsc" {
		block, err = ec.bscscan.GetBlockByNumber(context.Background(), number)
	} else {
		return nil, fmt.Errorf("unsupported chain: %s", chain)
	}

	return block, err
}

// GetAccountBalance returns an account balance
func (ec *ExplorerClient) GetAccountBalance(address string, chain string) (*Balance, error) {
	var balance *Balance
	var err error

	if chain == "eth" {
		balance, err = ec.etherscan.GetAccountBalance(context.Background(), address)
	} else if chain == "bsc" {
		balance, err = ec.bscscan.GetAccountBalance(context.Background(), address)
	} else {
		return nil, fmt.Errorf("unsupported chain: %s", chain)
	}

	return balance, err
}

type Transaction struct {
	Hash         string `json:"hash"`
	BlockNumber  int64  `json:"blockNumber"`
	From         string `json:"from"`
	To           string `json:"to"`
	Value        string `json:"value"`
	Gas          int64  `json:"gas"`
	GasPrice     string `json:"gasPrice"`
	Nonce        int64  `json:"nonce"`
	Timestamp    int64  `json:"timestamp"`
	Confirmations int64  `json:"confirmations"`
}

type Block struct {
	Number       int64  `json:"number"`
	Hash         string `json:"hash"`
	Timestamp    int64  `json:"timestamp"`
	Transactions []Transaction `json:"transactions"`
}

type Balance struct {
	Address string `json:"address"`
	Balance string `json:"balance"`
}
