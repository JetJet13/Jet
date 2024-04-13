//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_PACKAGE_PATH_NODE_H
#define JETLANG_AST_PACKAGE_PATH_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../../../lexeme/lexeme.h"
#include "../../ast-literal-nodes/ast-string-literal-node.h"

class ASTPackagePathNode : public ASTNode {
private:
    ASTStringLiteralNode* _packagePath;
public:
    ASTPackagePathNode(ASTStringLiteralNode* packagePath);
    ASTStringLiteralNode* getPackagePath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_PACKAGE_PATH_NODE_H
