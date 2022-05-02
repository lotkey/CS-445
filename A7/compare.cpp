#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string line,
                               const std::vector<char>& separators);
size_t find_first_of(const std::string& word, const std::vector<char>& chars);

int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "Not enough arguments" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename1 = argv[1];
    std::string filename2 = argv[2];
    std::vector<std::string> lines1;
    std::vector<std::string> lines2;
    std::string line;

    std::ifstream infile(filename1);
    while (std::getline(infile, line)) {
        if (!line.empty() && line[0] != '*') { lines1.push_back(line); }
    }

    infile.close();
    infile.open(filename2);
    while (std::getline(infile, line)) {
        if (!line.empty() && line[0] != '*') { lines2.push_back(line); }
    }

    while (filename1.size() != filename2.size()) {
        if (filename1.size() < filename2.size()) {
            filename1 += " ";
        } else if (filename1.size() > filename2.size()) {
            filename2 += " ";
        }
    }

    int maxSize = lines1.size();
    if (lines2.size() > maxSize) { maxSize = lines2.size(); }
    const std::vector<char> delimiters = {
        ' ', '\t', '\n', '\v', '\r', '\f', ':'};

    bool different = false;

    for (int i = 0; i < maxSize; i++) {
        if (different) {
            std::getline(std::cin, line);
            different = false;
        }

        if (line == "exit") { return EXIT_SUCCESS; }

        if (lines1.size() > i && lines2.size() > i) {
            auto words1 = split(lines1[i], delimiters);
            auto words2 = split(lines2[i], delimiters);

            if (words1.size() >= 1 && words1[0] != words2[0]) {
                std::cout << "Different instruction numbers:" << std::endl;
                std::cout << filename1 << ":\t" << words1[0] << std::endl;
                std::cout << filename2 << ":\t" << words2[0] << std::endl;
                different = true;
            }
            if (words1.size() >= 2 && words1[1] != words2[1]) {
                std::cout << "Different instructions:" << std::endl;
                std::cout << filename1 << ":\t" << words1[1] << std::endl;
                std::cout << filename2 << ":\t" << words2[1] << std::endl;
                different = true;
            }
            if (words1.size() >= 3 && words1[2] != words2[2]) {
                std::cout << "Different args:" << std::endl;
                std::cout << filename1 << ":\t" << words1[2] << std::endl;
                std::cout << filename2 << ":\t" << words2[2] << std::endl;
                different = true;
            }
            if (different) {
                std::cout << "Difference at instruction address: " << words1[0]
                          << ", " << words2[0] << std::endl;
            }
        } else if (lines1.size() > i) {
            std::cout << filename1 << ":\t" << lines1[i] << std::endl;
            std::cout << filename2 << ":" << std::endl;
            different = true;
        } else {
            std::cout << filename1 << ":" << std::endl;
            std::cout << filename2 << ":\t" << lines2[i] << std::endl;
            different = true;
        }
    }
    std::cout << "End of files." << std::endl;
}

std::vector<std::string> split(std::string line,
                               const std::vector<char>& separators)
{
    std::vector<std::string> words;
    size_t pos = 0;
    while ((pos = find_first_of(line, separators)) != std::string::npos) {
        std::string word = line.substr(0, pos);
        if (!word.empty()) { words.push_back(line.substr(0, pos)); }
        line.erase(0, pos + 1);
    }

    return words;
}

size_t find_first_of(const std::string& word, const std::vector<char>& chars)
{
    for (size_t i = 0; i < word.size(); i++) {
        for (auto c : chars) {
            if (word[i] == c) { return i; }
        }
    }

    return std::string::npos;
}