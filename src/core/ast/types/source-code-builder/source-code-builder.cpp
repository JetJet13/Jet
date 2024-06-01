//
// Created by Johny Georges on 2024-05-30.
//

#include "source-code-builder.h"
#include "../../../../shared/types/basic-character-type.h"

SourceCodeBuilder::SourceCodeBuilder() {
    _sourceCode = "";
}

SourceCodeBuilder* SourceCodeBuilder::add(ASTNode* node) {
    _sourceCode += node->toSourceCode();
    return this;
}

SourceCodeBuilder* SourceCodeBuilder::addWithWhitespace(ASTNode* node) {
    _sourceCode += WHITE_SPACE;
    _sourceCode += node->toSourceCode();
    return this;
}

SourceCodeBuilder* SourceCodeBuilder::addWithNewLine(ASTNode* node) {
    _sourceCode += node->toSourceCode();
    _sourceCode += NEW_LINE;
    return this;
}

SourceCodeBuilder* SourceCodeBuilder::addNewLine() {
    _sourceCode += NEW_LINE;
    return this;
}

std::string SourceCodeBuilder::build() {
    return _sourceCode;
}