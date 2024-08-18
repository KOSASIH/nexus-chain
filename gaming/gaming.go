package gaming

import (
	"github.com/unity3d-go/unity-go"
	"github.com/unrealengine-go/unreal-go"
)

// GamingPlatform represents a gaming platform
type GamingPlatform struct {
	unity  *unity.Client
	unreal *unreal.Client
}

// NewGamingPlatform returns a new instance of GamingPlatform
func NewGamingPlatform(unityAPIKey string, unrealAPIKey string) (*GamingPlatform, error) {
	unityClient, err := unity.NewClient(unityAPIKey)
	if err != nil {
		return nil, err
	}

	unrealClient, err := unreal.NewClient(unrealAPIKey)
	if err != nil {
		return nil, err
	}

	return &GamingPlatform{
		unity:  unityClient,
		unreal: unrealClient,
	}, nil
}

// CreateGame creates a new game
func (gp *GamingPlatform) CreateGame(name string, description string, genre string) (*Game, error) {
	var game *Game
	var err error

	if gp.unity != nil {
		game, err = gp.unity.CreateGame(name, description, genre)
	} else if gp.unreal != nil {
		game, err = gp.unreal.CreateGame(name, description, genre)
	} else {
		return nil, fmt.Errorf("no gaming platform available")
	}

	return game, err
}

// GetGame returns a game by ID
func (gp *GamingPlatform) GetGame(id string) (*Game, error) {
	var game *Game
	var err error

	if gp.unity != nil {
		game, err = gp.unity.GetGame(id)
	} else if gp.unreal != nil {
		game, err = gp.unreal.GetGame(id)
	} else {
		return nil, fmt.Errorf("no gaming platform available")
	}

	return game, err
}

// UpdateGame updates a game
func (gp *GamingPlatform) UpdateGame(id string, name string, description string, genre string) (*Game, error) {
	var game *Game
	var err error

	if gp.unity != nil {
		game, err = gp.unity.UpdateGame(id, name, description, genre)
	} else if gp.unreal != nil {
		game, err = gp.unreal.UpdateGame(id, name, description, genre)
	} else {
		return nil, fmt.Errorf("no gaming platform available")
	}

	return game, err
}

// DeleteGame deletes a game
func (gp *GamingPlatform) DeleteGame(id string) error {
	var err error

	if gp.unity != nil {
		err = gp.unity.DeleteGame(id)
	} else if gp.unreal != nil {
		err = gp.unreal.DeleteGame(id)
	} else {
		return fmt.Errorf("no gaming platform available")
	}

	return err
}

type Game struct {
	ID          string `json:"id"`
	Name        string `json:"name"`
	Description string `json:"description"`
	Genre       string `json:"genre"`
}
