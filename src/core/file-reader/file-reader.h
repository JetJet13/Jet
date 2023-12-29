//
// Created by Johny Georges on 2023-12-28.
//

#ifndef JETLANG_FILE_READER_H
#define JETLANG_FILE_READER_H

#include <fstream>
#include <optional>

struct Cursor {
    uint8_t line;
    uint8_t position;
};

class FileReader {
private:
    std::string _filePath;
    std::ifstream _fileStream;
    Cursor _cursor;
public:
    void open(std::string &filePath);
    void close();
    std::optional<char> peek();
    std::optional<char> advance();
    uint8_t getCurrentLine() const;
    uint8_t getCurrentPosition() const;
};

#endif //JETLANG_FILE_READER_H
