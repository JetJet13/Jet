//
// Created by Johny Georges on 2023-12-28.
//

#include "file-reader.h"

#include <utility>
#include "../../shared/utils/file-io/file-io.h"
#include "../../shared/types/basic-character-type.h"
#include "../../shared/utils/logger/logger.h"

void FileReader::open(std::string &filePath) {
    _filePath = filePath;
    _fileStream = FileIO::readFile(filePath);
    _cursor = {
        .line =  1,
        .column =  0
    };
    _handleNewLine = false;
    _isOpen = true;
    _numAdvances = 0;
}

void FileReader::close() {
    _fileStream.close();
    _isOpen = false;
    Logger::log("file closed", _filePath);
}

std::optional<char> FileReader::peek() {
    auto peekCharacter = _fileStream.peek();
    if (_fileStream.fail()) {
        Logger::log("fileStream failed");
        _fileStream.clear();
        peekCharacter = _fileStream.peek();
    }
    if (!_isOpen || peekCharacter == EOF) {
        if (peekCharacter == EOF) {
            Logger::log("peekCharacter is EOF");
        }
        return {};
    }
    return std::char_traits<char>::to_char_type(peekCharacter);
}

std::optional<char> FileReader::advance() {
    if (!_isOpen) {
        return {};
    }

    auto nextCharacter = _fileStream.get();
    _numAdvances++;
    if (nextCharacter == EOF) {
        return {};
    }

    if (_handleNewLine) {
        _cursor.line++;
        _cursor.column = 0;
        _handleNewLine = nextCharacter == NEW_LINE;
    } else if (nextCharacter == NEW_LINE) {
        _handleNewLine = true;
        _cursor.column++;
    } else {
        _cursor.column++;
    }
    return std::char_traits<char>::to_char_type(nextCharacter);
}

void FileReader::retreat() {
    if (_isOpen) {
        _fileStream.unget();
        _numAdvances--;
    }
}

Cursor FileReader::getCursor() {
    return _cursor;
}

void FileReader::setCursor(Cursor cursor) {
    _cursor = cursor;
}

unsigned long FileReader::getPeekLine() {
    auto nextChar = this->peek();
    if (!nextChar) {
        return -1;
    }

    if (_handleNewLine) {
        return _cursor.line + 1;
    }
    return _cursor.line;
}

unsigned long FileReader::getPeekColumn() {
    auto nextChar = this->peek();
    if (!nextChar) {
        return -1;
    }

    if (_handleNewLine) {
        return 0;
    }
    return _cursor.column;
}

unsigned long FileReader::getNumAdvances() const {
    return _numAdvances;
}

bool FileReader::isOpen() const {
    return _isOpen;
}

