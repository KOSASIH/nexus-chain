#include "blockchain_based_artificial_life.h"
#include "blockchain_interface.h"
#include "artificial_life_engine.h"

BlockchainBasedArtificialLife::BlockchainBasedArtificialLife() {
    // Initialize blockchain-based artificial life system
    this->blockchain_interface = new BlockchainInterface();
    this->artificial_life_engine = new ArtificialLifeEngine();
}

void BlockchainBasedArtificialLife::createOrganism() {
    // Create a new organism on the blockchain
    std::string organism_id = blockchain_interface->createNewOrganism();
    artificial_life_engine->createOrganism(organism_id);
}

void BlockchainBasedArtificialLife::evolveOrganism() {
    // Evolve an organism on the blockchain
    std::string organism_id = blockchain_interface->getOrganismId();
    artificial_life_engine->evolveOrganism(organism_id);
    blockchain_interface->updateOrganism(organism_id, artificial_life_engine->getOrganismState());
}

void BlockchainBasedArtificialLife::interactWithEnvironment() {
    // Interact with the environment on the blockchain
    std::string organism_id = blockchain_interface->getOrganismId();
    artificial_life_engine->interactWithEnvironment(organism_id);
    blockchain_interface->updateOrganism(organism_id, artificial_life_engine->getOrganismState());
}

void BlockchainBasedArtificialLife::reproduce() {
    // Reproduce an organism on the blockchain
    std::string parent_id = blockchain_interface->getOrganismId();
    std::string child_id = blockchain_interface->createNewOrganism();
    artificial_life_engine->reproduce(parent_id, child_id);
    blockchain_interface->updateOrganism(child_id, artificial_life_engine->getOrganismState());
}
