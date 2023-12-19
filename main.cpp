#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

class HashTable {
private:
    size_t tableSize;
    std::vector<std::string> hashTable;

    size_t customHash(const std::string& str) {
        const int p = 31; // Простое число p для хеширования
        size_t hashValue = 0;

        for (char c : str) {
            hashValue = (hashValue * p + c) % tableSize;
        }

        return hashValue;
    }

public:
    HashTable(size_t size) : tableSize(size), hashTable(size, "") {}

    bool insert(const std::string& word) {
        size_t hashValue = customHash(word);
        size_t initialIndex = hashValue;

        do {
            if (hashTable[hashValue] == "") {
                hashTable[hashValue] = word;
                return true;
            }
            hashValue = (hashValue + 1) % tableSize;
        } while (hashValue != initialIndex);

        return false; // Нет свободных ячеек для вставки
    }

    void writeToFile(const std::string& filename) {
        std::ofstream outputFile(filename); // Имя файла для записи хеш-таблицы

        if (!outputFile.is_open()) {
            std::cout << "Не удалось открыть файл для записи.\n";
            return;
        }

        for (size_t i = 0; i < tableSize; ++i) {
            if (hashTable[i] != "") {
                outputFile << "Хеш " << i << ": " << hashTable[i] << std::endl;
            }
        }

        outputFile.close();
        std::cout << "Хеш-таблица успешно записана в " << filename << std::endl;
    }
};

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    const size_t tableSize = 1000; // Размер хеш-таблицы

    std::ifstream inputFile("input.txt"); // Замените "input.txt" на имя вашего файла с текстом

    if (!inputFile.is_open()) {
        std::cout << "Не удалось открыть входной файл.\n";
        return 1;
    }

    HashTable hashTable(tableSize);

    std::string word;
    while (inputFile >> word) {
        hashTable.insert(word);
    }

    inputFile.close();

    hashTable.writeToFile("output.txt"); // Имя файла для записи хеш-таблицы

    return 0;
}
