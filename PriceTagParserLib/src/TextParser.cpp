#include "TextParser.h"

TextParser* TextParser::createTextParser(TextParserId id) {
    TextParser *parser;
    switch (id) {
        case SimpleTextParserId:
            parser = new SimpleTextParser();
            break;
        default:
            assert(false);
    }
    return parser;
}

SimpleTextParser::~SimpleTextParser() {

}

void SimpleTextParser::parse(std::string text) {

}