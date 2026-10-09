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
