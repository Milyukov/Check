#include "GlobalParameters.h"

enum TextParserId { SimpleTextParserId = 0 };
class TextParser {
public:
    virtual ~TextParser() {};
    virtual void parse(std::string text) = 0;
    static TextParser *createTextParser(TextParserId id);
    std::string getPrice() { return price; };
    std::string getProducrName() { return productName; };
protected:
    std::string price;
    std::string productName;
};

class SimpleTextParser : public TextParser {
    ~SimpleTextParser();
    void parse(std::string text);
};