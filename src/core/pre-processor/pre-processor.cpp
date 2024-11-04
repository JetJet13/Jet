//
// Created by Johny Georges on 2024-11-04.
//

#include "pre-processor.h"
#include "../jet-file/jet-file-id-generator/jet-file-id-generator.h"

PreProcessor::PreProcessor(SyntaxAnalyzer* syntaxAnalyzer, SemanticAnalyzer* semanticAnalyzer) {
    _processedFileMap = PreProcessorMap();
    _syntaxAnalyzer = syntaxAnalyzer;
    _semanticAnalyzer = semanticAnalyzer;
}

ASTFileNode* PreProcessor::buildFile(std::string filePath, FileScope* fileScope) {
    auto fileNode = new ASTFileNode(std::move(fileScope->getScope()), filePath, fileScope->getImports(), fileScope->getModule());
    fileNode->hoistTypes({ AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE });
    fileNode->hoistTypes({ AST_ENUM_DECLARATION_NODE });
    fileNode->hoistTypes({ AST_FUNCTION_DECLARATION_NODE, AST_PROCEDURE_DECLARATION_NODE });
    fileNode->hoistTypes({ AST_CLASS_DECLARATION_NODE });
    fileNode->setupModuleIfNecessary();
    return fileNode;
}

JetFile* PreProcessor::process(std::string filePath) {
    auto processedFile = _processedFileMap.findByFilePath(filePath);
    if (processedFile) {
        return processedFile.value();
    }
    auto fileNode = this->buildFile(filePath, _syntaxAnalyzer->analyze(filePath));
    auto typeSignatureScope = new TypeSignatureLookupTable();
    auto typeCheckerResult = _semanticAnalyzer->analyze(fileNode, typeSignatureScope);
    if (!typeCheckerResult.ok()) {
        typeCheckerResult.printErrors();
        throw std::logic_error("type checker has errors: " + filePath);
    }
    auto jetFile = new JetFile(fileNode, typeSignatureScope, typeCheckerResult);
    this->resolveModuleImports(jetFile);
    return jetFile;
}

void PreProcessor::resolveModuleImports(JetFile* jetFile) {
    for (auto node : *jetFile->getFile()->getImports()) {
        auto filePath = jetFile->getFile()->getPathDirectory().append(
                node->getPath()->getImportPath()->getValue());
        jetFile->addImportedFile(this->process(filePath));
    }
}