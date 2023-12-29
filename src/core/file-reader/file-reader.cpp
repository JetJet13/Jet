//
// Created by Johny Georges on 2023-12-28.
//

#include "file-reader.h"

#include <utility>
#include "../../shared/utils/file-io/file-io.h"
#include "../../shared/types/new-line.h"
#include "../../shared/utils/logger/logger.h"

void FileReader::open(std::string &filePath) {
    _filePath = filePath;
    _fileStream = FileIO::readFile(filePath);
    _cursor = {
        .line =  1,
        .position =  0
    };
}

void FileReader::close() {
    _fileStream.close();
    Logger::log("file closed", _filePath);
}

std::optional<char> FileReader::peek() {
    auto peekCharacter = _fileStream.peek();
    if (peekCharacter == EOF) {
        return {};
    }
    return std::char_traits<char>::to_char_type(peekCharacter);
}

std::optional<char> FileReader::advance() {
    auto nextCharacter = _fileStream.get();
    if (nextCharacter == EOF) {
        return {};
    }

    if (nextCharacter == NEW_LINE) {
        _cursor.line++;
        _cursor.position = 0;
    } else {
        _cursor.position++;
    }
    return std::char_traits<char>::to_char_type(nextCharacter);
}

uint8_t FileReader::getCurrentLine() const {
    return _cursor.line;
}

uint8_t FileReader::getCurrentPosition() const {
    return _cursor.position;
}

