from models.neural_network import NeuralNetwork
from data_loader import DataLoader

class Trainer:
    def __init__(self, data_loader, neural_network, epochs=10):
        self.data_loader = data_loader
        self.neural_network = neural_network
        self.epochs = epochs

    def train(self):
        for epoch in range(self.epochs):
            X_batch, y_batch = self.data_loader.get_batch()
            self.neural_network.train(X_batch, y_batch)
            print(f'Epoch {epoch+1}, Loss: {self.neural_network.model.loss:.4f}, Accuracy: {self.neural_network.model.accuracy:.4f}')

    def evaluate(self):
        X_test, y_test = self.data_loader.data[2:]
        loss, accuracy = self.neural_network.model.evaluate(X_test, y_test)
        print(f'Test Loss: {loss:.4f}, Test Accuracy: {accuracy:.4f}')
