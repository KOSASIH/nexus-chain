package defi

import (
	"context"
	"fmt"
	"math/big"

	"github.com/compound-finance/compound-go"
	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
)

// LendingProtocol represents a lending protocol
type LendingProtocol struct {
	compoundClient *compound.Client
}

// NewLendingProtocol returns a new instance of LendingProtocol
func NewLendingProtocol(url string) (*LendingProtocol, error) {
	client, err := compound.NewClient(url)
	if err != nil {
		return nil, err
	}

	return &LendingProtocol{compoundClient: client}, nil
}

// Lend lends an asset to the protocol
func (lp *LendingProtocol) Lend(ctx context.Context, asset common.Address, amount *big.Int) error {
	// Get the asset's underlying token
	token, err := lp.compoundClient.GetToken(ctx, asset)
	if err != nil {
		return err
	}

	// Lend the asset to the protocol
	tx, err := lp.compoundClient.Lend(ctx, token, amount)
	if err != nil {
		return err
	}

	fmt.Printf("Lent %s to the protocol: %s\n", amount, tx.Hash().Hex())

	return nil
}

// Borrow borrows an asset from the protocol
func (lp *LendingProtocol) Borrow(ctx context.Context, asset common.Address, amount *big.Int) error {
	// Get the asset's underlying token
	token, err := lp.compoundClient.GetToken(ctx, asset)
	if err != nil {
		return err
	}

	// Borrow the asset from the protocol
	tx, err := lp.compoundClient.Borrow(ctx, token, amount)
	if err != nil {
		return err
	}

	fmt.Printf("Borrowed %s from the protocol: %s\n", amount, tx.Hash().Hex())

	return nil
}

// GetAccountBalance returns the balance of an account in the lending protocol
func (lp *LendingProtocol) GetAccountBalance(ctx context.Context, account common.Address) (*big.Int, error) {
	// Get the account's balance in the protocol
	balance, err := lp.compoundClient.GetAccountBalance(ctx, account)
	if err != nil {
		return nil, err
	}

	return balance, nil
}
