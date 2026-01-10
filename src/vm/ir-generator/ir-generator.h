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
#include "../ir-nodes/ir-block-nodes/ir-block-node.h"
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
#include "../ir-nodes/ir-block-nodes/ir-control-flow-block-node.h"
#include "../ir-type/ir-captured-variable-type.h"
#include "../ir-type/ir-invocable-type.h"
#include "../ir-type/ir-struct-ref-type.h"

class IRGenerator {
private:
    std::unique_ptr<llvm::LLVMContext> _context;
    IRStrategyMap _irStrategyMap;
    IRInjector* _irInjector;
    llvm::StructType* _arrayPointerType;
    llvm::StructType* _structRefType;
    llvm::StructType* _typeValueType;
    llvm::StructType* _refType;
    llvm::StructType* _invocableType;
public:
    explicit IRGenerator(IRInjector* irInjector);
    IRNode* generateFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext);
    void generateInitialTypeFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext);
    void generatePostInitialTypeFor(ASTNode* node, IRLookupTable* scope, IRContext* irContext);
    IRStatementNode* generateFor(ASTStatementNode* node, IRLookupTable* scope, IRContext* irContext);
    IRDeclarationNode* generateFor(ASTDeclarationNode* node, IRLookupTable* scope, IRContext* irContext);
    IRTypeDeclarationNode* generateFor(ASTTypeDeclarationNode* node, IRLookupTable* scope, IRContext* irContext);
    IRFunctionParameterListNode* generateFor(ASTFunctionParameterListNode* node, IRLookupTable* scope, IRContext* irContext, llvm::Function* irFunction);
    IRExpressionNode* generateFor(ASTExpressionNode* node, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
    IRExpressionNode* generateFor(ASTFunctionArgumentNode* node, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
    IRLiteralNode* generateFor(ASTLiteralNode* node, IRLookupTable* scope, IRContext* irContext);
    IRType* generateInitialTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRType* generatePostInitialTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRType* generateTypeFor(llvm::Constant* constant);
    IRType* generateTypeFor(TypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRArrayPointerType* generateTypeFor(ArrayTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IREnumType* generateTypeFor(EnumTypeSignature* typeSignature, std::vector<llvm::Constant*> enumValues, IRLookupTable* scope, IRContext* irContext);
    IRStructType* generateTypeFor(InterfaceTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRStructRefType* generateTypeFor(StructTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRStructRefType* generateTypeFor(TupleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRStructType* generateTypeFor(LambdaScopeTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRModuleType* generateTypeFor(ModuleTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRClassType* generateTypeFor(ClassTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRPointerType* generateTypeFor(PointerTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    IRRefType* generateTypeFor(RefTypeSignature* typeSignature, IRLookupTable* scope, IRContext* irContext);
    llvm::Type* getVoidType();
    IRType* generateVoidType();
    IRPointerType* generateIRInvocableCleanupType();
    IRInvocableType* generateIRInvocableType();
    IRPointerType* generateIrPointerType();
    IRPointerType* generateIrPointerType(IRType* type);
    IRRefType* generateIrRefType(IRType* type);
    llvm::StructType* getFunctionParameterType();
    IRArrayType* generateIRArrayType(IRType* elementType, unsigned long size);
    std::string getArrayPrototypeFunctionName(std::string id);
    std::string getRefPrototypeFunctionName(std::string id);
    std::string getJetUtilsFunctionName(std::string id);
    IRFunctionType* generateFunctionIrType(llvm::FunctionType* functionType);
    IRArrayType* generateVarArgsTypeValuesIrType(unsigned long numVarArgs);
    std::vector<llvm::Value*> generateArgumentPlaceholderList(IRFunctionType* irFunctionType);
    std::vector<llvm::Value*> generateArgumentPlaceholderList(IRInvocableType* irInvocableType);
    llvm::PointerType* generatePointerType();
    llvm::PointerType* generatePointerType(llvm::Type* type);
    llvm::IntegerType* generateIntType();
    llvm::IntegerType* generateInt32Type();
    llvm::Type* generateFloatType();
    llvm::Type* generateDoubleType();
    llvm::Type* generateLiteralType();
    llvm::IntegerType* generateBooleanType();
    llvm::IntegerType* generateCharType();
    llvm::IntegerType* generatePointerIntType();
    IRTypeValueInstructionNode* generateIRTypeValueFor(IRType* irType, IRContext* irContext);
    IRTypeValueType* generateIrTypeValueType();
    llvm::AllocaInst* generateIrTypeValueTypeAllocation();
    llvm::GetElementPtrInst* generateGEP(IRType* irType, llvm::Value* pointer, unsigned long index);
    llvm::ExtractValueInst* generateExtractValue(llvm::Value* value, unsigned int index);
    llvm::StoreInst* generateStoreInstruction(llvm::Value* value, llvm::Value* pointer, IRType* irType);
    llvm::LoadInst* generateLoadInstruction(llvm::Value* pointer, IRType* irType);
    IRParameterListType* generateParameterList(ParameterListTypeSignature* parameterList, IRLookupTable* scope, IRContext* irContext, std::optional<ParameterListItemTypeSignature*> scopeParameter = {});
    IRParameterType* generateParameterType(ParameterListItemTypeSignature* parameter, IRLookupTable* scope, IRContext* irContext);
    llvm::ConstantInt* generateIntConstant(int integer);
    llvm::ConstantInt* generateChar(char character);
    llvm::ConstantInt* generateBoolean(bool value);
    llvm::ConstantInt* generateInt64Constant(int integer);
    llvm::Constant* generateRawString(std::string rawString);
    llvm::Constant* getOrInsertGlobalVariableString(std::string id, std::string rawString, IRContext* irContext);
    IRArrayPointerType* generateIrArrayPointerType(IRPointerType* irPointerType);
    IRArrayPointerType* generateIrArrayPointerType(IRType* arrayElementType);
    IRStructRefType* generateIRStructRefType(IRStructType* irStructType);
    IRStructRefType* generateIRStructRefType();
    IRStructType* generateIRStructType();
    IRInstructionNode* generateFunctionParameterAllocation(IRType* irType);
    IRType* generateIRCaptureCounterType();
    IRType* generateIRStructRefCounterType();
    IRType* generateIRArcType();
    IRInstructionNode* generateArcAllocationForFunctionParameter(IRContext* irContext, llvm::Value* source, unsigned long count);
    IRInstructionNode* generateArcAllocationForStructRef(IRContext* irContext, llvm::Value* source, unsigned long count);
    IRInstructionNode* generateArcAllocation(IRContext* irContext, IRType* irType, llvm::Value* source, unsigned long count = 0);
    IRInstructionNode* generateArcAllocation(IRContext* irContext, unsigned long initialCount = 0);
    IRCapturedVariableType* generateIRCapturedVariableType(IRType* variableIrType);
    IRType* generateIRCharType();
    IRArrayPointerType* generateIrStringArrayPointerType();
    llvm::StructType* generateArrayPointerType();
    llvm::StructType* getArrayPointerType();
    llvm::StructType* getStructRefType();
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
    IRFunctionNode* generateMainFunction(std::string functionName, IRModuleNode* irModuleNode);
    IRModuleNode* generateUtilInternalModule();
    IRInjector* getInjector();
};

#endif //JETLANG_IR_GENERATOR_H
