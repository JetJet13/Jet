//
// Created by Johny Georges on 2024-11-04.
//

#include "pre-processor.h"
#include "../jet-file/jet-file-id-generator/jet-file-id-generator.h"
#include "semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table-factory.h"

PreProcessor::PreProcessor(std::shared_ptr<SyntaxAnalyzer> syntaxAnalyzer, std::shared_ptr<SemanticAnalyzer> semanticAnalyzer) {
    _processedFileMap = PreProcessorMap();
    _scopeAnalyzer = ScopeAnalyzer();
    _syntaxAnalyzer = syntaxAnalyzer;
    _semanticAnalyzer = semanticAnalyzer;
}

std::shared_ptr<ASTFileNode> PreProcessor::buildFile(std::string filePath, std::shared_ptr<FileScope> fileScope) {
    auto fileNode = std::make_shared<ASTFileNode>(std::move(fileScope->getScope()), filePath, fileScope->getImports(), fileScope->getModule());
    fileNode->markGlobalVariables();
    fileNode->hoistTypes({ AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE });
    fileNode->setupModuleIfNecessary();
    return fileNode;
}

std::shared_ptr<JetFile> PreProcessor::process(std::string filePath) {
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
    _scopeAnalyzer.process(fileNode);
    // todo - change to createForModule() once debug-mode compiler flag is setup
    auto typeSignatureScope = TypeSignatureLookupTableFactory::createForDebugModule(fileNode->getModuleName());
    auto importedJetFiles = this->resolveModuleImports(fileNode, typeSignatureScope);
    auto typeCheckerResult = _semanticAnalyzer->analyze(fileNode, typeSignatureScope);
    if (!typeCheckerResult.ok()) {
        typeCheckerResult.printErrors();
        throw std::logic_error("type checker has errors: " + filePath);
    }
    return std::make_shared<JetFile>(fileNode, typeSignatureScope, typeCheckerResult, importedJetFiles);
}

std::set<std::shared_ptr<JetFile>> PreProcessor::resolveModuleImports(std::shared_ptr<ASTFileNode> fileNode, std::shared_ptr<TypeSignatureLookupTable> scope) {
    auto importedJetFiles = std::set<std::shared_ptr<JetFile>>();
    for (auto node : *fileNode->getImports()) {
        auto filePath = fileNode->getPathDirectory().append(node->getPath()->getImportPath()->getValue());
        auto jetFile = this->process(filePath);
        if (!jetFile->isModule()) {
            throw std::logic_error("cannot import a file that is not a module: " + jetFile->getId());
        }
        scope->link(jetFile->getScope());
        importedJetFiles.insert(jetFile);
    }
    return importedJetFiles;
}