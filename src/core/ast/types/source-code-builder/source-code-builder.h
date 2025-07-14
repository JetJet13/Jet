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
    std::optional<ASTNode*> _lastNode = {};
public:
    SourceCodeBuilder();
    SourceCodeBuilder* add(ASTNode* node);
    std::string build();
};
#endif //JETLANG_SOURCE_CODE_BUILDER_H
