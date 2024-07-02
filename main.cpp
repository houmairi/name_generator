#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>

class AustrianDataGenerator {
private:
    std::mt19937 rng;
    std::vector<std::string> firstNames = {"Anna", "Michael", "Lisa", "Markus", "Sarah", "Thomas", "Julia", "Andreas", "Maria", "Daniel"};
    std::vector<std::string> lastNames = {"Müller", "Gruber", "Wagner", "Pichler", "Bauer", "Steiner", "Moser", "Mayer", "Hofer", "Leitner"};

    std::string generateName() {
        std::uniform_int_distribution<> firstDist(0, firstNames.size() - 1);
        std::uniform_int_distribution<> lastDist(0, lastNames.size() - 1);
        return firstNames[firstDist(rng)] + " " + lastNames[lastDist(rng)];
    }

    std::string generateBirthDate() {
        std::uniform_int_distribution<> yearDist(1950, 2003);
        std::uniform_int_distribution<> monthDist(1, 12);
        std::uniform_int_distribution<> dayDist(1, 28);  // Simplified, doesn't account for different month lengths
        int year = yearDist(rng);
        int month = monthDist(rng);
        int day = dayDist(rng);
        return std::to_string(day) + ":" + std::to_string(month) + ":" + std::to_string(year);
    }

    std::string generatePassword() {
        const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()";
        std::uniform_int_distribution<> dist(0, chars.size() - 1);
        std::string password;
        for (int i = 0; i < 12; ++i) {
            password += chars[dist(rng)];
        }
        return password;
    }

    std::string generateAustrianPhone() {
        std::vector<std::string> prefixes = {"650", "660", "664", "676", "699", "680", "681"};
        std::uniform_int_distribution<> prefix_dist(0, prefixes.size() - 1);
        std::uniform_int_distribution<> number_dist(1000000, 9999999);
        return prefixes[prefix_dist(rng)] + std::to_string(number_dist(rng));
    }

public:
    AustrianDataGenerator() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

    void generateData(int count, const std::string& filename) {
        std::ofstream outFile(filename + ".txt");
        for (int i = 0; i < count; ++i) {
            std::string name = generateName();
            std::string birthDate = generateBirthDate();
            std::string password = generatePassword();
            std::string phone = generateAustrianPhone();

            outFile << "Name: " << name << std::endl;
            outFile << "Birth Date: " << birthDate << std::endl;
            outFile << "Password: " << password << std::endl;
            outFile << "Phone: " << phone << std::endl;
            outFile << std::endl;
        }
    }
};

int main() {
    AustrianDataGenerator generator;
    int count;
    std::string filename;

    std::cout << "Enter number of records to generate: ";
    std::cin >> count;
    std::cout << "Enter output filename (without .txt extension): ";
    std::cin >> filename;

    generator.generateData(count, filename);

    std::cout << "Data generated and saved to " << filename << ".txt" << std::endl;
    return 0;
}