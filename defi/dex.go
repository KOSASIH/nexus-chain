package defi

import (
	"context"
	"fmt"
	"math/big"

	"github.com/uniswap/uniswap-go"
	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
)

// Dex represents a decentralized exchange
type Dex struct {
	uniswapClient *uniswap.Client
}

// NewDex returns a new instance of Dex
func NewDex(url string) (*Dex, error) {
	client, err := uniswap.NewClient(url)
	if err != nil {
		return nil, err
	}

	return &Dex{uniswapClient: client}, nil
}

// GetTokenPrice returns the price of a token on the DEX
func (dex *Dex) GetTokenPrice(ctx context.Context, token common.Address) (*big.Int, error) {
	// Get the token's price on the DEX
	price, err := dex.uniswapClient.GetTokenPrice(ctx, token)
	if err != nil {
		return nil, err
	}

	return price, nil
}

// Swap swaps two tokens on the DEX
func (dex *Dex) Swap(ctx context.Context, tokenIn common.Address, amountIn *big.Int, tokenOut common.Address, amountOut *big.Int) error {
	// Get the token pair
	tokenPair, err := dex.uniswapClient.GetTokenPair(ctx, tokenIn, tokenOut)
	if err != nil {
		return err
	}

	// Swap the tokens
	tx, err := dex.uniswapClient.Swap(ctx, tokenPair, amountIn, amountOut)
	if err != nil {
		return err
	}

	fmt.Printf("Swapped %s for %s: %s\n", amountIn, amountOut, tx.Hash().Hex())

	return nil
}

// GetAccountBalance returns the balance of an account on the DEX
func (dex *Dex) GetAccountBalance(ctx context.Context, account common.Address) (*big.Int, error) {
	// Get the account's balance on the DEX
	balance, err := dex.uniswapClient.GetAccountBalance(ctx, account)
	if err != nil {
		return nil, err
	}

	return balance, nil
}
