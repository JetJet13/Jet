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
// Created by Johny Georges on 2024-05-30.
//

#ifndef JETLANG_SOURCE_CODE_BUILDER_H
#define JETLANG_SOURCE_CODE_BUILDER_H

#include <string>
#include <optional>

class ASTNode;

class SourceCodeBuilder {
private:
    std::string _sourceCode;
    std::optional<std::shared_ptr<ASTNode>> _lastNode = {};
public:
    SourceCodeBuilder();
    SourceCodeBuilder* add(std::shared_ptr<ASTNode> node);
    std::string build();
};
#endif //JETLANG_SOURCE_CODE_BUILDER_H
