package defi

import (
	"fmt"
	"math/big"

	"github.com/makerdao/maker-go"
	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
)

// Stablecoin represents a stablecoin
type Stablecoin struct {
	makerClient *maker.Client
}

// NewStablecoin returns a new instance of Stablecoin
func NewStablecoin(url string) (*Stablecoin, error) {
	client, err := maker.NewClient(url)
	if err != nil {
		return nil, err
	}

	return &Stablecoin{makerClient: client}, nil
}

// Mint mints a new stablecoin
func (sc *Stablecoin) Mint(ctx context.Context, amount *big.Int) error {
	// Mint the stablecoin
	tx, err := sc.makerClient.Mint(ctx, amount)
	if err != nil {
		return err
	}

	fmt.Printf("Minted %s stablecoin: %s\n", amount, tx.Hash().Hex())

	return nil
}

// Burn burns an existing stablecoin
func (sc *Stablecoin) Burn(ctx context.Context, amount *big.Int) error {
	// Burn the stablecoin
	tx, err := sc.makerClient.Burn(ctx, amount)
	if err != nil {
		return err
	}

	fmt.Printf("Burned %s stablecoin: %s\n", amount, tx.Hash().Hex())

	return nil
}

// GetAccountBalance returns the balance of an account in the stablecoin
func (sc *Stablecoin) GetAccountBalance(ctx context.Context, account common.Address) (*big.Int, error) {
	// Get the account's balance in the stablecoin
	balance, err := sc.makerClient.GetAccountBalance(ctx, account)
	if err != nil {
		return nil, err
	}

	return balance, nil
}

// GetStablecoinPrice returns the price of the stablecoin in terms of a fiat currency
func (sc *Stablecoin) GetStablecoinPrice(ctx context.Context) (*big.Int, error) {
	// Get the stablecoin's price in terms of a fiat currency
	price, err := sc.makerClient.GetStablecoinPrice(ctx)
	if err != nil {
		return nil, err
	}

	return price, nil
}
