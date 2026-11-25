#include <peglib.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " \"<expression>\"\n";
        return 1;
    }

    // Concatène les arguments : ./parse "2 + 3" ou ./parse 2 + 3
    std::string expr = argv[1];
    for (int i = 2; i < argc; ++i) expr += std::string(" ") + argv[i];

    peg::parser p(R"(
        Expr    <- Term (AddOp Term)*
        Term    <- Factor (MulOp Factor)*
        Factor  <- Number / '(' Expr ')' / '-' Factor
        AddOp   <- < [-+] >
        MulOp   <- < [*/] >
        Number  <- < [0-9]+ ('.' [0-9]+)? >
        %whitespace <- [ \t]*
    )");
    if (!p) return 1; // grammaire invalide

    // Réduction gauche à droite : associativité correcte pour - et /
    auto fold = [](const peg::SemanticValues& vs) {
        double r = std::any_cast<double>(vs[0]);
        for (size_t i = 1; i < vs.size(); i += 2) {
            char op = std::any_cast<char>(vs[i]);
            double v = std::any_cast<double>(vs[i + 1]);
            switch (op) {
                case '+': r += v; break;
                case '-': r -= v; break;
                case '*': r *= v; break;
                case '/': r /= v; break;
            }
        }
        return r;
    };
    p["Expr"] = fold;
    p["Term"] = fold;
    p["AddOp"]  = [](const peg::SemanticValues& vs) { return vs.token()[0]; };
    p["MulOp"]  = [](const peg::SemanticValues& vs) { return vs.token()[0]; };
    p["Number"] = [](const peg::SemanticValues& vs) { return vs.token_to_number<double>(); };
    p["Factor"] = [](const peg::SemanticValues& vs) {
        double v = std::any_cast<double>(vs[0]);
        return vs.choice() == 2 ? -v : v;   // alternative '-' Factor
    };

    double val;
    if (!p.parse(expr, val)) {
        std::cerr << "Expression invalide : " << expr << '\n';
        return 1;
    }
    std::cout << val << '\n';
}