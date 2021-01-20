#include <iostream>
using namespace std;

enum punctuationToken : char
{
    NULL_TOKEN     = '\0',
    SPACE          = ' ',
    TAB            = '\t',
    NL             = '\n',

    END_STATEMENT  = ';',
    BEGIN_LIST     = '(',
    END_LIST       = ')',
    BEGIN_SQR      = '[',
    END_SQR        = ']',
    BEGIN_BLOCK    = '{',
    END_BLOCK      = '}',
    COLON          = ':',
    COMMA          = ',',
    HASH           = '#',

    BEGIN_STRING   = '"',
    END_STRING     = BEGIN_STRING,

    ASSIGN         = '=',
    ADD            = '+',
    SUBTRACT       = '-',
    MULTIPLY       = '*',
    DIVIDE         = '/'
};

void whatIGot(punctuationToken T)
{
  //char a = T;
  std::cout << "the T is" << T << '\n';
}

int main(int argc, char const *argv[]) {
  whatIGot(BEGIN_LIST);
  //char a = 'a';
  char a = char(128);
  std::cout << a << '\n';
  return 0;
}
