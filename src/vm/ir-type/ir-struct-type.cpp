//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-struct-type.h"
#include "../../shared/utils/logger/logger.h"

IRStructType::IRStructType(llvm::StructType *type, std::unordered_map<std::string, unsigned long> keyIndexMap, std::unordered_map<std::string, IRType*> keyTypeMap) : IRType(type) {
    _type = type;
    _keyIndexMap = keyIndexMap;
    _keyTypeMap = keyTypeMap;
}

llvm::StructType* IRStructType::getType() {
    return _type;
}

void IRStructType::makeGlobal(std::string id, std::unique_ptr<llvm::LLVMContext>* context) {
    _type = llvm::StructType::create(**context, _type->elements(), id);
}

void IRStructType::setAlignmentAndSizeForIRTypes() {
    auto alignment = this->getAlignment();
    std::optional<IRType*> prevType = {};
    auto prevTypeSize = 0;
    for (int i = 0; i < this->size(); ++i) {
        auto irTypeAtIndex = this->getIRTypeByIndex(i);
        irTypeAtIndex->setAlignmentOverride(alignment);
        if (irTypeAtIndex->isStructType()) {
            ((IRStructType*)irTypeAtIndex)->setAlignmentAndSizeForIRTypes();
        }
        auto currentTypeSize = irTypeAtIndex->getSizeInBytes();
        if (currentTypeSize % alignment.value() == 0 && prevTypeSize > 0 && prevTypeSize < alignment.value()) {
            prevType.value()->setSizeInBytesOverride(alignment.value());
            prevTypeSize = alignment.value();
        }

        if (i == this->size() - 1 && currentTypeSize % alignment.value() != 0 && prevTypeSize % alignment.value() == 0) {
            irTypeAtIndex->setSizeInBytesOverride(alignment.value());
        } else {
            prevType = irTypeAtIndex;
            prevTypeSize = irTypeAtIndex->getSizeInBytes();
        }
    }



}

unsigned long IRStructType::size() {
    return _type->getNumElements();
}

uint64_t IRStructType::getSizeInBytes() {
    auto totalSize = 0;
    for (auto keyValue : _keyTypeMap) {
        totalSize += keyValue.second->getSizeInBytes();
    }
    auto alignment = this->getAlignment().value();
    auto totalRemainder = totalSize % alignment;
    if (totalRemainder > 0) {
        auto factor = std::floor(totalSize / alignment) + 1;
        auto paddedSize = factor * alignment;
        return paddedSize;
    }
    return totalSize;
}

void IRStructType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    for (auto keyValue : _keyTypeMap) {
       keyValue.second->setAlignmentOverride(alignmentOverride);
    }
}


llvm::Align IRStructType::getAlignment() {
    if (_alignmentOverride) {
        return _alignmentOverride.value();
    }
    unsigned long largestSize = 1;
    for (unsigned long i = 0; i < this->getType()->getStructNumElements(); i++) {
        auto structElementSize = this->getIRTypeByIndex(i)->getAlignment().value();
        if (structElementSize > largestSize) {
            largestSize = structElementSize;
        }
    }
    auto largestPowerOfTwo = std::ceil(log2(largestSize));
    return llvm::Align(std::pow(2, largestPowerOfTwo));
}

std::string IRStructType::getKeyForIndex(unsigned long index) {
    for (const auto& keyValue : _keyIndexMap) {
        if (keyValue.second == index) {
            return keyValue.first;
        }
    }
    throw std::logic_error("no key found for index: " + std::to_string(index));
}

unsigned long IRStructType::getIndexForKey(std::string key) {
    auto result = _keyIndexMap.find(key);
    if (result == _keyIndexMap.end()) {
        throw std::logic_error("no struct index found for key: " + key);
    } else {
        return result->second;
    }
}

unsigned long IRStructType::getIndexForKey(unsigned long indexAsKey) {
    return this->getIndexForKey(std::to_string(indexAsKey));
}

IRType* IRStructType::getIRTypeForKey(std::string key) {
    auto result = _keyTypeMap.find(key);
    if (result == _keyTypeMap.end()) {
        throw std::logic_error("no type found for key: " + key);
    } else {
        return result->second;
    }
}

IRType* IRStructType::getIRTypeByIndex(unsigned long index) {
    for (auto keyValue : _keyIndexMap) {
        if (keyValue.second == index) {
            return this->getIRTypeForKey(keyValue.first);
        }
    }
    throw std::logic_error("no type found for index: " + std::to_string(index));
}

bool IRStructType::containsTypeThatRequiresFreeing() {
    for (auto keyValue : _keyTypeMap) {
        if (keyValue.second->containsTypeThatRequiresFreeing()) {
            return true;
        }
    }
    return false;
}

bool IRStructType::isStructType() {
    return true;
}

void IRStructType::print() {
    Logger::log("IR STRUCT TYPE");
    llvm::outs().write_escaped("|");
    _type->print(llvm::outs(), true, true);
    llvm::outs().write_escaped("|");
    for (auto keyValue : _keyTypeMap) {
        llvm::outs().write_escaped("|");
        llvm::outs().write_escaped(keyValue.first);
        llvm::outs().write_escaped(" : ");
        keyValue.second->print();
        llvm::outs().write_escaped("|");
    }
    llvm::outs().write_escaped("|");
    for (const auto& keyValue : _keyIndexMap) {
        llvm::outs().write_escaped("|");
        llvm::outs().write_escaped(keyValue.first);
        llvm::outs().write_escaped(" : ");
        llvm::outs().write_escaped(std::to_string(keyValue.second));
        llvm::outs().write_escaped("|");
    }
}
