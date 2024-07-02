#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class GermanNameGenerator {
private:
    std::vector<std::string> malePrefixes;
    std::vector<std::string> maleSuffixes;
    std::vector<std::string> femalePrefixes;
    std::vector<std::string> femaleSuffixes;
    std::vector<std::string> surnames;
    std::mt19937 rng;

    void initializeSyllables() {
        malePrefixes = {"Hein", "Frie", "Wolf", "Lud", "Ger", "Hans", "Die", "Karl"};
        maleSuffixes = {"rich", "helm", "gang", "wig", "hard", "ter", "trich", "mann"};
        femalePrefixes = {"An", "Mar", "Ger", "Hil", "Ing", "Eli", "Ur", "Chris"};
        femaleSuffixes = {"na", "gret", "trud", "de", "rid", "sa", "sula", "tina"};
        surnames = {"Müller", "Schmidt", "Schneider", "Fischer", "Weber", "Meyer", "Wagner", "Becker", "Hoffmann", "Schäfer"};
    }

    std::string generateSyllable(const std::vector<std::string>& syllables) {
        std::uniform_int_distribution<> dist(0, syllables.size() - 1);
        return syllables[dist(rng)];
    }

public:
    GermanNameGenerator() : rng(std::random_device{}()) {
        initializeSyllables();
    }

    std::string generateName(bool isMale) {
        const auto& prefixes = isMale ? malePrefixes : femalePrefixes;
        const auto& suffixes = isMale ? maleSuffixes : femaleSuffixes;
        
        std::string name = generateSyllable(prefixes) + generateSyllable(suffixes);
        name[0] = std::toupper(name[0]);  // Capitalize the first letter
        return name;
    }

    std::string generateSurname() {
        return generateSyllable(surnames);
    }

    void generateNames(bool isMale, int count, const std::string& filename) {
        std::ofstream outFile(filename + ".txt");
        for (int i = 0; i < count; ++i) {
            outFile << generateName(isMale) << ":" << generateSurname() << std::endl;
        }
    }
};

int main() {
    GermanNameGenerator generator;
    char gender;
    int count;
    std::string filename;

    std::cout << "Enter gender (M/F): ";
    std::cin >> gender;
    std::cout << "Enter number of names to generate: ";
    std::cin >> count;
    std::cout << "Enter output filename (without .txt extension): ";
    std::cin >> filename;

    bool isMale = (std::toupper(gender) == 'M');
    generator.generateNames(isMale, count, filename);

    std::cout << "German names generated and saved to " << filename << ".txt" << std::endl;
    return 0;
}