package main

import (
	"fmt"
	"log"

	"github.com/nexus-chain/nexus-chain/chain"
	"github.com/nexus-chain/nexus-chain/consensus"
	"github.com/nexus-chain/nexus-chain/network"
	"github.com/nexus-chain/nexus-chain/smartcontract"
	"github.com/nexus-chain/nexus-chain/wallet"
)

func main() {
	// Create a new blockchain instance
	bc := chain.NewBlockchain(
		consensus.NewProofOfWork(big.NewInt(10)),
		network.NewTCPNetwork("localhost:8080"),
		smartcontract.NewSimpleSmartContract(),
		wallet.NewSimpleWallet(),
	)

	// Create a new block and add it to the blockchain
	block := chain.Block{
		Header: chain.BlockHeader{
			Timestamp: 1643723400,
			Height:    1,
		},
		Transactions: []chain.Transaction{
			{
				From:   "Alice",
				To:     "Bob",
				Amount: big.NewInt(5),
			},
		},
	}
	bc.AddBlock(block)

	// Create a new transaction and send it to the network
	tx := chain.Transaction{
		From:   "Bob",
		To:     "Charlie",
		Amount: big.NewInt(3),
	}
	bc.Network.SendMessage(tx.Hash())

	// Receive the transaction from the network
	receivedTx, err := bc.Network.ReceiveMessage()
	if err != nil {
		log.Fatal(err)
	}

	// Execute the transaction on the smart contract
	err = bc.SmartContractEngine.Execute(chain.Transaction{
		From:   "Bob",
		To:     "Charlie",
		Amount: big.NewInt(3),
	})
	if err != nil {
		log.Fatal(err)
	}

	// Add the transaction to the wallet
	err = bc.Wallet.ReceiveTransaction(tx)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Blockchain height:", bc.Height)
	fmt.Println("Last block hash:", bc.CurrentBlock.Hash())
}
