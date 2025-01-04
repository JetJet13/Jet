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
    void generatePreConstructor(ASTClassDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType);
    IRClassConstructorNode* generate(ASTClassConstructorDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType);
    IRClassMethodNode* generate(ASTClassMethodDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType);
    void declareMethod(ASTClassMethodDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IRClassType* irClassType);
public:
    IRClassDeclarationNode* generate(ASTClassDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};


#endif //JETLANG_CLASS_DECLARATION_IR_STRATEGY_H
