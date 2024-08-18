package interop

import (
	"github.com/cosmos/ibc-go/v3/modules/core/keeper"
	"github.com/polkadot-js/common/types"
)

// AtomicSwap represents a cross-chain atomic swap
type AtomicSwap struct {
	chainA  string
	chainB  string
	assetA  string
	assetB  string
	amountA uint64
	amountB uint64
}

// NewAtomicSwap returns a new instance of AtomicSwap
func NewAtomicSwap(chainA string, chainB string, assetA string, assetB string, amountA uint64, amountB uint64) *AtomicSwap {
	return &AtomicSwap{
		chainA:  chainA,
		chainB:  chainB,
		assetA:  assetA,
		assetB:  assetB,
		amountA: amountA,
		amountB: amountB,
	}
}

// Init initializes the atomic swap
func (as *AtomicSwap) Init() error {
	// Initialize IBC client for chain A
	ibcClientA, err := keeper.NewClient(as.chainA)
	if err != nil {
		return err
	}

	// Initialize IBC client for chain B
	ibcClientB, err := keeper.NewClient(as.chainB)
	if err != nil {
		return err
	}

	// Initialize Polkadot interoperability client for chain A
	polkadotClientA, err := types.NewClient(as.chainA)
	if err != nil {
		return err
	}

	// Initialize Polkadot interoperability client for chain B
	polkadotClientB, err := types.NewClient(as.chainB)
	if err != nil {
		return err
	}

	return nil
}

// Execute executes the atomic swap
func (as *AtomicSwap) Execute() error {
	// Create a new IBC packet for chain A
	packetA, err := ibcClientA.CreatePacket(as.assetA, as.amountA)
	if err != nil {
		return err
	}

	// Create a new IBC packet for chain B
	packetB, err := ibcClientB.CreatePacket(as.assetB, as.amountB)
	if err != nil {
		return err
	}

	// Send packet A to chain B using IBC
	err = ibcClientA.SendPacket(packetA, as.chainB)
	if err != nil {
		return err
	}

	// Send packet B to chain A using IBC
	err = ibcClientB.SendPacket(packetB, as.chainA)
	if err != nil {
		return err
	}

	// Verify the swap using Polkadot interoperability
	err = polkadotClientA.VerifySwap(as.assetA, as.amountA, as.chainB)
	if err != nil {
		return err
	}

	err = polkadotClientB.VerifySwap(as.assetB, as.amountB, as.chainA)
	if err != nil {
		return err
	}

	return nil
}

// Cancel cancels the atomic swap
func (as *AtomicSwap) Cancel() error {
	// Cancel the IBC packet for chain A
	err := ibcClientA.CancelPacket(as.assetA, as.amountA)
	if err != nil {
		return err
	}

	// Cancel the IBC packet for chain B
	err = ibcClientB.CancelPacket(as.assetB, as.amountB)
	if err != nil {
		return err
	}

	return nil
}
