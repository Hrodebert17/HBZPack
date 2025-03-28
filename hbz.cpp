#include "hbz.h"
#include <fstream>

std::string decompressString(std::string value) {
  std::vector<int> intVecContent;
  std::string characterString;
  for (auto character : value) {
    if (character != ',') {
      if (character != '\n') {
        characterString += character;
      }
    } else {
      intVecContent.push_back(std::stoi(characterString));
      characterString = "";
    }
  }
  if (!characterString.empty()) {
    intVecContent.push_back(std::stoi(characterString));
  }
  std::string finalContent;
  for (auto integer : intVecContent) {
    finalContent += static_cast<char>(integer);
  }
  return finalContent;
}

std::string compress(std::string value) {
  std::string outputText;
  bool firstChar = true;
  for (auto character : value) {
    if (!firstChar) {
      outputText += ",";
    } else {
      firstChar = false;
    }
    outputText += std::to_string(static_cast<int>(character));
  }
  return outputText;
}

void compressFiles(std::vector<std::string> fileVector,
                   std::string outputFileName) {
  for (auto fileName : fileVector) {
    std::ifstream inputFile(fileName);
    // open the file
    if (inputFile.is_open()) {
      // now we will scan the file getting all the content inside of it;
      std::string fileContent;
      std::string line;
      while (std::getline(inputFile, line)) {
        if (!fileContent.empty()) {
          fileContent += "\n";
        }
        fileContent += line;
      }
      inputFile.close();
      std::string outputText;
      bool firstChar = true;
      for (auto character : fileContent) {
        if (!firstChar) {
          outputText += ",";
        } else {
          firstChar = false;
        }
        outputText += std::to_string(static_cast<int>(character));
      }
      outputText += " ";
      firstChar = true;
      for (auto character : fileName) {
        if (!firstChar) {
          outputText += ",";
        } else {
          firstChar = false;
        }
        outputText += std::to_string(static_cast<int>(character));
      }
      outputText += "\n";
      std::ofstream offFile(outputFileName, std::ios::app);
      if (offFile.is_open()) {
        offFile.write(outputText.c_str(), outputText.size());
        offFile.close();
      }
    }
  }
}

void decompressFiles(std::string archive) {
  // we have a file called "output.hbz" this file contains some special data,
  // each line is a file and each line also contains a file in form of
  // numbers, after the numberical content which is the file content we find
  // the file name. an example would be
  // 104,101,108,108,111,32,119,111,114,108,100,33 test.txt this is the
  // codification of a file called test.txt containing the text: "hello
  // world!"

  // firstly we will get each line of the zip

  std::vector<std::string> files;

  std::ifstream inputFile(archive);
  if (inputFile.is_open()) {
    std::string line;
    while (std::getline(inputFile, line)) {
      files.push_back(line);
    }
  }

  // after collecting all files from the zips we can go on and extract them,
  // we can do that by reversing the process we did before to zip them,
  for (auto fileToExtract : files) {
    // in order to actually save the file we need his name, following
    // what we did to zip them we can just copy the last digits until we
    // find a space then we will decode it.
    std::string content;
    std::string name;

    {
      bool switchContentName = false;
      for (auto character : fileToExtract) {
        if (character == ' ') {
          switchContentName = true;
          continue;
        }
        if (switchContentName) {
          name += character;
        } else {
          content += character;
        }
      }
    }
    // now that we subdivided the infos we can go on and actually decode them
    {
      // name conversion
      std::vector<int> intVecContent;
      std::string characterString;
      for (auto character : name) {
        if (character != ',') {
          if (character != '\n') {
            characterString += character;
          }
        } else {
          intVecContent.push_back(std::stoi(characterString));
          characterString = "";
        }
      }
      if (!characterString.empty()) {
        intVecContent.push_back(std::stoi(characterString));
      }
      std::string finalContent;
      for (auto integer : intVecContent) {
        finalContent += static_cast<char>(integer);
      }
      name = finalContent;
    }

    {
      // content conversion
      std::vector<int> intVecContent;
      std::string characterString;
      for (auto character : content) {
        if (character != ',') {
          if (character != '\n') {
            characterString += character;
          }
        } else {
          intVecContent.push_back(std::stoi(characterString));
          characterString = "";
        }
      }
      if (!characterString.empty()) {
        intVecContent.push_back(std::stoi(characterString));
      }
      std::string finalContent;
      for (auto integer : intVecContent) {
        finalContent += static_cast<char>(integer);
      }
      content = finalContent;
    }

    // after converting everything we can go on and save the file
    std::ofstream offFile(name, std::ios::trunc);
    if (offFile.is_open()) {
      offFile.write(content.c_str(), content.size());
      offFile.close();
    }
  }
}
