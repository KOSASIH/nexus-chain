import os
import json
from typing import Dict, List
from web3 import Web3
from eth_utils import to_checksum_address
from pydantic import BaseModel
from tensorflow.keras.models import load_model
from nsca.models import NeuralNetwork
from nsca.data import TrainingData

class Analyzer(BaseModel):
    contract_address: str
    contract_abi: Dict[str, List[Dict[str, str]]]
    neural_network: NeuralNetwork
    training_data: TrainingData

    def __init__(self, contract_address: str, contract_abi: Dict[str, List[Dict[str, str]]]):
        super().__init__()
        self.contract_address = to_checksum_address(contract_address)
        self.contract_abi = contract_abi
        self.neural_network = NeuralNetwork()
        self.training_data = TrainingData()

    def analyze(self) -> Dict[str, str]:
        # Load the neural network model
        model = load_model("nsca/models/neural_network.h5")

        # Get the contract bytecode
        bytecode = Web3.eth.getCode(self.contract_address).hex()

        # Preprocess the bytecode
        bytecode = self.preprocess_bytecode(bytecode)

        # Make predictions using the neural network model
        predictions = model.predict(bytecode)

        # Postprocess the predictions
        results = self.postprocess_predictions(predictions)

        return results

    def preprocess_bytecode(self, bytecode: str) -> str:
        # Remove unnecessary characters from the bytecode
        bytecode = bytecode.replace("0x", "")

        # Convert the bytecode to a numerical representation
        bytecode = [int(bytecode[i:i+2], 16) for i in range(0, len(bytecode), 2)]

        # Normalize the bytecode
        bytecode = [byte / 255 for byte in bytecode]

        return bytecode

    def postprocess_predictions(self, predictions: List[float]) -> Dict[str, str]:
        # Convert the predictions to a dictionary
        results = {}

        # Add the contract address to the results
        results["contract_address"] = self.contract_address

        # Add the predictions to the results
        results["predictions"] = predictions

        return results

    def save_results(self, results: Dict[str, str]) -> None:
        # Save the results to a JSON file
        with open("results.json", "w") as f:
            json.dump(results, f)

    def load_results(self) -> Dict[str, str]:
        # Load the results from a JSON file
        with open("results.json", "r") as f:
            results = json.load(f)

        return results
