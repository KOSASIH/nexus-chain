#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>

class CheckerASTVisitor : public RecursiveASTVisitor<CheckerASTVisitor> {
public:
    bool VisitFunctionDecl(FunctionDecl *f) {
        // Get function name
        const auto name = f->getNameAsString();

        // Check if name contains _
        if (name.find("_") != std::string::npos) {
            // Get the diagnostic engine
            auto &DE = f->getASTContext().getDiagnostics();

            // Create custom error message
            auto diagID = DE.getCustomDiagID(DiagnosticsEngine::Error, "Function name contains `_`.");

            // Report our custom error
            DE.Report(f->getLocation(), diagID);
        }

        return true;
    }
};

int main(int argc, const char **argv) {
    // Create a clang tool instance
    clang::tooling::ClangTool tool("checker", argv[1]);

    // Create an AST consumer
    CheckerASTConsumer consumer;

    // Run the tool
    tool.run(&consumer);

    return 0;
}
