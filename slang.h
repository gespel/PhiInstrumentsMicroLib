#include <Array.h>

Array<String, 1024> split(String input) {
    Array<String, 1024> out;

    String sub = "";
    for(int i = 0; i < strlen(input.c_str()); i++) {
        if(input.charAt(i) == ' ') {
            out.push_back(sub);
            sub = "";
        }
        else {
            sub.concat(input.charAt(i));
        }
    }
}

enum TokenType {
    IDENTIFIER,
    NUMBER,
    FUNCTION,
    RETURN
};

class Token {
public:
    Token() {

    }
    Token(TokenType t, String v) {
        this->t = t;
        this->v = v;
    }
    TokenType getType() {
        return t;
    }
    String getValue() {
        return v;
    }
private:
    TokenType t;
    String v;
};

class Slang {
public:
    Slang();
    void tokenize(String input);
private:
    Array<Token, 1024> tokens;
};

Slang::Slang() {
    
}

void Slang::tokenize(String input) {
    //tokens.push_back(Token(TokenType::FUNCTION, "FUNCTION"));
    Array<String, 1024> splited = split(input);
    for(int i = 0; i < strlen(input.c_str()); i++) {
        if(isAlpha(input.charAt(i))) {
            String name = "";
            while(isAlpha(input.charAt(i))) {
                name.concat(input.charAt(i));
                i++;
            }
        }
        if(isDigit(input.charAt(i))) {

        }
    }
}
