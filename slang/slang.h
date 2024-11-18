#define MAX_TOKENS 64
#include <Array.h>
#include "../synths.h"
#include "token.h"
#include "function.h"

class Slang {
public:
    Slang(double sampleRate, Array<Token, MAX_TOKENS> tokens);
    void tokenize(String input);
    void interpret();
    Token createAlphaToken(String input);
    void printTokens();
    Array<SineSynth*, 64> getSineSynths();
    Array<SawtoothSynth*, 64> getSawtoothSynths();
    Array<Function*, 64> getFunctions();
    int getNumSineSynths();
    int getNumSawtoothSynths();
    void printDebug();
    void clear();
private:
    Array<Token, MAX_TOKENS> tokens;
    Array<SineSynth*, 64> sineSynths;
    Array<SawtoothSynth*, 64> sawtoothSynths;
    Array<Function*, 64> functions;
    bool consume(TokenType input, TokenType expected, int *i);
    bool peek(TokenType input, TokenType expected);
    void createSineSynth(String freq);
    void createSawtoothSynth(String freq);
    double sampleRate;
};

void Slang::clear() {
    sineSynths.clear();
    sawtoothSynths.clear();
    functions.clear();
}

Slang::Slang(double sampleRate, Array<Token, MAX_TOKENS> tokens) {
    this->tokens = tokens;
    this->sampleRate = sampleRate;
}

void Slang::printTokens() {
    for(Token t : tokens) {
        Serial.println(t.typeAsString() + " -> " + t.getValue());
    }
    Serial.println("==========================================");
}


bool Slang::peek(TokenType input, TokenType expected) {
    if(input == expected) {
        return true;
    }
    else {
        return false;
    }
}

bool Slang::consume(TokenType input, TokenType expected, int *i) {
    if(input == expected) {
        (*i)++;
        return true;
    }
    else {
        Serial.println("WRONG TOKEN. EXPECTED OTHER TOKEN. Expected:");
        Serial.println(Token(expected, "").typeAsString());
        Serial.println("Got:");
        Serial.println(Token(input, "").typeAsString());
        sleep(5);
        exit(-1);
        return false;
    }
}

void Slang::interpret() {
    for(int i = 0; i < this->tokens.size(); i++) {
        bool executed = false;
        if(peek(tokens[i].getType(), SINESYNTH)) {
            consume(tokens[i].getType(), SINESYNTH, &i);
            consume(tokens[i].getType(), LEFT_PARANTHESIS, &i);
            peek(tokens[i].getType(), NUMBER);
            String freq = tokens[i].getValue();
            consume(tokens[i].getType(), NUMBER, &i);
            consume(tokens[i].getType(), RIGHT_PARANTHESIS, &i);
            consume(tokens[i].getType(), SEMICOLON, &i);

            createSineSynth(freq);
            executed = true;
        }
        else if(peek(tokens[i].getType(), SAWTOOTHSYNTH)) {
            consume(tokens[i].getType(), SAWTOOTHSYNTH, &i);
            consume(tokens[i].getType(), LEFT_PARANTHESIS, &i);
            peek(tokens[i].getType(), NUMBER);
            String freq = tokens[i].getValue();
            consume(tokens[i].getType(), NUMBER, &i);
            consume(tokens[i].getType(), RIGHT_PARANTHESIS, &i);
            consume(tokens[i].getType(), SEMICOLON, &i);

            createSawtoothSynth(freq);
            executed = true;
        }
        else if(peek(tokens[i].getType(), FUNCTION)) {
            Array<Token*, 64> functiontokens;
            consume(tokens[i].getType(), FUNCTION, &i);
            peek(tokens[i].getType(), IDENTIFIER);
            String name = tokens[i].getValue();
            consume(tokens[i].getType(), IDENTIFIER, &i);
            consume(tokens[i].getType(), LEFT_BRACKETS, &i);
            while(tokens[i].getType() != RIGHT_BRACKETS) {
                //Serial.println(tokens[i].typeAsString());
                functiontokens.push_back(&tokens[i]);
                i++;
            }
            consume(tokens[i].getType(), RIGHT_BRACKETS, &i);
            Serial.print("Creating function with the name ");
            Serial.println(name);
            
            functions.push_back(new Function(name, functiontokens));
            executed = true;
        }
        if(executed) {
            i--;
        }
    }
}

void Slang::createSineSynth(String freq) {
    double f = freq.toDouble();
    String pre = "Creating Sine Synthesizer with ";
    String out = pre + f;
    Serial.println(out);
    SineSynth *s = new SineSynth(f, sampleRate);
    sineSynths.push_back(s);
}

void Slang::createSawtoothSynth(String freq) {
    double f = freq.toDouble();
    String pre = "Creatine Sawtooth Synthesizer with ";
    String out = pre + f;
    Serial.println(out);
    SawtoothSynth *s = new SawtoothSynth(f, sampleRate);
    sawtoothSynths.push_back(s);
}

Array<SineSynth*, 64> Slang::getSineSynths() {
    return sineSynths;
}

Array<SawtoothSynth*, 64> Slang::getSawtoothSynths() {
    return sawtoothSynths;
}

Array<Function*, 64> Slang::getFunctions() {
    return functions;
}

void Slang::printDebug() {
    String pre_sine = "Number of SineSynths: ";
    String pre_saw = " Number of SawtoothSynths: ";
    Serial.println(pre_sine + this->getSineSynths().size() + pre_saw + this->getSawtoothSynths().size());

    Serial.println("");
    String pre_functions = "Number of defined functions: ";
    Serial.println(pre_functions + this->getFunctions().size());
    for(auto f : functions) {
        Serial.print("Name: ");
        Serial.println(f->getName());
        for(auto t : f->getTokens()) {
            Serial.println("\t" + t->typeAsString() + " " + t->getValue());
        }
    }
}