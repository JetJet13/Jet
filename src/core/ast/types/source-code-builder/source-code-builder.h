//
// Created by Johny Georges on 2024-05-30.
//

#ifndef JETLANG_SOURCE_CODE_BUILDER_H
#define JETLANG_SOURCE_CODE_BUILDER_H

#include <string>

class ASTNode;

class SourceCodeBuilder {
private:
    std::string _sourceCode;
public:
    SourceCodeBuilder();
    SourceCodeBuilder* add(ASTNode* node);
    SourceCodeBuilder* addWithWhitespace(ASTNode* node);
    SourceCodeBuilder* addWithNewLine(ASTNode* node);
    SourceCodeBuilder* addNewLine();
    std::string build();
};
#endif //JETLANG_SOURCE_CODE_BUILDER_H
