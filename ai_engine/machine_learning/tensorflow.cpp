#include <tensorflow/cc/ops/standard_ops.h>
#include <tensorflow/cc/saved_model/loader.h>
#include <tensorflow/cc/saved_model/tag_constants.h>

class TensorFlowModel {
public:
    TensorFlowModel(std::string modelPath) : modelPath(modelPath) {
        // Load the TensorFlow model
        tensorflow::NewSession(tensorflow::SessionOptions(), &session);
        tensorflow::LoadSavedModel(session, {tensorflow::kSavedModelTagServe}, modelPath);
    }

    std::string predict(std::string input) {
        // Create a TensorFlow tensor from the input
        tensorflow::Tensor inputTensor(tensorflow::DT_STRING, tensorflow::TensorShape({1}));
        inputTensor.scalar<std::string>()() = input;

        // Run the model
        std::vector<tensorflow::Tensor> outputs;
        session->Run({inputTensor}, {"output"}, {}, &outputs);

        // Get the output
        tensorflow::Tensor outputTensor = outputs[0];
        std::string output = outputTensor.scalar<std::string>()();

        return output;
    }

private:
    std::string modelPath;
    tensorflow::Session* session;
};

int main() {
    TensorFlowModel model("model.pb");
    std::string input = "input data";
    std::string output = model.predict(input);
    std::cout << "Predicted output: " << output << std::endl;
    return 0;
}
