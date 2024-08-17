package governance

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
	"github.com/aragon/aragonOS-go/aragon"
)

// GovernanceClient represents a governance client
type GovernanceClient struct {
	client  *ethclient.Client
	aragon  *aragon.Aragon
	dao     *aragon.DAO
	voting  *aragon.Voting
	proposal *aragon.Proposal
}

// NewGovernanceClient returns a new instance of GovernanceClient
func NewGovernanceClient(url string, aragonAddress common.Address, daoAddress common.Address, votingAddress common.Address, proposalAddress common.Address) (*GovernanceClient, error) {
	client, err := ethclient.Dial(url)
	if err != nil {
		return nil, err
	}

	aragonClient, err := aragon.NewAragon(client, aragonAddress)
	if err != nil {
		return nil, err
	}

	daoClient, err := aragon.NewDAO(client, daoAddress)
	if err != nil {
		return nil, err
	}

	votingClient, err := aragon.NewVoting(client, votingAddress)
	if err != nil {
		return nil, err
	}

	proposalClient, err := aragon.NewProposal(client, proposalAddress)
	if err != nil {
		return nil, err
	}

	return &GovernanceClient{
		client:  client,
		aragon:  aragonClient,
		dao:     daoClient,
		voting:  votingClient,
		proposal: proposalClient,
	}, nil
}

// CreateProposal creates a new proposal
func (gc *GovernanceClient) CreateProposal(title string, description string, choices []string) (*aragon.Proposal, error) {
	return gc.proposal.CreateProposal(context.Background(), title, description, choices)
}

// VoteOnProposal votes on a proposal
func (gc *GovernanceClient) VoteOnProposal(proposalID *big.Int, choice int) error {
	return gc.voting.VoteOnProposal(context.Background(), proposalID, choice)
}

// GetProposal returns a proposal
func (gc *GovernanceClient) GetProposal(proposalID *big.Int) (*aragon.Proposal, error) {
	return gc.proposal.GetProposal(context.Background(), proposalID)
}

// GetVotingResults returns the voting results
func (gc *GovernanceClient) GetVotingResults(proposalID *big.Int) (*aragon.VotingResults, error) {
	return gc.voting.GetVotingResults(context.Background(), proposalID)
}

// ExecuteProposal executes a proposal
func (gc *GovernanceClient) ExecuteProposal(proposalID *big.Int) error {
	return gc.dao.ExecuteProposal(context.Background(), proposalID)
}

// GetDAO returns the DAO
func (gc *GovernanceClient) GetDAO() (*aragon.DAO, error) {
	return gc.dao.GetDAO(context.Background())
}

// GetVoting returns the voting contract
func (gc *GovernanceClient) GetVoting() (*aragon.Voting, error) {
	return gc.voting.GetVoting(context.Background())
}

// GetProposalCount returns the number of proposals
func (gc *GovernanceClient) GetProposalCount() (*big.Int, error) {
	return gc.proposal.GetProposalCount(context.Background())
}
