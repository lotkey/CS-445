#include <filesystem>
#include <iostream>
#include <set>
#include <string>

int main() {
    const std::filesystem::path test_data_path = "./testData/";
    const std::string output_path = "./testOutputs/";

    std::set<std::string> files;
    for (const auto &entry :
         std::filesystem::directory_iterator(test_data_path)) {
        if (entry.is_regular_file()) {
            auto extension = entry.path().extension();
            std::string filename = entry.path().filename().string();
            if (extension == ".out") {
                files.insert(filename.substr(0, filename.find_last_of(".")));
            }
        }
    }

    for (const auto &file : files) {
        std::string command =
            "./test.sh " + file + " > " + output_path + file + ".out";
        system(command.c_str());
    }
}