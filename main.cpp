#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>

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
        std::uniform_int_distribution<> dayDist(1, 28);
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
        std::vector<std::string> prefixes = {"0650", "0660", "0664", "0676", "0699", "0680", "0681"};
        std::uniform_int_distribution<> prefix_dist(0, prefixes.size() - 1);
        std::uniform_int_distribution<> number_dist(1000000, 9999999);
        return prefixes[prefix_dist(rng)] + std::to_string(number_dist(rng));
    }

    std::string generateEmailPrefix(const std::string& name) {
        std::string email = name;
        std::transform(email.begin(), email.end(), email.begin(),
            [](unsigned char c) { return std::tolower(c); });
        std::replace(email.begin(), email.end(), ' ', '.');
        
        // Add random variations
        std::uniform_int_distribution<> varDist(0, 3);
        std::uniform_int_distribution<> numDist(0, 999);
        
        switch(varDist(rng)) {
            case 0: // Add a random number
                email += std::to_string(numDist(rng));
                break;
            case 1: // Use only first name initial and last name
                email = email[0] + email.substr(email.find('.') + 1);
                break;
            case 2: // Swap first and last name
                {
                    size_t dotPos = email.find('.');
                    if (dotPos != std::string::npos) {
                        email = email.substr(dotPos + 1) + "." + email.substr(0, dotPos);
                    }
                }
                break;
            default: // Leave as is
                break;
        }
        
        return email;
    }

    std::string escapeCSV(const std::string& str) {
        if (str.find(',') != std::string::npos || str.find('"') != std::string::npos) {
            std::ostringstream result;
            result << '"';
            for (char c : str) {
                if (c == '"') result << '"';
                result << c;
            }
            result << '"';
            return result.str();
        }
        return str;
    }

public:
    AustrianDataGenerator() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

    void generateData(int count, const std::string& filename) {
        std::ofstream outFile(filename + ".csv");
        
        // Write CSV header
        outFile << "Name,EmailPrefix,BirthDate,Password,Phone\n";

        for (int i = 0; i < count; ++i) {
            std::string name = generateName();
            std::string emailPrefix = generateEmailPrefix(name);
            std::string birthDate = generateBirthDate();
            std::string password = generatePassword();
            std::string phone = generateAustrianPhone();

            outFile << escapeCSV(name) << ","
                    << escapeCSV(emailPrefix) << ","
                    << escapeCSV(birthDate) << ","
                    << escapeCSV(password) << ","
                    << escapeCSV(phone) << "\n";
        }
    }
};

int main() {
    AustrianDataGenerator generator;
    int count;
    std::string filename;

    std::cout << "Enter number of records to generate: ";
    std::cin >> count;
    std::cout << "Enter output filename (without .csv extension): ";
    std::cin >> filename;

    generator.generateData(count, filename);

    std::cout << "Data generated and saved to " << filename << ".csv" << std::endl;
    return 0;
}