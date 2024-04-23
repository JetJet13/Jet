//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_CONSTRUCTOR_NODE_H
#define JETLANG_AST_CLASS_CONSTRUCTOR_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"

class ASTClassConstructorNode : public ASTNode {
private:
    ASTFunctionParameterListNode* _parameters;
    ASTFunctionBlockNode* _content;
public:
    explicit ASTClassConstructorNode(ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content);
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionBlockNode* getContent();
    unsigned long numParameters();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_CONSTRUCTOR_NODE_H
