// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2023-12-28.
//

#include "file-reader.h"

#include <utility>
#include "../../shared/utils/file-io/file-io.h"
#include "../../shared/types/basic-character-type.h"
#include "../../shared/utils/logger/logger.h"
#include "../../shared/types/exit-status.enum.h"

void FileReader::switchToDebugMode() {
    _debugMode = true;
}

void FileReader::open(std::string &filePath) {
    _filePath = filePath;
    _fileStream = FileIO::readFile(filePath);
    _cursor = {
        .line =  1,
        .column =  1
    };
    _handleNewLine = false;
    _isOpen = true;
    _numAdvances = 0;
}

void FileReader::close() {
    _fileStream.close();
    _isOpen = false;
    Logger::debugLog(_debugMode, "file closed", _filePath);
}

std::optional<char> FileReader::peek() {
    if (!_isOpen) {
        return {};
    }

    auto peekCharacter = _fileStream.peek();
    if (_fileStream.fail()) {
        Logger::debugLog(_debugMode, "fileStream failed", _fileStream.failbit, _fileStream.bad(), _fileStream.badbit);
        _fileStream.clear();
        _fileStream.seekg(_numAdvances);
        peekCharacter = _fileStream.peek();
    }
    if (!_isOpen || peekCharacter == EOF) {
        if (peekCharacter == EOF) {
            Logger::debugLog(_debugMode, "peekCharacter is EOF");
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
        Logger::debugLog(_debugMode, "nextCharacter is EOF!");
        return {};
    }
    if (nextCharacter == NEW_LINE) {
        _handleNewLine = true;
    } else {
        _cursor.column++;
    }

    if (_handleNewLine) {
        _cursor.line++;
        _cursor.column = 1;
        _handleNewLine = false;
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

uint64_t FileReader::getPeekLine() {
    auto nextChar = this->peek();
    if (!nextChar) {
        return -1;
    }

    if (_handleNewLine) {
        return _cursor.line + 1;
    }
    return _cursor.line;
}

uint64_t FileReader::getPeekColumn() {
    auto nextChar = this->peek();
    if (!nextChar) {
        return -1;
    }

    if (_handleNewLine) {
        return 1;
    }
    return _cursor.column;
}

uint64_t FileReader::getNumAdvances() const {
    return _numAdvances;
}

bool FileReader::isOpen() const {
    return _isOpen;
}

