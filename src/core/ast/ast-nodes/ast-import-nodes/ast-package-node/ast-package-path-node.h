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
    std::shared_ptr<ASTStringLiteralNode> _packagePath;
public:
    ASTPackagePathNode(std::shared_ptr<ASTStringLiteralNode> packagePath);
    std::shared_ptr<ASTStringLiteralNode> getPackagePath();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PACKAGE_PATH_NODE_H
