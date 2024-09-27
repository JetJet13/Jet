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
#include "../ir-nodes/ir-function-nodes/ir-function-parameter-list-node.h"
#include "../ir-type/ir-type.h"
#include "../ir-type/ir-parameter-type.h"
#include "../ir-type/ir-parameter-list-type.h"
#include "../ir-nodes/ir-statement-nodes/ir-statement-node.h"
#include "../ir-type/ir-struct-type.h"
#include "../../core/type-signature/enum-type-signature/enum-type-signature.h"
#include "../../core/type-signature/struct-type-signature/struct-type-signature.h"
#include "../../core/type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../ir-type/ir-enum-type.h"
#include "../ir-type/ir-pointer-type.h"
#include "../ir-type/ir-function-type.h"
#include "../../core/type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/lambda-type-signature/procedure-lambda-type-signature/procedure-lambda-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/lambda-type-signature/function-lambda-type-signature/function-lambda-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../ir-type/ir-array-pointer-type.h"
#include "../ir-nodes/ir-declaration-nodes/ir-declaration-node.h"
#include "../ir-injector/ir-injector.h"
#include "../types/ir-operation-type.h"

class IRGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> _context;
    IRStrategyMap _irStrategyMap;
    IRInjector* _irInjector;
public:
    explicit IRGenerator(IRInjector* irInjector);
    IRNode* generateFor(ASTNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode);
    IRStatementNode* generateFor(ASTStatementNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode);
    IRDeclarationNode* generateFor(ASTDeclarationNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode);
    IRFunctionParameterListNode* generateFor(ASTFunctionParameterListNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode, llvm::Function* irFunction);
    IRExpressionNode* generateFor(ASTExpressionNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode, IROperationType irOperationType);
    IRLiteralNode* generateFor(ASTLiteralNode* node, IRLookupTable* scope, IRModuleNode* irModuleNode);
    IRType* generateTypeFor(llvm::Constant* constant);
    IRType* generateTypeFor(TypeSignature* typeSignature);
    IRArrayPointerType* generateTypeFor(ArrayTypeSignature* typeSignature);
    IREnumType* generateTypeFor(EnumTypeSignature* typeSignature, std::vector<llvm::Constant*> enumValues);
    IRStructType* generateTypeFor(StructTypeSignature* typeSignature);
    IRStructType* generateTypeFor(TupleTypeSignature* typeSignature);
    IRType* generateVoidType();
    IRPointerType* generateIrPointerType();
    IRPointerType* generateIrPointerType(IRType* type);
    llvm::PointerType* generatePointerType();
    llvm::PointerType* generatePointerType(llvm::Type* type);
    llvm::IntegerType* generateIntType();
    llvm::IntegerType* generateCharType();
    IRParameterListType* generateParameterList(ParameterListTypeSignature* parameterList);
    IRParameterType* generateParameterType(ParameterListItemTypeSignature* parameter);
    llvm::Constant* generateIntConstant(int integer);
    IRArrayPointerType* generateArrayPointerType(IRPointerType* irPointerType);
    IRArrayPointerType* generateArrayPointerType(llvm::PointerType* pointerType, IRType* arrayElementType);
    IRBlockNode* generateFunctionBlock(llvm::Function* irFunction);
    IRModuleNode* generateModule(std::string moduleName);
    void initModule(IRModuleNode* irModule);
    IRFunctionNode* generateEmptyFunction(std::string functionName, IRModuleNode* irModuleNode);
    IRInjector* getInjector();
};

#endif //JETLANG_IR_GENERATOR_H
