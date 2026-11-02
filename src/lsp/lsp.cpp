// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2026-10-29.
//

#include "lsp.h"
#include "../shared/utils/logger/logger.h"
#include "utils/lsp-logger.h"

int main (int argc, const char* argv[]) {
//     std::io Server
//     lsp::LanguageSession server;
//    server.on([](td_initialize::request const& req) {
//        td_initialize::response rsp;
//        rsp.id = req.id;
//        return rsp;
//    });
//
//    server.on([&](Notify_Exit::notify&) {
//        exitRequested.notify(std::make_unique<bool>(true));
//    });
//
//    server.startStdio();

//  TCP Server
    auto protocolJsonHandler = std::make_shared<lsp::ProtocolJsonHandler>();
    auto logger = LspLogger();
    auto endpoint = std::make_shared<GenericEndpoint>(logger);
    auto server = lsp::TcpServer("127.0.0.1", "8080", protocolJsonHandler, endpoint, logger);
    Condition<bool> exitRequested;

    server.point.registerHandler(
        [&](const td_initialize::request& req) -> lsp::ResponseOrError<td_initialize::response> {
            td_initialize::response rsp;
            CodeLensOptions code_lens_options;
            code_lens_options.resolveProvider = true;
            rsp.result.capabilities.codeLensProvider = code_lens_options;

//            auto signatureHelpOptions = lsSignatureHelpOptions();
//            signatureHelpOptions.workDoneProgress = true;
//            rsp.result.capabilities.signatureHelpProvider = signatureHelpOptions;

            auto textDocumentSyncOptions = lsTextDocumentSyncOptions();
            textDocumentSyncOptions.change = lsTextDocumentSyncKind::Full;
            textDocumentSyncOptions.openClose = true;
            textDocumentSyncOptions.willSave = true;
            rsp.result.capabilities.textDocumentSync = std::pair(lsTextDocumentSyncKind::Full, textDocumentSyncOptions);

            std::cout << "Initialization Done!" << std::endl;
            return rsp;
        }
    );

    server.point.registerHandler(
        [](const td_signatureHelp::request& req) -> lsp::ResponseOrError<td_signatureHelp::response> {
            std::cout << "Signature Help Message Received!" << std::endl;
            td_signatureHelp::response rsp;
            rsp.result.signatures = {};
            return rsp;
        }
    );

//    server.point.registerHandler(
//        [](const ::request& req) -> lsp::ResponseOrError<td_signatureHelp::response> {
//            std::cout << "Signature Help Message Received!" << std::endl;
//            td_signatureHelp::response rsp;
//            rsp.result.signatures = {};
//            return rsp;
//        }
//    );

    server.point.registerHandler(
        [](const Notify_TextDocumentDidOpen::notify& notify) {
            std::cout << "Text Document Opened!" << std::endl;
        }
    );

    server.point.registerHandler(
        [](const Notify_TextDocumentDidChange::notify& notify) {
            std::cout << "Text Document Changed!" << std::endl;
        }
    );

    server.point.registerHandler(
        [](const Notify_TextDocumentDidClose::notify& notify) {
            std::cout << "Text Document Closed!" << std::endl;
        }
    );

    server.point.registerHandler(
        [](const Notify_InitializedNotification::notify& notify) {
            std::cout << "Initialized Notification Received!" << std::endl;
        }
    );

    server.point.registerHandler(
        [](const Notify_SetTrace::notify& notify) {
            std::cout << "Set Trace Notification Received! " << notify.params.value << std::endl;
        }
    );

    server.point.registerHandler(
        [](const Notify_sendNotification::notify& notify)  {
            std::cout << "Send Notification Received!" << std::endl;
        }
    );

    server.point.registerHandler(
        [](const Notify_Cancellation::notify& notify)  {
            std::cout << "Cancellation Notification Received!" << std::endl;
        }
    );

    server.point.registerHandler(
        [&](const Notify_Exit::notify& notify)  {
            std::cout << "Exit Notification Received!" << std::endl;
            server.stop();
        }
    );

    server.point.registerHandler(
        [&](const td_definition::request& req, const CancelMonitor& monitor) -> lsp::ResponseOrError<td_definition::response> {
            auto rsp = td_definition::response();
            rsp.result.first= std::vector<lsLocation>();
            logger.info("TD DEFINITION RESPONSE!");
            return rsp;
        }
    );

    server.run();
}