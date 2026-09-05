//
// Created by Johny Georges on 2023-12-28.
//

#ifndef JETLANG_FILE_READER_H
#define JETLANG_FILE_READER_H

#include <fstream>
#include <optional>

struct Cursor {
    unsigned long line;
    unsigned long column;
};

class FileReader {
private:
    std::string _filePath;
    std::ifstream _fileStream;
    Cursor _cursor;
    bool _handleNewLine;
    bool _isOpen;
    unsigned long _numAdvances;
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
    unsigned long getPeekLine();
    unsigned long getPeekColumn();
    unsigned long getNumAdvances() const;
    bool isOpen() const;
};

#endif //JETLANG_FILE_READER_H
