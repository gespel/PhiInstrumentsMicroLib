#define MAX_TOKENS 128
#include <Array.h>
#include "../synths.h"
#include "token.h"





class Slang {
public:
    Slang(double sampleRate, Array<Token, MAX_TOKENS> tokens);
    void tokenize(String input);
    void interpret();
    Token createAlphaToken(String input);
    void printTokens();
    Array<SineSynth*, 64> getSineSynths();
    Array<SawtoothSynth*, 64> getSawtoothSynths();
    int getNumSineSynths();
    int getNumSawtoothSynths();
private:
    Array<Token, MAX_TOKENS> tokens;
    Array<SineSynth*, 64> sineSynths;
    Array<SawtoothSynth*, 64> sawtoothSynths;
    bool consume(TokenType input, TokenType expected, int *i);
    bool peek(TokenType input, TokenType expected);
    void createSineSynth(String freq);
    void createSawtoothSynth(String freq);
    double sampleRate;
};

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
        Serial.println("WRONG TOKEN. EXPECTED OTHER TOKEN");
        Serial.print(expected);
        Serial.print(" ");
        Serial.println(input);
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