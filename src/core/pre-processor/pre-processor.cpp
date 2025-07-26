//
// Created by Johny Georges on 2024-11-04.
//

#include "pre-processor.h"
#include "../jet-file/jet-file-id-generator/jet-file-id-generator.h"
#include "semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table-factory.h"

PreProcessor::PreProcessor(SyntaxAnalyzer* syntaxAnalyzer, SemanticAnalyzer* semanticAnalyzer) {
    _processedFileMap = PreProcessorMap();
    _syntaxAnalyzer = syntaxAnalyzer;
    _semanticAnalyzer = semanticAnalyzer;
}

ASTFileNode* PreProcessor::buildFile(std::string filePath, FileScope* fileScope) {
    auto fileNode = new ASTFileNode(std::move(fileScope->getScope()), filePath, fileScope->getImports(), fileScope->getModule());
    fileNode->markGlobalVariables();
    fileNode->hoistTypes({ AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE });
    fileNode->hoistTypes({ AST_ENUM_DECLARATION_NODE, AST_INTERFACE_TYPE_DECLARATION_NODE });
    fileNode->setupModuleIfNecessary();
    return fileNode;
}

JetFile* PreProcessor::process(std::string filePath) {
    auto processedFile = _processedFileMap.findByFilePath(filePath);
    if (processedFile) {
        return processedFile.value();
    }
    auto syntaxResult = _syntaxAnalyzer->analyze(filePath);
    if (!syntaxResult->ok()) {
        syntaxResult->printErrors();
        throw std::logic_error("syntax analyzer has errors: " + filePath);
    }
    auto fileNode = this->buildFile(filePath, syntaxResult->getFileScope());
    auto typeSignatureScope = TypeSignatureLookupTableFactory::createForModule();
    auto importedJetFiles = this->resolveModuleImports(fileNode, typeSignatureScope);
    auto typeCheckerResult = _semanticAnalyzer->analyze(fileNode, typeSignatureScope);
    if (!typeCheckerResult.ok()) {
        typeCheckerResult.printErrors();
        throw std::logic_error("type checker has errors: " + filePath);
    }
    return new JetFile(fileNode, typeSignatureScope, typeCheckerResult, importedJetFiles);
}

std::vector<JetFile*> PreProcessor::resolveModuleImports(ASTFileNode* fileNode, TypeSignatureLookupTable* scope) {
    auto importedJetFiles = std::vector<JetFile*>();
    for (auto node : *fileNode->getImports()) {
        auto filePath = fileNode->getPathDirectory().append(node->getPath()->getImportPath()->getValue());
        auto jetFile = this->process(filePath);
        if (!jetFile->isModule()) {
            throw std::logic_error("cannot import a file that is not a module: " + jetFile->getId());
        }
        auto module = jetFile->getFile()->getModule().value();
        scope->insert(module->getId(), module->getTypeSignature());
        for (auto moduleExport : *module->getExports()) {
            auto key = module->getId() + "." + moduleExport->getId();
            scope->insert(key, moduleExport->getTypeSignature());
        }
        importedJetFiles.push_back(jetFile);
    }
    return importedJetFiles;
}