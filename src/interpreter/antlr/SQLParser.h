
// Generated from /Users/cobalt/Projects/courses/database-system/minisql/src/interpreter/SQL.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  SQLParser : public antlr4::Parser {
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

  enum {
    RuleQuery = 0, RuleStatement = 1, RuleCommands = 2, RuleCreateTableStatement = 3, 
    RuleDropTableStatement = 4, RuleCreateIndexStatement = 5, RuleDropIndexStatement = 6, 
    RuleSelectStatement = 7, RuleInsertStatement = 8, RuleDeleteStatement = 9, 
    RuleWhereClause = 10, RuleColumnElement = 11, RuleColumnElementList = 12, 
    RulePrimaryKeyConstraint = 13, RuleCondition = 14, RuleConditionList = 15, 
    RuleAttributeList = 16, RuleIdentifier = 17, RuleDataType = 18, RuleIntType = 19, 
    RuleFloatType = 20, RuleCharType = 21, RuleLiteral = 22, RuleString = 23, 
    RuleNumber = 24, RuleBinaryOperator = 25, RuleFilePath = 26, RuleQuitCommand = 27, 
    RuleExecuteFileCommand = 28
  };

  SQLParser(antlr4::TokenStream *input);
  ~SQLParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class QueryContext;
  class StatementContext;
  class CommandsContext;
  class CreateTableStatementContext;
  class DropTableStatementContext;
  class CreateIndexStatementContext;
  class DropIndexStatementContext;
  class SelectStatementContext;
  class InsertStatementContext;
  class DeleteStatementContext;
  class WhereClauseContext;
  class ColumnElementContext;
  class ColumnElementListContext;
  class PrimaryKeyConstraintContext;
  class ConditionContext;
  class ConditionListContext;
  class AttributeListContext;
  class IdentifierContext;
  class DataTypeContext;
  class IntTypeContext;
  class FloatTypeContext;
  class CharTypeContext;
  class LiteralContext;
  class StringContext;
  class NumberContext;
  class BinaryOperatorContext;
  class FilePathContext;
  class QuitCommandContext;
  class ExecuteFileCommandContext; 

  class  QueryContext : public antlr4::ParserRuleContext {
  public:
    QueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    CommandsContext *commands();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EOF();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QueryContext* query();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CreateTableStatementContext *createTableStatement();
    DropTableStatementContext *dropTableStatement();
    CreateIndexStatementContext *createIndexStatement();
    DropIndexStatementContext *dropIndexStatement();
    SelectStatementContext *selectStatement();
    InsertStatementContext *insertStatement();
    DeleteStatementContext *deleteStatement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  CommandsContext : public antlr4::ParserRuleContext {
  public:
    CommandsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QuitCommandContext *quitCommand();
    ExecuteFileCommandContext *executeFileCommand();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommandsContext* commands();

  class  CreateTableStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *tableName = nullptr;;
    CreateTableStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *TABLE();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *LPARN();
    ColumnElementListContext *columnElementList();
    PrimaryKeyConstraintContext *primaryKeyConstraint();
    antlr4::tree::TerminalNode *RPARN();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateTableStatementContext* createTableStatement();

  class  DropTableStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *tableName = nullptr;;
    DropTableStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *TABLE();
    IdentifierContext *identifier();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropTableStatementContext* dropTableStatement();

  class  CreateIndexStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *indexName = nullptr;;
    SQLParser::IdentifierContext *tableName = nullptr;;
    SQLParser::IdentifierContext *columnName = nullptr;;
    CreateIndexStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    antlr4::tree::TerminalNode *INDEX();
    antlr4::tree::TerminalNode *ON();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *LPARN();
    antlr4::tree::TerminalNode *RPARN();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateIndexStatementContext* createIndexStatement();

  class  DropIndexStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *indexName = nullptr;;
    DropIndexStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *INDEX();
    IdentifierContext *identifier();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropIndexStatementContext* dropIndexStatement();

  class  SelectStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *tableName = nullptr;;
    SelectStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *FROM();
    IdentifierContext *identifier();
    WhereClauseContext *whereClause();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectStatementContext* selectStatement();

  class  InsertStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *tableName = nullptr;;
    InsertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *INTO();
    antlr4::tree::TerminalNode *VALUES();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *LPARN();
    AttributeListContext *attributeList();
    antlr4::tree::TerminalNode *RPARN();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertStatementContext* insertStatement();

  class  DeleteStatementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *tableName = nullptr;;
    DeleteStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *FROM();
    IdentifierContext *identifier();
    WhereClauseContext *whereClause();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteStatementContext* deleteStatement();

  class  WhereClauseContext : public antlr4::ParserRuleContext {
  public:
    WhereClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    ConditionListContext *conditionList();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereClauseContext* whereClause();

  class  ColumnElementContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *columnName = nullptr;;
    antlr4::Token *unique = nullptr;;
    ColumnElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DataTypeContext *dataType();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *UNIQUE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnElementContext* columnElement();

  class  ColumnElementListContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::ColumnElementContext *columnElementContext = nullptr;;
    std::vector<ColumnElementContext *> elements;;
    ColumnElementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    std::vector<ColumnElementContext *> columnElement();
    ColumnElementContext* columnElement(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ColumnElementListContext* columnElementList();

  class  PrimaryKeyConstraintContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *columnName = nullptr;;
    PrimaryKeyConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PRIMARY();
    antlr4::tree::TerminalNode *KEY();
    antlr4::tree::TerminalNode *LPARN();
    antlr4::tree::TerminalNode *RPARN();
    IdentifierContext *identifier();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryKeyConstraintContext* primaryKeyConstraint();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::IdentifierContext *columnName = nullptr;;
    SQLParser::LiteralContext *value = nullptr;;
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BinaryOperatorContext *binaryOperator();
    IdentifierContext *identifier();
    LiteralContext *literal();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  ConditionListContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::ConditionContext *conditionContext = nullptr;;
    std::vector<ConditionContext *> conditions;;
    ConditionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);
    std::vector<ConditionContext *> condition();
    ConditionContext* condition(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionListContext* conditionList();

  class  AttributeListContext : public antlr4::ParserRuleContext {
  public:
    SQLParser::LiteralContext *literalContext = nullptr;;
    std::vector<LiteralContext *> attributes;;
    AttributeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LiteralContext *> literal();
    LiteralContext* literal(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeListContext* attributeList();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *BACKTICK_QUOTED_ID();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  DataTypeContext : public antlr4::ParserRuleContext {
  public:
    DataTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IntTypeContext *intType();
    FloatTypeContext *floatType();
    CharTypeContext *charType();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DataTypeContext* dataType();

  class  IntTypeContext : public antlr4::ParserRuleContext {
  public:
    IntTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntTypeContext* intType();

  class  FloatTypeContext : public antlr4::ParserRuleContext {
  public:
    FloatTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FloatTypeContext* floatType();

  class  CharTypeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *length = nullptr;;
    CharTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *LPARN();
    antlr4::tree::TerminalNode *RPARN();
    antlr4::tree::TerminalNode *INT_NUMBER();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CharTypeContext* charType();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringContext *string();
    NumberContext *number();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SINGLE_QUOTED_STRING();
    antlr4::tree::TerminalNode *DOUBLE_QUOTED_STRING();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringContext* string();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_NUMBER();
    antlr4::tree::TerminalNode *DECIMAL_NUMBER();
    antlr4::tree::TerminalNode *FLOAT_NUMBER();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumberContext* number();

  class  BinaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *NOT_EQUAL();
    antlr4::tree::TerminalNode *LESS_THAN();
    antlr4::tree::TerminalNode *GREATER_THAN();
    antlr4::tree::TerminalNode *LESS_THAN_OR_EQUAL();
    antlr4::tree::TerminalNode *GREATER_THAN_OR_EQUAL();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BinaryOperatorContext* binaryOperator();

  class  FilePathContext : public antlr4::ParserRuleContext {
  public:
    FilePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilePathContext* filePath();

  class  QuitCommandContext : public antlr4::ParserRuleContext {
  public:
    QuitCommandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *QUIT();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuitCommandContext* quitCommand();

  class  ExecuteFileCommandContext : public antlr4::ParserRuleContext {
  public:
    ExecuteFileCommandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXEC_FILE();
    FilePathContext *filePath();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExecuteFileCommandContext* executeFileCommand();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

