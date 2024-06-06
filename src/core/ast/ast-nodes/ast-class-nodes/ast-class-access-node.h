//
// Created by Johny Georges on 2024-04-25.
//

#ifndef JETLANG_AST_CLASS_ACCESS_NODE_H
#define JETLANG_AST_CLASS_ACCESS_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "ast-this-access-node.h"
#include "ast-this-node.h"

class ASTClassAccessNode : public ASTNode {
private:
    ASTThisNode* _this;
    ASTThisAccessNode* _thisAccess;
public:
    ASTClassAccessNode(ASTThisNode* thisNode, ASTThisAccessNode* thisAccess);
    ASTThisNode* getThis();
    ASTThisAccessNode* getThisAccess();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_ACCESS_NODE_H
