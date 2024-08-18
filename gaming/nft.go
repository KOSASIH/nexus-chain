package gaming

import (
	"github.com/opensea/opensea-go"
	"github.com/rarible/rarible-go"
)

// NFTMarketplace represents an NFT marketplace
type NFTMarketplace struct {
	opensea *opensea.Client
	rarible *rarible.Client
}

// NewNFTMarketplace returns a new instance of NFTMarketplace
func NewNFTMarketplace(openseaAPIKey string, raribleAPIKey string) (*NFTMarketplace, error) {
	openseaClient, err := opensea.NewClient(openseaAPIKey)
	if err != nil {
		return nil, err
	}

	raribleClient, err := rarible.NewClient(raribleAPIKey)
	if err != nil {
		return nil, err
	}

	return &NFTMarketplace{
		opensea: openseaClient,
		rarible: raribleClient,
	}, nil
}

// CreateNFT creates a new NFT
func (nm *NFTMarketplace) CreateNFT(name string, description string, image string) (*NFT, error) {
	var nft *NFT
	var err error

	if nm.opensea != nil {
		nft, err = nm.opensea.CreateNFT(name, description, image)
	} else if nm.rarible != nil {
		nft, err = nm.rarible.CreateNFT(name, description, image)
	} else {
		return nil, fmt.Errorf("no NFT marketplace available")
	}

	return nft, err
}

// GetNFT returns an NFT by ID
func (nm *NFTMarketplace) GetNFT(id string) (*NFT, error) {
	var nft *NFT
	var err error

	if nm.opensea != nil {
		nft, err = nm.opensea.GetNFT(id)
	} else if nm.rarible != nil {
		nft, err = nm.rarible.GetNFT(id)
	} else {
		return nil, fmt.Errorf("no NFT marketplace available")
	}

	return nft, err
}

// UpdateNFT updates an NFT
func (nm *NFTMarketplace) UpdateNFT(id string, name string, description string, image string) (*NFT, error) {
	var nft *NFT
	var err error

	if nm.opensea != nil {
		nft, err = nm.opensea.UpdateNFT(id, name, description, image)
	} else if nm.rarible != nil {
		nft, err = nm.rarible.UpdateNFT(id, name, description, image)
	} else {
		return nil, fmt.Errorf("no NFT marketplace available")
	}

	return nft, err
}

// DeleteNFT deletes an NFT
func (nm *NFTMarketplace) DeleteNFT(id string) error {
	var err error

	if nm.opensea != nil {
		err = nm.opensea.DeleteNFT(id)
	} else if nm.rarible != nil {
		err = nm.rarible.DeleteNFT(id)
	} else {
		return fmt.Errorf("no NFT marketplace available")
	}

	return err
}

type NFT struct {
	ID          string `json:"id"`
	Name        string `json:"name"`
	Description string `json:"description"`
	Image       string `json:"image"`
}
