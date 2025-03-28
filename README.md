# **HBZPack**  
*A lightweight file bundling and compression library*  

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)  
🔗 **GitHub:** [HBZPack](https://github.com/Hrodebert17/HBZPack)  

## **Overview**  
HBZPack allows you to easily bundle multiple files into a single `.hbz` archive and extract them when needed. It also supports text compression and decompression for efficient storage.  

## **Features**  
✔️ Lightweight & fast file bundling  
✔️ Simple text compression & decompression  
✔️ Minimal setup – just include `hbz.h` and `hbz.cpp`  
✔️ Cross-platform support  

## **Installation**  
Just include the following files in your project:  
```cpp
#include "hbz.h"
```

## **Usage**  

### **Text Compression & Decompression**  
```cpp
#include "hbz.h"

std::string text = "Hello, HBZPack!";
std::string compressed = compress(text);
std::string decompressed = decompressString(compressed);
```

### **File Bundling & Extraction**  
```cpp
#include "hbz.h"

std::vector<std::string> files = {"file1.txt", "file2.txt"};
compressFiles(files, "archive.hbz"); // Creates an archive

decompressFiles("archive.hbz"); // Extracts files from the archive
```

## **License**  
This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.  

