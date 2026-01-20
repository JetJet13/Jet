//
// Created by Johny Georges on 2024-07-05.
//

#include "ir-module-node.h"


IRModuleNode::IRModuleNode(std::unique_ptr<llvm::Module> irValue, std::string arrayAccessFunctionName, std::string copyArrayFunctionName, std::string copyPointerFunctionName, std::string copyLambdaFunctionName, std::string copyStructFunctionName, std::string copyStructRefFunctionName, std::string copyValueFunctionName, std::string copyStringFunctionName, std::string copyRefFunctionName, std::string freeArrayFunctionName, std::string freePointerFunctionName, std::string freeLambdaFunctionName, std::string freeInvocableFunctionName, std::string freeStructFunctionName, std::string freeStructRefFunctionName, std::string freeValueFunctionName, std::string freeStringFunctionName, std::string freeRefFunctionName, std::string freeCapturedVariableFunctionName, std::string printFunctionName, std::string printIntFunctionName, std::string printFloatFunctionName, std::string printCharFunctionName, std::string printBoolFunctionName, std::string printStringFunctionName, std::string printRefFunctionName, std::string printArrayFunctionName, std::string printStructFunctionName, std::string printStructRefFunctionName, std::string printLambdaFunctionName, std::string printWhitespaceFunctionName, std::string printCommaFunctionName, std::string printNewLineFunctionName, std::string printDebugMarkerFunctionName, std::string printDebugPointerFunctionName, std::string printDebugStringFunctionName, std::string printDebugRefCountFunctionName, std::string range1pFunctionName, std::string range2pFunctionName, std::string range3pFunctionName, std::string mallocFunctionName, std::string mallocFreeFunctionName, std::string mallocSizeFunctionName, std::string equalValueFunctionName, std::string equalStringFunctionName, std::string equalArrayFunctionName, std::string equalStructFunctionName, std::string equalStructRefFunctionName, std::string equalRefFunctionName, std::string equalRefLeftOnlyFunctionName, std::string equalRefRightOnlyFunctionName, std::string stringConcatFunctionName, std::string arrayAppendFunctionName, std::string arrayPrependFunctionName, std::string arrayConcatFunctionName, std::string arrayHeadFunctionName, std::string arrayLastFunctionName, std::string arrayDropFunctionName, std::string arrayDropLastFunctionName, std::string arrayTailFunctionName, std::string arrayTakeFunctionName, std::string arrayTakeLastFunctionName, std::string arraySizeFunctionName, std::string arrayEmptyFunctionName, std::string memcpyFunctionName, std::string setupSrefFunctionName, std::string setupRefFunctionName, std::string setupRefForStructFunctionName, std::string refOfFunctionName, std::string srefWithFunctionName, std::string sameRefAsFunctionName, std::string incrementRefCountFunctionName, std::string incrementLambdaRefCountFunctionName, std::string getRefCountFunctionName) {
    _irValue = std::move(irValue);
    _arrayAccessFunctionName = arrayAccessFunctionName;
    _copyArrayFunctionName = copyArrayFunctionName;
    _copyPointerFunctionName = copyPointerFunctionName;
    _copyLambdaFunctionName = copyLambdaFunctionName;
    _copyStructFunctionName = copyStructFunctionName;
    _copyStructRefFunctionName = copyStructRefFunctionName;
    _copyValueFunctionName = copyValueFunctionName;
    _copyStringFunctionName = copyStringFunctionName;
    _copyRefFunctionName = copyRefFunctionName;
    _freeArrayFunctionName = freeArrayFunctionName;
    _freePointerFunctionName = freePointerFunctionName;
    _freeLambdaFunctionName = freeLambdaFunctionName;
    _freeInvocableFunctionName = freeInvocableFunctionName;
    _freeStructFunctionName = freeStructFunctionName;
    _freeStructRefFunctionName = freeStructRefFunctionName;
    _freeValueFunctionName = freeValueFunctionName;
    _freeStringFunctionName = freeStringFunctionName;
    _freeRefFunctionName = freeRefFunctionName;
    _freeCapturedVariableFunctionName = freeCapturedVariableFunctionName;
    _printFunctionName = printFunctionName;
    _printIntFunctionName = printIntFunctionName;
    _printFloatFunctionName = printFloatFunctionName;
    _printCharFunctionName = printCharFunctionName;
    _printBoolFunctionName = printBoolFunctionName;
    _printStringFunctionName = printStringFunctionName;
    _printRefFunctionName = printRefFunctionName;
    _printArrayFunctionName = printArrayFunctionName;
    _printStructFunctionName = printStructFunctionName;
    _printStructRefFunctionName = printStructRefFunctionName;
    _printLambdaFunctionName = printLambdaFunctionName;
    _printWhitespaceFunctionName = printWhitespaceFunctionName;
    _printCommaFunctionName = printCommaFunctionName;
    _printNewLineFunctionName = printNewLineFunctionName;
    _printDebugMarkerFunctionName = printDebugMarkerFunctionName;
    _printDebugPointerFunctionName = printDebugPointerFunctionName;
    _printDebugStringFunctionName = printDebugStringFunctionName;
    _printDebugRefCountFunctionName = printDebugRefCountFunctionName;
    _range1pFunctionName = range1pFunctionName;
    _range2pFunctionName = range2pFunctionName;
    _range3pFunctionName = range3pFunctionName;
    _mallocFunctionName = mallocFunctionName;
    _mallocFreeFunctionName = mallocFreeFunctionName;
    _mallocSizeFunctionName = mallocSizeFunctionName;
    _equalValueFunctionName = equalValueFunctionName;
    _equalStringFunctionName = equalStringFunctionName;
    _equalArrayFunctionName = equalArrayFunctionName;
    _equalStructFunctionName = equalStructFunctionName;
    _equalStructRefFunctionName = equalStructRefFunctionName;
    _equalRefFunctionName = equalRefFunctionName;
    _equalRefLeftOnlyFunctionName = equalRefLeftOnlyFunctionName;
    _equalRefRightOnlyFunctionName = equalRefRightOnlyFunctionName;
    _stringConcatFunctionName = stringConcatFunctionName;
    _arrayAppendFunctionName = arrayAppendFunctionName;
    _arrayPrependFunctionName = arrayPrependFunctionName;
    _arrayConcatFunctionName = arrayConcatFunctionName;
    _arrayHeadFunctionName = arrayHeadFunctionName;
    _arrayLastFunctionName = arrayLastFunctionName;
    _arrayDropFunctionName = arrayDropFunctionName;
    _arrayDropLastFunctionName = arrayDropLastFunctionName;
    _arrayTailFunctionName = arrayTailFunctionName;
    _arrayTakeFunctionName = arrayTakeFunctionName;
    _arrayTakeLastFunctionName = arrayTakeLastFunctionName;
    _arraySizeFunctionName = arraySizeFunctionName;
    _arrayEmptyFunctionName = arrayEmptyFunctionName;
    _memcpyFunctionName = memcpyFunctionName;
    _setupSrefFunctionName = setupSrefFunctionName;
    _setupRefFunctionName = setupRefFunctionName;
    _setupRefForStructFunctionName = setupRefForStructFunctionName;
    _refOfFunctionName = refOfFunctionName;
    _srefWithFunctionName = srefWithFunctionName;
    _sameRefAsFunctionName = sameRefAsFunctionName;
    _incrementRefCountFunctionName = incrementRefCountFunctionName;
    _incrementLambdaRefCountFunctionName = incrementLambdaRefCountFunctionName;
    _getRefCountFunctionName = getRefCountFunctionName;
}

std::unique_ptr<llvm::Module>* IRModuleNode::getModule() {
    if (_linkedToIRModule != nullptr) {
        return _linkedToIRModule->getModule();
    }
    return &_irValue;
}

void IRModuleNode::linkTo(std::shared_ptr<IRModuleNode> otherIRModule) {
    if (_linkedToIRModule != nullptr) {
        _linkedToIRModule->linkTo(otherIRModule);
        return;
    }
    llvm::Linker::linkModules(
            *otherIRModule->getModule()->get(),
            std::move(_irValue)
    );
    _linkedToIRModule = otherIRModule;
}

llvm::Function* IRModuleNode::findFunction(std::string name) {
    if (_linkedToIRModule != nullptr) {
        return _linkedToIRModule->findFunction(name);
    }
    return _irValue->getFunction(name);
}

llvm::Function* IRModuleNode::getArrayAccessFunction() {
    return this->findFunction(_arrayAccessFunctionName);
}

llvm::Function* IRModuleNode::getCopyArrayFunction() {
    return this->findFunction(_copyArrayFunctionName);
}

llvm::Function* IRModuleNode::getCopyPointerFunction() {
    return this->findFunction(_copyPointerFunctionName);
}

llvm::Function* IRModuleNode::getCopyLambdaFunction() {
    return this->findFunction(_copyLambdaFunctionName);
}

llvm::Function* IRModuleNode::getCopyStructFunction() {
    return this->findFunction(_copyStructFunctionName);
}

llvm::Function* IRModuleNode::getCopyStructRefFunction() {
    return this->findFunction(_copyStructRefFunctionName);
}

llvm::Function* IRModuleNode::getCopyValueFunction() {
    return this->findFunction(_copyValueFunctionName);
}

llvm::Function* IRModuleNode::getCopyStringFunction() {
    return this->findFunction(_copyStringFunctionName);
}

llvm::Function* IRModuleNode::getCopyRefFunction() {
    return this->findFunction(_copyRefFunctionName);
}

llvm::Function* IRModuleNode::getFreeArrayFunction() {
    return this->findFunction(_freeArrayFunctionName);
}

llvm::Function* IRModuleNode::getFreePointerFunction() {
    return this->findFunction(_freePointerFunctionName);
}

llvm::Function* IRModuleNode::getFreeLambdaFunction() {
    return this->findFunction(_freeLambdaFunctionName);
}

llvm::Function* IRModuleNode::getFreeInvocableFunction() {
    return this->findFunction(_freeInvocableFunctionName);
}

llvm::Function* IRModuleNode::getFreeStructFunction() {
    return this->findFunction(_freeStructFunctionName);
}

llvm::Function* IRModuleNode::getFreeStructRefFunction() {
    return this->findFunction(_freeStructRefFunctionName);
}

llvm::Function* IRModuleNode::getFreeValueFunction() {
    return this->findFunction(_freeValueFunctionName);
}

llvm::Function* IRModuleNode::getFreeStringFunction() {
    return this->findFunction(_freeStringFunctionName);
}

llvm::Function* IRModuleNode::getFreeRefFunction() {
    return this->findFunction(_freeRefFunctionName);
}

llvm::Function* IRModuleNode::getFreeCapturedVariableFunction() {
    return this->findFunction(_freeCapturedVariableFunctionName);
}

llvm::Function* IRModuleNode::getPrintFunction() {
    return this->findFunction(_printFunctionName);
}

llvm::Function* IRModuleNode::getPrintIntFunction() {
    return this->findFunction(_printIntFunctionName);
}

llvm::Function* IRModuleNode::getPrintFloatFunction() {
    return this->findFunction(_printFloatFunctionName);
}

llvm::Function* IRModuleNode::getPrintCharFunction() {
    return this->findFunction(_printCharFunctionName);
}

llvm::Function* IRModuleNode::getPrintBoolFunction() {
    return this->findFunction(_printBoolFunctionName);
}

llvm::Function* IRModuleNode::getPrintStringFunction() {
    return this->findFunction(_printStringFunctionName);
}

llvm::Function* IRModuleNode::getPrintRefFunction() {
    return this->findFunction(_printRefFunctionName);
}

llvm::Function* IRModuleNode::getPrintArrayFunction() {
    return this->findFunction(_printArrayFunctionName);
}

llvm::Function* IRModuleNode::getPrintStructFunction() {
    return this->findFunction(_printStructFunctionName);
}

llvm::Function* IRModuleNode::getPrintStructRefFunction() {
    return this->findFunction(_printStructRefFunctionName);
}

llvm::Function* IRModuleNode::getPrintLambdaFunction() {
    return this->findFunction(_printLambdaFunctionName);
}

llvm::Function* IRModuleNode::getPrintWhitespaceFunction() {
    return this->findFunction(_printWhitespaceFunctionName);
}

llvm::Function* IRModuleNode::getPrintCommaFunction() {
    return this->findFunction(_printCommaFunctionName);
}

llvm::Function* IRModuleNode::getPrintNewLineFunction() {
    return this->findFunction(_printNewLineFunctionName);
}

llvm::Function* IRModuleNode::getPrintDebugMarkerFunction() {
    return this->findFunction(_printDebugMarkerFunctionName);
}

llvm::Function* IRModuleNode::getPrintDebugPointerFunction() {
    return this->findFunction(_printDebugPointerFunctionName);
}

llvm::Function* IRModuleNode::getPrintDebugStringFunction() {
    return this->findFunction(_printDebugStringFunctionName);
}

llvm::Function* IRModuleNode::getPrintDebugRefCountFunction() {
    return this->findFunction(_printDebugRefCountFunctionName);
}

llvm::Function* IRModuleNode::getRange1pFunction() {
    return this->findFunction(_range1pFunctionName);
}

llvm::Function* IRModuleNode::getRange2pFunction() {
    return this->findFunction(_range2pFunctionName);
}

llvm::Function* IRModuleNode::getRange3pFunction() {
    return this->findFunction(_range3pFunctionName);
}

llvm::Function* IRModuleNode::getMallocFunction() {
    return this->findFunction(_mallocFunctionName);
}

llvm::Function* IRModuleNode::getMallocFreeFunction() {
    return this->findFunction(_mallocFreeFunctionName);
}

llvm::Function* IRModuleNode::getMallocSizeFunction() {
    return this->findFunction(_mallocSizeFunctionName);
}

llvm::Function* IRModuleNode::getEqualValueFunction() {
    return this->findFunction(_equalValueFunctionName);
}

llvm::Function* IRModuleNode::getEqualStringFunction() {
    return this->findFunction(_equalStringFunctionName);
}

llvm::Function* IRModuleNode::getEqualArrayFunction() {
    return this->findFunction(_equalArrayFunctionName);
}

llvm::Function* IRModuleNode::getEqualStructFunction() {
    return this->findFunction(_equalStructFunctionName);
}

llvm::Function* IRModuleNode::getEqualStructRefFunction() {
    return this->findFunction(_equalStructRefFunctionName);
}

llvm::Function* IRModuleNode::getEqualRefFunction() {
    return this->findFunction(_equalRefFunctionName);
}

llvm::Function* IRModuleNode::getEqualRefLeftOnlyFunction() {
    return this->findFunction(_equalRefLeftOnlyFunctionName);
}

llvm::Function* IRModuleNode::getEqualRefRightOnlyFunction() {
    return this->findFunction(_equalRefRightOnlyFunctionName);
}

llvm::Function* IRModuleNode::getStringConcatFunction() {
    return this->findFunction(_stringConcatFunctionName);
}

llvm::Function* IRModuleNode::getArrayAppendFunction() {
    return this->findFunction(_arrayAppendFunctionName);
}

llvm::Function* IRModuleNode::getArrayPrependFunction() {
    return this->findFunction(_arrayPrependFunctionName);
}

llvm::Function* IRModuleNode::getArrayConcatFunction() {
    return this->findFunction(_arrayConcatFunctionName);
}

llvm::Function* IRModuleNode::getArrayHeadFunction() {
    return this->findFunction(_arrayHeadFunctionName);
}

llvm::Function* IRModuleNode::getArrayLastFunction() {
    return this->findFunction(_arrayLastFunctionName);
}

llvm::Function* IRModuleNode::getArrayDropFunction() {
    return this->findFunction(_arrayDropFunctionName);
}

llvm::Function* IRModuleNode::getArrayDropLastFunction() {
    return this->findFunction(_arrayDropLastFunctionName);
}

llvm::Function* IRModuleNode::getArrayTailFunction() {
    return this->findFunction(_arrayTailFunctionName);
}

llvm::Function* IRModuleNode::getArrayTakeFunction() {
    return this->findFunction(_arrayTakeFunctionName);
}

llvm::Function* IRModuleNode::getArrayTakeLastFunction() {
    return this->findFunction(_arrayTakeLastFunctionName);
}

llvm::Function* IRModuleNode::getArraySizeFunction() {
    return this->findFunction(_arraySizeFunctionName);
}

llvm::Function* IRModuleNode::getArrayEmptyFunction() {
    return this->findFunction(_arrayEmptyFunctionName);
}

llvm::Function* IRModuleNode::getMemcpyFunction() {
    return this->findFunction(_memcpyFunctionName);
}

llvm::Function* IRModuleNode::getSetupSrefFunction() {
    return this->findFunction(_setupSrefFunctionName);
}

llvm::Function* IRModuleNode::getSetupRefFunction() {
    return this->findFunction(_setupRefFunctionName);
}

llvm::Function* IRModuleNode::getSetupRefForStructFunction() {
    return this->findFunction(_setupRefForStructFunctionName);
}

llvm::Function* IRModuleNode::getRefOfFunction() {
    return this->findFunction(_refOfFunctionName);
}

llvm::Function* IRModuleNode::getSrefWithFunction() {
    return this->findFunction(_srefWithFunctionName);
}

llvm::Function* IRModuleNode::getSameRefAsFunction() {
    return this->findFunction(_sameRefAsFunctionName);
}

llvm::Function* IRModuleNode::getIncrementRefCountFunction() {
    return this->findFunction(_incrementRefCountFunctionName);
}

llvm::Function* IRModuleNode::getIncrementLambdaRefCountFunction() {
    return this->findFunction(_incrementLambdaRefCountFunctionName);
}

llvm::Function* IRModuleNode::getGetRefCountFunction() {
    return this->findFunction(_getRefCountFunctionName);
}