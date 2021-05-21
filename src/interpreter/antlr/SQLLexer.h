
// Generated from /Users/cobalt/Projects/courses/database-system/minisql/src/interpreter/SQL.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  SQLLexer : public antlr4::Lexer {
public:
  enum {
    DOT = 1, COMMA = 2, SEMICOLON = 3, UNDERSCORE = 4, LPARN = 5, RPARN = 6, 
    STAR = 7, INT_NUMBER = 8, DECIMAL_NUMBER = 9, FLOAT_NUMBER = 10, CREATE = 11, 
    DROP = 12, SELECT = 13, INSERT = 14, DELETE = 15, QUIT = 16, EXEC_FILE = 17, 
    FROM = 18, WHERE = 19, ON = 20, INTO = 21, TABLE = 22, KEY = 23, INDEX = 24, 
    VALUES = 25, PRIMARY = 26, UNIQUE = 27, INT = 28, CHAR = 29, FLOAT = 30, 
    AND = 31, EQUAL = 32, NOT_EQUAL = 33, LESS_THAN = 34, GREATER_THAN = 35, 
    LESS_THAN_OR_EQUAL = 36, GREATER_THAN_OR_EQUAL = 37, WHITESPACE = 38, 
    IDENTIFIER = 39, BACKTICK_QUOTED_ID = 40, DOUBLE_QUOTED_STRING = 41, 
    SINGLE_QUOTED_STRING = 42, STRING = 43
  };

  SQLLexer(antlr4::CharStream *input);
  ~SQLLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

