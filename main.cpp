#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class NameGenerator {
private:
    std::vector<std::string> malePrefixes;
    std::vector<std::string> maleSuffixes;
    std::vector<std::string> femalePrefixes;
    std::vector<std::string> femaleSuffixes;
    std::mt19937 rng;

    void initializeSyllables() {
        malePrefixes = {"Al", "Ber", "Car", "Dan", "Ed", "Fred", "Gre", "Har"};
        maleSuffixes = {"en", "on", "an", "ard", "in", "ley", "son", "ton"};
        femalePrefixes = {"Am", "Bri", "Car", "Dan", "El", "Fion", "Gra", "Han"};
        femaleSuffixes = {"a", "elle", "ina", "lyn", "ey", "ie", "anna", "beth"};
    }

    std::string generateSyllable(const std::vector<std::string>& syllables) {
        std::uniform_int_distribution<> dist(0, syllables.size() - 1);
        return syllables[dist(rng)];
    }

public:
    NameGenerator() : rng(std::random_device{}()) {
        initializeSyllables();
    }

    std::string generateName(bool isMale) {
        const auto& prefixes = isMale ? malePrefixes : femalePrefixes;
        const auto& suffixes = isMale ? maleSuffixes : femaleSuffixes;
        
        std::string name = generateSyllable(prefixes) + generateSyllable(suffixes);
        name[0] = std::toupper(name[0]);  // Capitalize the first letter
        return name;
    }

    void generateNames(bool isMale, int count, const std::string& filename) {
        std::ofstream outFile(filename);
        for (int i = 0; i < count; ++i) {
            outFile << generateName(isMale) << std::endl;
        }
    }
};

int main() {
    NameGenerator generator;
    char gender;
    int count;
    std::string filename;

    std::cout << "Enter gender (M/F): ";
    std::cin >> gender;
    std::cout << "Enter number of names to generate: ";
    std::cin >> count;
    std::cout << "Enter output filename: ";
    std::cin >> filename;

    bool isMale = (std::toupper(gender) == 'M');
    generator.generateNames(isMale, count, filename);

    std::cout << "Names generated and saved to " << filename << std::endl;
    return 0;
}