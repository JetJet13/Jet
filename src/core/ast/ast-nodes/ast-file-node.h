//
// Created by Johny Georges on 2024-01-15.
//

#ifndef JETLANG_AST_FILE_NODE_H
#define JETLANG_AST_FILE_NODE_H

#include <filesystem>
#include <vector>
#include "ast-node.h"
#include "ast-block-nodes/ast-block-node.h"
#include "ast-declaration-nodes/ast-import-single-module-declaration-node.h"

class ASTFileNode : public ASTNode {
private:
    std::filesystem::path _path;
    std::vector<ASTImportSingleModuleDeclarationNode*> _imports;
    std::vector<ASTNode*> _body;
public:
    ASTFileNode(std::vector<ASTNode*> body, std::string path);
    void append(ASTNode* node);
    std::string getPathDirectory();
    void hoistTypes(std::vector<ASTNodeType> astNodeTypes);
    std::vector<ASTNode*>* getBody();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FILE_NODE_H
