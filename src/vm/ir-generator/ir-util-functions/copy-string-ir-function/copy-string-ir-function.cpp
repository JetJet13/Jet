//
// Created by Johny Georges on 2024-09-26.
//

#include "copy-string-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string CopyStringIRFunction::getCopyStringIRFunctionName() {
    return "jet.copy.string";
}

void CopyStringIRFunction::generateCopyStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType(new IRType(irGenerator->generateCharType()));
    auto arrayPointerType = irGenerator->generateArrayPointerType(pointerType);
    auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(**context), { pointerType->getType(), arrayPointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStringIRFunction::getCopyStringIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto destinationParameterAllocation = IRInstructionNodeFactory::create(pointerType);
    irGenerator->getInjector()->inject(
        functionBlock,
        new IRFunctionParameterDeclarationNode(
            new llvm::Argument(pointerType->getType()),
            destinationParameterAllocation
        ),
        irModuleNode
    );

    auto arrayPointerParamAllocationType = irGenerator->generateIrPointerType(arrayPointerType);
    auto arrayPointerParameterAllocation = IRInstructionNodeFactory::create(arrayPointerParamAllocationType);
    irGenerator->getInjector()->inject(
        functionBlock,
        new IRFunctionParameterDeclarationNode(
            new llvm::Argument(arrayPointerType->getType()),
            arrayPointerParameterAllocation
        ),
        irModuleNode
    );
}