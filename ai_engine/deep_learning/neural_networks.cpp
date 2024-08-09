#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <vector>

typedef float Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;

class NeuralNetwork {
public:
    NeuralNetwork(std::vector<uint> topology, Scalar learningRate = Scalar(0.005));

    void propagateForward(RowVector& input);
    void propagateBackward(RowVector& output);
    void calcErrors(RowVector& output);
    void updateWeights();
    void train(std::vector<RowVector*> data);

    std::vector<RowVector*> neuronLayers;
    std::vector<RowVector*> cacheLayers;
    std::vector<RowVector*> deltas;
    std::vector<Matrix*> weights;
    Scalar learningRate;
};

NeuralNetwork::NeuralNetwork(std::vector<uint> topology, Scalar learningRate) {
    // Initialize the neural network with the given topology and learning rate
}

void NeuralNetwork::propagateForward(RowVector& input) {
    // Forward propagation of data through the neural network
}

void NeuralNetwork::propagateBackward(RowVector& output) {
    // Backward propagation of errors through the neural network
}

void NeuralNetwork::calcErrors(RowVector& output) {
    // Calculate the errors made by neurons in each layer
}

void NeuralNetwork::updateWeights() {
    // Update the weights of connections based on the errors
}

void NeuralNetwork::train(std::vector<RowVector*> data) {
    // Train the neural network with the given data
}
