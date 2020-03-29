#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/stat.h>

std::vector<std::string> dictionary;

void CreateDictionary(std::string file)
{
    std::cout << std::string("Creating dictionary for '") + file + "'..."
              << "\n";
    std::ifstream inFile(file);

    std::ofstream dictFile;
    remove((file + ".dict").c_str());
    dictFile.open(file + ".dict");

    dictionary.push_back(" ");

    for (std::string line; getline(inFile, line);)
    {
        std::istringstream iss(line);
        do
        {
            std::string word;
            iss >> word;
            if (std::find(dictionary.begin(), dictionary.end(), word) == dictionary.end())
            {
                dictionary.push_back(word);
                dictFile << word << "\n";
            }
        } while (iss);
    }
    inFile.close();
    dictFile.close();
}

void CompressFile(std::string file)
{
    std::cout << std::string("Compressing file '") + file + "'..."
              << "\n";
    std::ofstream compressedFile;
    remove((file + ".zac").c_str());
    compressedFile.open(file + ".zac");

    std::ifstream inFile(file);

    for (std::string line; getline(inFile, line);)
    {
        std::istringstream iss(line);
        do
        {
            std::string word;
            char c;
            iss.get(c);
            if (c == ' ')
            {
                compressedFile << 0 << ' ';
            }
            else{
                iss.seekg(-1, std::ios::cur);
                iss >> word;
                ptrdiff_t index = std::distance(dictionary.begin(), std::find(dictionary.begin(), dictionary.end(), word));
                if (!(index >= dictionary.size()) && word != "")
                {
                    compressedFile << index << ' ';
                }
            }
        } while (iss);
        compressedFile << -1 << ' ';
    }

    inFile.close();
    compressedFile.close();
}

void ExtractFile(std::string file)
{
    std::cout << std::string("Extracting '") << file << "'...\n";
    std::ifstream inFile(file);

    std::ofstream extractedFile;
    remove(("extract" + file.substr(0, file.length() - 4)).c_str());
    extractedFile.open("extract" + file.substr(0, file.length() - 4));
    std::string line;
    getline(inFile, line);
    std::istringstream iss(line);

    for (int index; iss >> index;)
    {
        if (index == 0)
        {
            extractedFile << ' ';
        }
        else if (index == -1){
            extractedFile << '\n';
        }
        else
        {
            extractedFile << dictionary.at(index-1);
        }
    }
    inFile.close();
    extractedFile.close();
}

bool FileExists(std::string name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void InitiateDict(std::string file)
{
    std::cout << "Reading file's dictionary...\n";
    std::ifstream inFile(file);

    for (std::string word; std::getline(inFile, word);)
    {
        dictionary.push_back(word);
    }
}

int main()
{
    std::cout << "[E]xtract or [C]ompress a file:\n";
    std::string option;
    std::cin >> option;
    std::string file;

    if (option == "C" || option == "c")
    {
        std::cout << "Please enter the file to compress:\n";
        std::cin >> file;
        CreateDictionary(file);
        CompressFile(file);
        std::cout << "\n--SUCCESS--\n";
    }
    else if (option == "E" || option == "e")
    {
        std::cout << "Please enter a file to extract:\n";
        std::cin >> file;
        std::string dict = (file.substr(0, file.length() - 4) + ".dict");
        if (file.substr(file.length() - 4, 4) != ".zac")
        {
            std::cout << "ERROR: Must be a '.zac' file!\n";
            std::cout << "To create a '.zac' file, first try the Compress option.";
        }
        else if (FileExists(file) && FileExists(dict))
        {
            InitiateDict(dict);
            ExtractFile(file);
            std::cout << "\n--SUCCESS--\n";
        }
        else
        {
            std::cout << "ERROR: The file you entered, or its dictionary, does not exists!\n";
        }
    }
}
