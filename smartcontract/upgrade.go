package smartcontract

import (
	"context"
	"fmt"
	"math/big"

	"github.com/OpenZeppelin/openzeppelin-solidity/contracts/upgradeable/UpgradeableContract.sol"
	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
)

// UpgradeableContract represents an upgradeable smart contract
type UpgradeableContract struct {
	contractAddress common.Address
	proxyAddress    common.Address
	implementation common.Address
}

// NewUpgradeableContract returns a new instance of UpgradeableContract
func NewUpgradeableContract(proxyAddress common.Address, implementation common.Address) (*UpgradeableContract, error) {
	// Create a new instance of the upgradeable contract
	contract, err := UpgradeableContract.NewUpgradeableContract(proxyAddress, implementation)
	if err != nil {
		return nil, err
	}

	return &UpgradeableContract{
		contractAddress: contract.Address(),
		proxyAddress:    proxyAddress,
		implementation: implementation,
	}, nil
}

// Upgrade upgrades the contract to a new implementation
func (uc *UpgradeableContract) Upgrade(ctx context.Context, newImplementation common.Address) error {
	// Upgrade the contract to the new implementation
	tx, err := uc.proxyAddress.Call(ctx, "upgrade", newImplementation)
	if err != nil {
		return err
	}

	fmt.Printf("Upgraded contract to new implementation: %s\n", tx.Hash().Hex())

	return nil
}

// GetImplementation returns the current implementation of the contract
func (uc *UpgradeableContract) GetImplementation(ctx context.Context) (common.Address, error) {
	// Get the current implementation of the contract
	implementation, err := uc.proxyAddress.Call(ctx, "implementation")
	if err != nil {
		return common.Address{}, err
	}

	return implementation, nil
}
