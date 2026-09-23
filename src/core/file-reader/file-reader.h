//
// Created by Johny Georges on 2023-12-28.
//

#ifndef JETLANG_FILE_READER_H
#define JETLANG_FILE_READER_H

#include <fstream>
#include <optional>

struct Cursor {
    uint64_t line;
    uint64_t column;
};

class FileReader {
private:
    std::string _filePath;
    std::ifstream _fileStream;
    Cursor _cursor;
    bool _handleNewLine;
    bool _isOpen;
    uint64_t _numAdvances;
    bool _debugMode = false;
public:
    void switchToDebugMode();
    void open(std::string &filePath);
    void close();
    std::optional<char> peek();
    std::optional<char> advance();
    void retreat();
    Cursor getCursor();
    void setCursor(Cursor cursor);
    uint64_t getPeekLine();
    uint64_t getPeekColumn();
    uint64_t getNumAdvances() const;
    bool isOpen() const;
};

#endif //JETLANG_FILE_READER_H
