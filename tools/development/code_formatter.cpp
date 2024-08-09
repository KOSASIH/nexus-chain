#include <clang/Format/Format.h>
#include <clang/Tooling/Tooling.h>

int main(int argc, const char **argv) {
    // Create a clang format style
    clang::format::FormatStyle style = clang::format::getLLVMStyle();

    // Create a file to format
    std::string fileContent = "..."; // read file content here

    // Format the file content
    std::string formattedContent = clang::format::reformat(fileContent, style);

    // Write the formatted content back to the file
    std::ofstream file("formatted_file.cpp");
    file << formattedContent;
    file.close();

    return 0;
}
