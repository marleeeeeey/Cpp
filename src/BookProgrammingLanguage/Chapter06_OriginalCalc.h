#pragma once

#include "StdHelper.hpp"

namespace StProgLangChapter06_OriginalCalc
{
    enum Token_value
    {
        NAME,
        NUMBER,
        END,
        PLUS   = '+',
        MINUS  = '-',
        MUL    = '*',
        DIV    = '/',
        PRINT  = ';',
        ASSIGN = '=',
        LP     = '(',
        RP     = ')',
    };

    Token_value         curr_tok = PRINT;
    int                 no_of_errors = 0;
    double              number_value;
    string              string_value;
    map<string, double> table;
    istream*            input = nullptr;

    inline istream & inp() { return *input; }

    double expr(bool get);
    double term(bool get);
    double prim(bool get);
    Token_value get_token();
    double error(const string & s);


    static int resolve(int argc = 0, char** argv = nullptr)
    {
        AFUN;
        AVAR(argc);

        switch (argc)
        {
            case 1:
                AMSG("Input from console");
                input = &cin;
                break;
            case 2:
                AMSG("Input from command line");
                AVAR(argv[1]);
                input = new stringstream(argv[1]);
                break;
            default:
                error("to many arguments or null arguments");
                return 1;
        }

        table["pi"] = 3.14;
        table["e"] = 2.7;

        while (inp())
        {
            get_token();
            if (curr_tok == END) break;
            if (curr_tok == PRINT) continue;

            double result = expr(false);
            AVAR(result);
        }

        if (input != &cin)
            delete input;

        AVAR(no_of_errors);
        return no_of_errors;
    }

    double expr(bool get)
    {
        double left = term(get);

        while (true)
            switch (curr_tok)
        {
                case PLUS:
                    left += term(true);
                    break;
                case MINUS:
                    left -= term(true);
                    break;
                default:
                    return left;
        }
    }

    double term(bool get)
    {
        double left = prim(get);

        while (true)
            switch (curr_tok)
        {
                case MUL:
                    left *= prim(true);
                    break;
                case DIV:
                    if (double d = prim(true))
                    {
                        left /= d;
                        break;
                    }
                    return error("divide by 0");
                default:
                    return left;
        }
    }


    double prim(bool get)
    {
        if (get) get_token();

        switch (curr_tok)
        {
            case NUMBER:
            {
                double v = number_value;
                get_token();
                return v;
            }
            case NAME:
            {
                double & v = table[string_value];
                if (get_token() == ASSIGN) v = expr(true);
                return v;
            }
            case MINUS:
                return -prim(true);
            case LP:
            {
                double e = expr(true);
                if (curr_tok != RP) return error("')' expected");
                get_token();
                return e;
            }
            default:
                return error("primary expected");
        }
    }

    Token_value get_token()
    {
        char ch = 0;

        do
        {
            if (!inp().get(ch)) return curr_tok = END;
        } while (ch != '\n' && isspace(ch));

        switch (ch)
        {
            case 0:
                return curr_tok = END;

            case ';':  case '\n':
                return curr_tok = PRINT;

            case '*':  case '/':  case '+':
            case '-':  case '(':  case ')':
            case '=':
                return curr_tok = Token_value(ch);

            case '0':  case '1':  case '2':  case '3':
            case '4':  case '5':  case '6':  case '7':
            case '8':  case '9':  case '.':
                inp().putback(ch);
                inp() >> number_value;
                return curr_tok = NUMBER;

            default:
                if (isalpha(ch))
                {
                    string_value = ch;
                    while (inp().get(ch) && isalnum(ch))
                        string_value.push_back(ch);

                    inp().putback(ch);
                    return curr_tok = NAME;
                }
                error("bad token");
                return curr_tok = PRINT;
        }
    }

    double error(const string & errMsg)
    {
        no_of_errors++;
        AMSG(errMsg);
        return 1;
    }

}
