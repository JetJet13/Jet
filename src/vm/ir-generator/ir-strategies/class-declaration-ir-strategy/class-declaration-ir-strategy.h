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
    std::optional<IRClassPreConstructorNode*> generatePreConstructor(ASTClassDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassConstructorNode* generate(ASTClassConstructorDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassMethodNode* generate(ASTClassMethodDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassMethodNode* generateStatic(ASTClassMethodDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    IRClassStaticPropertyNode* generateStaticProperty(ASTClassPropertyDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareMethod(ASTClassMethodDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareStaticMethod(ASTClassMethodDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareConstructor(ASTClassConstructorDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
    void declareStaticProperty(ASTClassPropertyDeclarationNode* node, bool isExportable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IRClassType* irClassType);
public:
    IRClassDeclarationNode* generate(ASTClassDeclarationNode* node,  IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};


#endif //JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
