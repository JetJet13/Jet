//
// Created by Johny Georges on 2024-06-11.
//

#ifndef JETLANG_IR_GENERATOR_H
#define JETLANG_IR_GENERATOR_H

#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "ir-lookup-table/ir-lookup-table.h"
#include "../../core/ast/ast-nodes/ast-declaration-nodes/ast-declaration-node.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-expression-node.h"
#include "../../core/ast/ast-nodes/ast-literal-nodes/ast-literal-node.h"
#include "../../core/ast/ast-nodes/ast-statement-nodes/ast-statement-node.h"
#include "ir-strategies/ir-strategy-map.h"
#include "../../core/type-signature/array-type-signature/array-type-signature.h"
#include "../ir-nodes/ir-node.h"
#include "../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../ir-nodes/ir-literal-nodes/ir-literal-node.h"
#include "../ir-nodes/ir-block-node.h"
#include "../ir-nodes/ir-module-node.h"
#include "../ir-nodes/ir-function-nodes/ir-function-node.h"

class IRGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> _context;
    IRStrategyMap _irStrategyMap;
public:
    explicit IRGenerator();
    IRNode* generateFor(ASTNode* node, IRLookupTable* scope);
    IRNode* generateFor(ASTStatementNode* node, IRLookupTable* scope);
    IRNode* generateFor(ASTDeclarationNode* node, IRLookupTable* scope);
    IRExpressionNode* generateFor(ASTExpressionNode* node, IRLookupTable* scope);
    IRLiteralNode* generateFor(ASTLiteralNode* node, IRLookupTable* scope);
    llvm::Type* generateTypeFor(TypeSignature* typeSignature);
    llvm::Type* determineBestFitType(std::vector<llvm::Value*> elementValues);
    llvm::Constant* generateZeroConstant();
    IRBlockNode* generateBasicBlock();
    IRBlockNode* generateFunctionBlock(IRFunctionNode* irFunctionNode);
    IRModuleNode* generateModule(std::string moduleName);
    IRFunctionNode* generateEmptyFunction(std::string functionName, IRModuleNode* irModuleNode);
    llvm::IRBuilder<> generateBasicBlockBuilder();
};

#endif //JETLANG_IR_GENERATOR_H
