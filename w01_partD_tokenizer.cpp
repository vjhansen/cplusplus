/*
 Part D is an extension of Part C. Create a program that reads a text string with multiple numbers and operators and prints the result. But now it should be possible, among other things, to use () around partial expressions and the program must deal with arbitrary number of parameters. It is also advantageous to add some other operators %, ^ (power) etc.
 
 A natural extension is also to create the program so that the text string can be entered at the start of the program from the command line.
 
 Example (The text at the back of the > is read during execution):
 
 Enter two numbers with an operator between> 4 + 5 + (7 + 4) * 3 + 4 * 4 + 9/3 + 4 * 12 - 3/4
 The answer to 4 + 5 + (7 + 4) * 3 + 4 * 4 + 9/3 + 4 * 12 - 3/4 is 108.25.
 */

#include <iostream>
#include <string>
#include <cmath>

#define pi 3.1415

int no_errors = 0;
double error(const char* s) {
    no_errors++;
    std::cerr << "error: " << s << '\n';
    return 1;
}

enum Token_val {
    name, number, end, PLUS='+', MINUS='-', mul='*',
    DIV='/', print=';', assign='=', LP='(' ,RP=')',
    MOD='%', power = '^'
};


// Token: sequence of chars, (kind, value) pairs: i.e. (number, 3)
class Token {
public:
    char kind;
    double value; // for numbers
    Token(char ch): kind(ch), value(0) {}
    Token(char ch, double val): kind(ch), value(val) {}
};

class Token_stream {
public:
    Token_stream(); // constructor
    
    Token get();
    void putback(Token curr_token);

private:
    bool full; // token in buffer?
    Token buffer;
};

Token_stream::Token_stream():full(false),buffer(0){}; // default constructor

void Token_stream::putback(Token curr_token) {
    if (full) error("putback() into full buffer");
    buffer = curr_token;
    full = true;
}

Token Token_stream::get() { // read chars from cin and compose tokens
    if (full) { // token in buffer
        full = false;   // read from cin
        return buffer; // return token from buffer
    }
    char ch;
    std::cin >> ch;
    switch (ch) {
        case ';':   // print
        case 'q':   // quit
        case '*': case '/': case '+': case '-':
        case '(': case ')': case '=': case '%':
        case '^':             return Token(ch);
        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9': case '.':
        {
            std::cin.putback(ch); // put digit back into input stream
            double val;
            std::cin >> val;
            return Token(number,val);
        }
        default:
            error("Bad token\n");
    }
    return false;
}

//double num_val;
Token_stream ts;
double expression();

/* Parsing (bottom-up)
 4) Expression: must be a term or end with a term
        Term
        Expression '+' term
        Expression '-' term
 3) Term: must be a primary or end with a primary
        Primary
        Term '*' primary
        Term '/' primary
        Term '%' primary
 2) Primary: a number or '(' followed by an expression followed by ')'
        Number
        '(' expression')'
 1) Number:
        floating-point-literal
 */

/* e.g. 45 + 11 * 7
// 45: number -> primary -> term -> expression followed by '+', 11=term: (expression+term=45+11)
// 11: number -> primary -> term followed by '*', 7=primary: (term * primary = 11 * 7)
// 45+11*7 is an expression where 3)(11*7) will be evaluated before the addition 4)45+(11*7)
*/

double primary() { // handles numbers and parentheses, calls expression().
    Token curr_token = ts.get(); // get token
    switch (curr_token.kind) {
        case number: {
            return curr_token.value; //return number
        }
        case MINUS:
            return -primary();
        case LP: {  // handle << '(' expression ')' >>
            auto e = expression();
            curr_token = ts.get();
            if (curr_token.kind != RP) error("')' missing\n");
            return e;
        }
        default:
            error("Primary expected!\n");
    }
    return false;
}

// multiplication and division has higher precedence than addition and subtraction.
double term() { // handles '*', '/' and '%'. calls primary
    double left = primary();
    Token curr_token = ts.get(); // get next token
    while(true) {
        switch (curr_token.kind) {
                //  Term '*' primary
            case mul:
                left *= term();
                curr_token = ts.get();
                break;
                
                
            case MOD: {
                auto d = term();
                int a=left;
                int b=d;
                left = a%b;
                curr_token = ts.get();
                break;
            }
            case power: // use pow not xor
                left = pow(left,term());
                curr_token = ts.get();
                break;
                
            case DIV:
                if (auto d = term()) {
                    left /= d;
                    curr_token = ts.get();
                    break;
                }
                error("do not divide by 0...\n");
            default:
                ts.putback(curr_token);
                return left;
        }
    }
}

// add and subtract
double expression() {
    double left = term(); // evaluate a Term
    Token curr_token = ts.get(); // get next token
    while (true) {
        switch (curr_token.kind) { // check which kind of token it is.
            case PLUS:
                left += term();
                curr_token = ts.get();
                break;
            case MINUS:
                left -= term();
                curr_token = ts.get();
                break;
            default:
                ts.putback(curr_token); // put token back into token stream
                return left; // return final answer.
        }
    }
}


int main() {
    double val = 0.0;
    try {
        while (std::cin) {
            std::cout << "Enter expression: \n";
            Token curr_token = ts.get();
            if(curr_token.kind == 'q') break;
            if(curr_token.kind == ';') {
                std::cout<<"=" << val << std::endl;
            }
            else {
                ts.putback(curr_token);
                }
            val = expression();
            }
        }
    catch (std::exception &e) {
        std::cerr<<"E: "<<e.what()<<'\n';
        return 1;
    }
}
