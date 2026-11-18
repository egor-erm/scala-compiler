#include <cstdio>
#include <fstream>
#include <iostream>

#include <FlexLexer.h>

#include "lexer/lexer_driver.h"
#include "nodes/nodes.h"

extern int yydebug;
int yyparse(TopStatSeqNode** out_root);

void yyerror(TopStatSeqNode** out_root, const char* message) {
    (void)out_root;
    std::fprintf(stderr, "%s\n", message);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file.scala>\n";
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 2;
    }

    yyFlexLexer lexer(&input, &std::cerr);
    setScalaLexer(&lexer);
    setScalaLexerParserMode(true);

    yydebug = 1;
    TopStatSeqNode* root = nullptr;
    const int status = yyparse(&root);
    setScalaLexerParserMode(false);

    if (status != 0 || root == nullptr) {
        deleteNodeTree(root);
        return 1;
    }

    std::cout << createDotTree(root);
    deleteNodeTree(root);
    return 0;
}
