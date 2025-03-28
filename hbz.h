#ifndef HBZ_H
#define HBZ_H
#include <string>
#include <vector>

std::string compress(std::string value); // compress a text
std::string decompressString(std::string value);
void compressFiles(std::vector<std::string> fileVector,
                   std::string outputFileName);
void decompressFiles(std::string archive);

#endif
