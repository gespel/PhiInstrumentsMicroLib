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
    out.push_back(sub);
    return out;
}

enum TokenType {
    IDENTIFIER,
    NUMBER,
    FUNCTION,
    RETURN,
    SEMICOLON
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
    Token createToken(String input);
private:
    Array<Token, 1024> tokens;
};

Slang::Slang() {
    
}

void Slang::tokenize(String input) {
    //tokens.push_back(Token(TokenType::FUNCTION, "FUNCTION"));
    Array<String, 1024> splited = split(input);

    Serial.print("Size: ");
    Serial.println(splited.size());
    for(auto w : splited) {
        Serial.println(w);
    }
    for(auto ts : splited) {
        if(isAlpha(input.charAt(i))) {
            String name = "";
            int i = 0;
            while(isAlpha(input.charAt(i))) {
                name.concat(input.charAt(i));
                i++;
            }
            auto t = createToken(name);
            tokens.push_back(t);
        }
        else if(isDigit(input.charAt(i))) {

        }

    }
}

Token Slang::createToken(String input) {
    if(input.equals("fn")) {
        return Token(TokenType::FUNCTION, "Function");
    }
    else if(input.equals("return")) {
        return Token(TokenType::RETURN, "Return");
    }
    else {
        return Token(TokenType::IDENTIFIER, input);
    }
}
