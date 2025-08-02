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
#include "../ir-lookup-table/ir-lookup-table.h"
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
#include "../../core/type-signature/module-type-signature/module-type-signature.h"
#include "../../core/type-signature/class-type-signature/class-type-signature.h"
#include "../ir-type/ir-enum-type.h"
#include "../ir-type/ir-pointer-type.h"
#include "../ir-type/ir-function-type.h"
#include "../../core/type-signature/invocable-type-signature/function-type-signature/function-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../ir-type/ir-array-pointer-type.h"
#include "../ir-nodes/ir-declaration-nodes/ir-declaration-node.h"
#include "../ir-injector/ir-injector.h"
#include "../types/ir-operation-type.h"
#include "../ir-type/ir-module-type.h"
#include "../ir-type/ir-class-type.h"
#include "../../core/ast/ast-nodes/ast-function-nodes/ast-function-argument-node.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"
#include "../ir-nodes/ir-context.h"
#include "../ir-type/ir-type-value-type.h"
#include "../ir-type/ir-ref-type.h"
#include "../../core/type-signature/ref-type-signature/ref-type-signature.h"
#include "../../core/type-signature/interface-type-signature/interface-type-signature.h"
#include "../ir-nodes/ir-type-declaration-nodes/ir-type-declaration-node.h"
#include "../../core/ast/ast-nodes/ast-type-declaration-nodes/ast-type-declaration-node.h"
#include "../../core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"
#include "../ir-type/ir-array-type.h"

class IRGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> _context;
    IRStrategyMap _irStrategyMap;
    IRInjector* _irInjector;
public:
    explicit IRGenerator(IRInjector* irInjector);
    IRNode* generateFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext);
    IRStatementNode* generateFor(ASTStatementNode* node, IRLookupTable* scope, IRContext* irContext);
    IRDeclarationNode* generateFor(ASTDeclarationNode* node, IRLookupTable* scope, IRContext* irContext);
    IRTypeDeclarationNode* generateFor(ASTTypeDeclarationNode* node, IRLookupTable* scope, IRContext* irContext);
    IRFunctionParameterListNode* generateFor(ASTFunctionParameterListNode* node, IRLookupTable* scope, IRContext* irContext, llvm::Function* irFunction);
    IRExpressionNode* generateFor(ASTExpressionNode* node, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
    IRExpressionNode* generateFor(ASTFunctionArgumentNode* node, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
    IRLiteralNode* generateFor(ASTLiteralNode* node, IRLookupTable* scope, IRContext* irContext);
    IRType* generateTypeFor(llvm::Constant* constant);
    IRType* generateTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRArrayPointerType* generateTypeFor(ArrayTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IREnumType* generateTypeFor(EnumTypeSignature* typeSignature, std::vector<llvm::Constant*> enumValues, IRLookupTable* scope, IRContext* irContext);
    IRStructType* generateTypeFor(InterfaceTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRStructType* generateTypeFor(StructTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRStructType* generateTypeFor(TupleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRModuleType* generateTypeFor(ModuleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRClassType* generateTypeFor(ClassTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRPointerType* generateTypeFor(PointerTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRRefType* generateTypeFor(RefTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRType* generateVoidType();
    IRFunctionType* generateIRFunctionType(llvm::Function* irFunction);
    IRPointerType* generateIrPointerType();
    IRPointerType* generateIrPointerType(IRType* type);
    IRRefType* generateIrRefType(IRType* type);
    IRArrayType* generateIRArrayType(IRType* elementType, unsigned long size);
    std::string getArrayPrototypeFunctionName(std::string id);
    std::string getJetUtilsFunctionName(std::string id);
    IRFunctionType* generateFunctionIrType(llvm::FunctionType* functionType);
    IRArrayType* generateVarArgsTypeValuesIrType(unsigned long numVarArgs);
    llvm::PointerType* generatePointerType();
    llvm::PointerType* generatePointerType(llvm::Type* type);
    llvm::IntegerType* generateIntType();
    llvm::Type* generateFloatType();
    llvm::Type* generateDoubleType();
    llvm::Type* generateLiteralType();
    llvm::IntegerType* generateBooleanType();
    llvm::IntegerType* generateCharType();
    llvm::IntegerType* generatePointerIntType();
    llvm::IntegerType* generateInt64Type();
    IRInstructionNode* generateIRTypeValueFor(IRType* irType);
    IRTypeValueType* generateIrTypeValueType();
    llvm::AllocaInst* generateIrTypeValueTypeAllocation();
    llvm::StoreInst* generateStoreInstruction(llvm::Value* value, llvm::Value* pointer, IRType* irType);
    IRParameterListType* generateParameterList(ParameterListTypeSignature* parameterList, IRLookupTable* scope, IRContext* irContext, std::optional<ParameterListItemTypeSignature*> scopeParameter = {});
    IRParameterType* generateParameterType(ParameterListItemTypeSignature* parameter, IRLookupTable* scope, IRContext* irContext);
    llvm::ConstantInt* generateIntConstant(int integer);
    llvm::ConstantInt* generateChar(char character);
    llvm::ConstantInt* generateBoolean(bool value);
    llvm::ConstantInt* generateInt64Constant(int integer);
    IRArrayPointerType* generateIrArrayPointerType(IRPointerType* irPointerType);
    IRArrayPointerType* generateIrArrayPointerType(IRType* arrayElementType);
    llvm::StructType* generateArrayPointerType();
    IRBlockNode* generateFunctionBlock(llvm::Function* irFunction);
    IRBlockNode* generateIfBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateIfThenBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateIfElseBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateIfEndBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateWhileConditionBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateWhileBodyBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateWhileEndBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForLoopConditionBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForLoopBodyBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForLoopEndBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForInBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForInSetupBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForInBodyBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateForInEndBlock(IRContext* irContext, std::string prefix = "");
    IRBlockNode* generateBasicBlock();
    IRBlockNode* generateBasicBlock(std::string label, IRContext* irContext);
    IRContext* generateContext(IRBlockNode* irBlock, IRModuleNode* irModule);
    IRModuleNode* generateModule(std::string moduleName);
    void initModule(IRModuleNode* irModule);
    IRFunctionNode* generateEmptyFunction(std::string functionName, IRModuleNode* irModuleNode);
    IRModuleNode* generateUtilInternalModule();
    IRInjector* getInjector();
};

#endif //JETLANG_IR_GENERATOR_H
