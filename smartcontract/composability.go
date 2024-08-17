package smartcontract

import (
	"context"
	"fmt"
	"math/big"

	"github.com/OpenZeppelin/openzeppelin-solidity/contracts/modular/ModularContract.sol"
	"github.com/ethereum/go-ethereum/accounts"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
)

// ModularContract represents a modular smart contract
type ModularContract struct {
	contractAddress common.Address
	modules         []common.Address
}

// NewModularContract returns a new instance of ModularContract
func NewModularContract(contractAddress common.Address, modules []common.Address) (*ModularContract, error) {
	// Create a new instance of the modular contract
	contract, err := ModularContract.NewModularContract(contractAddress, modules)
	if err != nil {
		return nil, err
	}

	return &ModularContract{
		contractAddress: contractAddress,
		modules:         modules,
	}, nil
}

// AddModule adds a new module to the contract
func (mc *ModularContract) AddModule(ctx context.Context, newModule common.Address) error {
	// Add the new module to the contract
	tx, err := mc.contractAddress.Call(ctx, "addModule", newModule)
	if err != nil {
		return err
	}

	fmt.Printf("Added new module to contract: %s\n", tx.Hash().Hex())

	return nil
}

// RemoveModule removes a module from the contract
func (mc *ModularContract) RemoveModule(ctx context.Context, module common.Address) error {
	// Remove the module from the contract
	tx, err := mc.contractAddress.Call(ctx, "removeModule", module)
	if err != nil {
		return err
	}

	fmt.Printf("Removed module from contract: %s\n", tx.Hash().Hex())

	return nil
}

// GetModules returns the current modules of the contract
func (mc *ModularContract) GetModules(ctx context.Context) ([]common.Address, error) {
	// Get the current modules of the contract
	modules, err := mc.contractAddress.Call(ctx, "getModules")
	if err != nil {
		return nil, err
	}

	return modules, nil
}
