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
// Created by Johny Georges on 2026-10-30.
//

#ifndef JETLANG_LSP_LOGGER_H
#define JETLANG_LSP_LOGGER_H

#include <LibLsp/JsonRpc/MessageIssue.h>

class LspLogger : public lsp::Log {
    void log(Level level, std::wstring&& msg) override;
    void log(Level level, const std::wstring& msg) override;
    void log(Level level, std::string&& msg) override;
    void log(Level level, const std::string& msg) override;
};

#endif //JETLANG_LSP_LOGGER_H
