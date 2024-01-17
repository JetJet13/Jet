//
// Created by Johny Georges on 2023-12-28.
//

#ifndef JETLANG_FILE_READER_H
#define JETLANG_FILE_READER_H

#include <fstream>
#include <optional>

struct Cursor {
    int line;
    int position;
};

class FileReader {
private:
    std::string _filePath;
    std::ifstream _fileStream;
    Cursor _cursor;
    bool _handleNewLine;
    bool _isOpen;
    int _numAdvances;
public:
    void open(std::string &filePath);
    void close();
    std::optional<char> peek();
    std::optional<char> advance();
    void retreat();
    Cursor getCursor();
    void setCursor(Cursor cursor);
    int getPeekLine();
    int getPeekPosition();
    int getNumAdvances() const;
    bool isOpen() const;
};

#endif //JETLANG_FILE_READER_H
