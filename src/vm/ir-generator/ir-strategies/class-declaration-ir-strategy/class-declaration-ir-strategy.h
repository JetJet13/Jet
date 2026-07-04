//
// Created by Johny Georges on 2024-12-09.
//

#ifndef JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
#define JETLANG_CLASS_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-class-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

class ClassDeclarationIRStrategy {
private:
    std::optional<IRClassPreConstructorNode*> generatePreConstructor(std::shared_ptr<ASTClassDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassConstructorNode* generate(std::shared_ptr<ASTClassConstructorDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassMethodNode* generate(std::shared_ptr<ASTClassMethodDeclarationNode> node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassMethodNode* generateStatic(std::shared_ptr<ASTClassMethodDeclarationNode> node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassStaticPropertyNode* generateStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareStaticMethod(std::shared_ptr<ASTClassMethodDeclarationNode> node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareConstructor(std::shared_ptr<ASTClassConstructorDeclarationNode> node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareStaticProperty(std::shared_ptr<ASTClassPropertyDeclarationNode> node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
public:
    IRClassDeclarationNode* generate(std::shared_ptr<ASTClassDeclarationNode> node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};


#endif //JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
