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
	"github.com/daostack/daostack-go/dao"
)

// VotingClient represents a voting client
type VotingClient struct {
	client  *ethclient.Client
	dao     *dao.DAO
	voting  *dao.Voting
	proposal *dao.Proposal
}

// NewVotingClient returns a new instance of VotingClient
func NewVotingClient(url string, daoAddress common.Address, votingAddress common.Address, proposalAddress common.Address) (*VotingClient, error) {
	client, err := ethclient.Dial(url)
	if err != nil {
		return nil, err
	}

	daoClient, err := dao.NewDAO(client, daoAddress)
	if err != nil {
		return nil, err
	}

	votingClient, err := dao.NewVoting(client, votingAddress)
	if err != nil {
		return nil, err
	}

	proposalClient, err := dao.NewProposal(client, proposalAddress)
	if err != nil {
		return nil, err
	}

	return &VotingClient{
		client:  client,
		dao:     daoClient,
		voting:  votingClient,
		proposal: proposalClient,
	}, nil
}

// CreateProposal creates a new proposal
func (vc *VotingClient) CreateProposal(title string, description string, choices []string) (*dao.Proposal, error) {
	return vc.proposal.CreateProposal(context.Background(), title, description, choices)
}

// VoteOnProposal votes on a proposal
func (vc *VotingClient) VoteOnProposal(proposalID *big.Int, choice int) error {
	return vc.voting.VoteOnProposal(context.Background(), proposalID, choice)
}

// GetProposal returns a proposal
func (vc *VotingClient) GetProposal(proposalID *big.Int) (*dao.Proposal, error) {
	return vc.proposal.GetProposal(context.Background(), proposalID)
}

// GetVotingResults returns the voting results
func (vc *VotingClient) GetVotingResults(proposalID *big.Int) (*dao.VotingResults, error) {
	return vc.voting.GetVotingResults(context.Background(), proposalID)
}
