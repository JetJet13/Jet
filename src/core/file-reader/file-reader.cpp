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
        .position =  0
    };
    _handleNewLine = false;
    _isOpen = true;
}

void FileReader::close() {
    _fileStream.close();
    _isOpen = false;
    Logger::log("file closed", _filePath);
}

std::optional<char> FileReader::peek() {
    auto peekCharacter = _fileStream.peek();
    if (!_isOpen || peekCharacter == EOF) {
        return {};
    }
    return std::char_traits<char>::to_char_type(peekCharacter);
}

std::optional<char> FileReader::advance() {
    auto nextCharacter = _fileStream.get();
    if (!_isOpen && nextCharacter == EOF) {
        return {};
    }

    if (_handleNewLine) {
        _cursor.line++;
        _cursor.position = 0;
        _handleNewLine = nextCharacter == NEW_LINE;
    } else if (nextCharacter == NEW_LINE) {
        _handleNewLine = true;
        _cursor.position++;
    } else {
        _cursor.position++;
    }
    return std::char_traits<char>::to_char_type(nextCharacter);
}

int FileReader::getPeekLine() {
    auto nextChar = this->peek();
    if (!nextChar) {
        return -1;
    }

    if (_handleNewLine) {
        return _cursor.line + 1;
    }
    return _cursor.line;
}

int FileReader::getPeekPosition() {
    auto nextChar = this->peek();
    if (!nextChar) {
        return -1;
    }

    if (_handleNewLine) {
        return 0;
    }
    return _cursor.position;
}


int FileReader::getCurrentLine() const {
    return _cursor.line;
}

int FileReader::getCurrentPosition() const {
    return _cursor.position;
}

bool FileReader::isOpen() const {
    return _isOpen;
}

