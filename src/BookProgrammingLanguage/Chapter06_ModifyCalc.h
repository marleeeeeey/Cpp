#pragma once

#include "StdHelper.hpp"

// Проект не доделан.
// Остановился на возможности добавления функций

namespace StProgLangChapter06_ModifyCalc
{
    enum Token_value
    {
        NONE,
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
        LP_FIG = '{',
        RP_FIG = '}',
        CALLFN = '@',
    };
       

    ostream & operator<<(std::ostream & os, const Token_value & tVal)
    {
        static std::map<Token_value, string> names
        { 
            { NONE  , "NONE  " },
            { NAME  , "NAME  " },
            { NUMBER, "NUMBER" },
            { END   , "END   " },
            { PLUS  , "PLUS  " },
            { MINUS , "MINUS " },
            { MUL   , "MUL   " },
            { DIV   , "DIV   " },
            { PRINT , "PRINT " },
            { ASSIGN, "ASSIGN" },
            { LP    , "LP    " },
            { RP    , "RP    " },
            { LP_FIG, "LP_FIG" },
            { RP_FIG, "RP_FIG" },
        };

        os << "<" << names[tVal] << ">";

        return os;
    }

    struct Token
    {
        Token(Token_value type = NONE, double value = 0, string name = "")
            : m_type(type)
            , m_name(name)
            , m_value(value)
        { }

        Token(Token_value type, string name)
            : m_type(type)
            , m_name(name)
        { }

        bool operator==(Token_value otherType) const 
        {
            return m_type == otherType;
        }

        Token_value m_type = NONE;
        string      m_name = "";
        double      m_value = 0;
    };

    ostream & operator<<(std::ostream & os, const Token & token)
    {
        os
            //<< "Type= "  
            << token.m_type << "   "
            << "Name="   << setw(10) << token.m_name << "   "
            << "Value="  << setw(5) << token.m_value
            ;

        return os;
    }

    typedef vector<Token> Tokens;


    class TokenThread
    {
    public:

        void append(const Token & t)
        {
            m_tokens.push_back(t);
        }

        void pop()
        {
            if (m_index < m_tokens.size())
                m_index++;
        }

        const Token & current()
        {
            return m_tokens[m_index];
        }

    private:
        friend ostream & operator<<(ostream & os, const TokenThread & tt);
        Tokens m_tokens;
        size_t m_index = 0;
    };

    ostream & operator<<(ostream & os, const TokenThread & tt)
    {
        AVAR(tt.m_index);
        AVAR(tt.m_tokens);

        return os;
    }

    enum TokenThreadName
    {
        e_global,
        e_fun,
    };

    typedef map<TokenThreadName, TokenThread> TokenThreads;


    // FIXME
    Tokens       g_tokens;          // Удалить 
    TokenThreads g_tokenThreads;    // И заменить на этот

    int                 g_errorNumber = 0;
    map<string, double> g_varTable;
    map<string, string> g_funcTable;
    istream*            g_input       = nullptr;

    inline istream & inp() { return *g_input; }

    double expr(bool get);
    double term(bool get);
    double prim(bool get);
    Token_value get_token(TokenThreadName ttn = e_global);
    double error(const string & s);
    Token_value addToken(const Token & t, TokenThreadName ttn = e_global);
    Token_value lastTokenType(TokenThreadName ttn = e_global);
    void loadAllTokens();

    static int resolve(int argc = 0, char** argv = nullptr)
    {
        AFUN;
        AVAR(argc);

        switch (argc)
        {
            case 1:
                AMSG("Input from console");
                g_input = &cin;
                break;
            case 2:
                AMSG("Input from command line");
                AVAR(argv[1]);
                g_input = new stringstream(argv[1]);
                break;
            default:
                error("to many arguments or null arguments");
                return 1;
        }

        g_varTable["pi"] = 3.14;
        g_varTable["e"] = 2.7;

        loadAllTokens();


        while (true)
        {
            Token_value lastToken = get_token();
            if (lastToken == END) break;
            if (lastToken == PRINT) continue;

            double result = expr(false);
            AVAR(result);
        }

        if (g_input != &cin)
            delete g_input;

        AVAR(g_errorNumber);
        return g_errorNumber;
    }

    double expr_base(bool get)
    {
        double left = term(get);

        while (true)
            switch (lastTokenType())
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

    double expr(bool get)
    {
        double exprRet = expr_base(get);
        AVAR(exprRet);
        return exprRet;
    }


    double term_base(bool get)
    {
        double left = prim(get);

        while (true)
            switch (lastTokenType())
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

    double term(bool get)
    {
        double termRet = term_base(get);
        AVAR(termRet);
        return termRet;
    }


    double prim_base(bool get)
    {
        if (get) get_token();

        switch (lastTokenType())
        {
            case NUMBER:
            {
                double v = g_tokens.back().m_value;
                get_token();
                return v;
            }
            case NAME:
            {
                double & v = g_varTable[g_tokens.back().m_name];
                if (get_token() == ASSIGN) v = expr(true);
                return v;
            }
            case MINUS:
                return -prim(true);
            case LP:
            {
                double e = expr(true);
                if (g_tokens.back().m_type != RP) return error("')' expected");
                get_token();
                return e;
            }
            case LP_FIG:
            {                
                g_varTable["funcVar"] = 555;
                
                auto tok = get_token();

                size_t startFunc = g_tokens.size();

                while (tok != RP_FIG)
                    tok = get_token();

                size_t endFunc = g_tokens.size();

                bool isNullFunc = startFunc == endFunc;

                AVAR(isNullFunc);
                AVAR(startFunc);
                AVAR(endFunc);

                return 0;

            }
            case CALLFN:
            {
                return 0;
                break;
            }
            default:
                AVAR(g_tokens.back());
                return error("primary expected");
        }
    }

    double prim(bool get)
    {
        double primRet = prim_base(get);
        AVAR(primRet);
        return primRet;
    }


    Token_value get_token_base()
    {
        char ch = 0;

        do
        {
            if (!inp().get(ch)) 
                return addToken(END);

        } while (ch != '\n' && isspace(ch));

        switch (ch)
        {
            case 0:
                return addToken(END);

            case ';':  case '\n':
                return addToken(PRINT);
                
            case '*':  case '/':  case '+':
            case '-':  case '(':  case ')':
            case '=':  case '{':  case '}':
            case '@':
                return addToken(Token_value(ch));

            case '0':  case '1':  case '2':  case '3':
            case '4':  case '5':  case '6':  case '7':
            case '8':  case '9':  case '.':
                inp().putback(ch);
                double val;
                inp() >> val;
                return addToken(Token(NUMBER, val));

            default:
                if (isalpha(ch))
                {
                    string name;
                    name = ch;
                    while (inp().get(ch) && isalnum(ch))
                        name.push_back(ch);
                    
                    inp().putback(ch);
                    return addToken(Token(NAME, name));
                }
                error("bad token");
                return addToken(PRINT);
        }
    }

    

    Token_value get_token(TokenThreadName ttn)
    {
        g_tokenThreads[ttn].pop();
        return g_tokenThreads[ttn].current().m_type;
    }

    double error(const string & errMsg)
    {
        g_errorNumber++;
        AMSG(errMsg);
        return 1;
    }

    Token_value addToken(const Token & t, TokenThreadName ttn)
    {
        g_tokenThreads[ttn].append(t);

        g_tokens.push_back(t);
        return t.m_type;
    }

    Token_value lastTokenType(TokenThreadName ttn)
    {
        return g_tokenThreads[ttn].current().m_type;
        //return g_tokens.back().m_type;
    }

    void loadAllTokens()
    {
        while (true)
        {
            if(get_token_base() == END) break;
        }
    }

}
