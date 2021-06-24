
// Generated from SQL.g4 by ANTLR 4.9


#include "SQLVisitor.h"

#include "SQLParser.h"


using namespace antlrcpp;
using namespace antlr4;

SQLParser::SQLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SQLParser::~SQLParser() {
  delete _interpreter;
}

std::string SQLParser::getGrammarFileName() const {
  return "SQL.g4";
}

const std::vector<std::string>& SQLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SQLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- FileContext ------------------------------------------------------------------

SQLParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::FileContext::EOF() {
  return getToken(SQLParser::EOF, 0);
}

std::vector<SQLParser::QueryContext *> SQLParser::FileContext::query() {
  return getRuleContexts<SQLParser::QueryContext>();
}

SQLParser::QueryContext* SQLParser::FileContext::query(size_t i) {
  return getRuleContext<SQLParser::QueryContext>(i);
}


size_t SQLParser::FileContext::getRuleIndex() const {
  return SQLParser::RuleFile;
}


antlrcpp::Any SQLParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::FileContext* SQLParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, SQLParser::RuleFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(58);
      dynamic_cast<FileContext *>(_localctx)->queryContext = query();
      dynamic_cast<FileContext *>(_localctx)->queries.push_back(dynamic_cast<FileContext *>(_localctx)->queryContext);
      setState(61); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SQLParser::CREATE)
      | (1ULL << SQLParser::DROP)
      | (1ULL << SQLParser::SELECT)
      | (1ULL << SQLParser::INSERT)
      | (1ULL << SQLParser::DELETE)
      | (1ULL << SQLParser::QUIT)
      | (1ULL << SQLParser::EXEC_FILE))) != 0));
    setState(63);
    match(SQLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryContext ------------------------------------------------------------------

SQLParser::QueryContext::QueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::QueryContext::SEMICOLON() {
  return getToken(SQLParser::SEMICOLON, 0);
}

SQLParser::StatementContext* SQLParser::QueryContext::statement() {
  return getRuleContext<SQLParser::StatementContext>(0);
}

SQLParser::CommandsContext* SQLParser::QueryContext::commands() {
  return getRuleContext<SQLParser::CommandsContext>(0);
}


size_t SQLParser::QueryContext::getRuleIndex() const {
  return SQLParser::RuleQuery;
}


antlrcpp::Any SQLParser::QueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitQuery(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::QueryContext* SQLParser::query() {
  QueryContext *_localctx = _tracker.createInstance<QueryContext>(_ctx, getState());
  enterRule(_localctx, 2, SQLParser::RuleQuery);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::CREATE:
      case SQLParser::DROP:
      case SQLParser::SELECT:
      case SQLParser::INSERT:
      case SQLParser::DELETE: {
        setState(65);
        statement();
        break;
      }

      case SQLParser::QUIT:
      case SQLParser::EXEC_FILE: {
        setState(66);
        commands();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(69);
    match(SQLParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

SQLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::CreateTableStatementContext* SQLParser::StatementContext::createTableStatement() {
  return getRuleContext<SQLParser::CreateTableStatementContext>(0);
}

SQLParser::DropTableStatementContext* SQLParser::StatementContext::dropTableStatement() {
  return getRuleContext<SQLParser::DropTableStatementContext>(0);
}

SQLParser::CreateIndexStatementContext* SQLParser::StatementContext::createIndexStatement() {
  return getRuleContext<SQLParser::CreateIndexStatementContext>(0);
}

SQLParser::DropIndexStatementContext* SQLParser::StatementContext::dropIndexStatement() {
  return getRuleContext<SQLParser::DropIndexStatementContext>(0);
}

SQLParser::SelectStatementContext* SQLParser::StatementContext::selectStatement() {
  return getRuleContext<SQLParser::SelectStatementContext>(0);
}

SQLParser::InsertStatementContext* SQLParser::StatementContext::insertStatement() {
  return getRuleContext<SQLParser::InsertStatementContext>(0);
}

SQLParser::DeleteStatementContext* SQLParser::StatementContext::deleteStatement() {
  return getRuleContext<SQLParser::DeleteStatementContext>(0);
}


size_t SQLParser::StatementContext::getRuleIndex() const {
  return SQLParser::RuleStatement;
}


antlrcpp::Any SQLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::StatementContext* SQLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, SQLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(78);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(71);
      createTableStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(72);
      dropTableStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(73);
      createIndexStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(74);
      dropIndexStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(75);
      selectStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(76);
      insertStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(77);
      deleteStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommandsContext ------------------------------------------------------------------

SQLParser::CommandsContext::CommandsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::QuitCommandContext* SQLParser::CommandsContext::quitCommand() {
  return getRuleContext<SQLParser::QuitCommandContext>(0);
}

SQLParser::ExecuteFileCommandContext* SQLParser::CommandsContext::executeFileCommand() {
  return getRuleContext<SQLParser::ExecuteFileCommandContext>(0);
}


size_t SQLParser::CommandsContext::getRuleIndex() const {
  return SQLParser::RuleCommands;
}


antlrcpp::Any SQLParser::CommandsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCommands(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::CommandsContext* SQLParser::commands() {
  CommandsContext *_localctx = _tracker.createInstance<CommandsContext>(_ctx, getState());
  enterRule(_localctx, 6, SQLParser::RuleCommands);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(82);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::QUIT: {
        enterOuterAlt(_localctx, 1);
        setState(80);
        quitCommand();
        break;
      }

      case SQLParser::EXEC_FILE: {
        enterOuterAlt(_localctx, 2);
        setState(81);
        executeFileCommand();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateTableStatementContext ------------------------------------------------------------------

SQLParser::CreateTableStatementContext::CreateTableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::CreateTableStatementContext::CREATE() {
  return getToken(SQLParser::CREATE, 0);
}

tree::TerminalNode* SQLParser::CreateTableStatementContext::TABLE() {
  return getToken(SQLParser::TABLE, 0);
}

SQLParser::IdentifierContext* SQLParser::CreateTableStatementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}

tree::TerminalNode* SQLParser::CreateTableStatementContext::LPARN() {
  return getToken(SQLParser::LPARN, 0);
}

SQLParser::ColumnElementListContext* SQLParser::CreateTableStatementContext::columnElementList() {
  return getRuleContext<SQLParser::ColumnElementListContext>(0);
}

SQLParser::PrimaryKeyConstraintContext* SQLParser::CreateTableStatementContext::primaryKeyConstraint() {
  return getRuleContext<SQLParser::PrimaryKeyConstraintContext>(0);
}

tree::TerminalNode* SQLParser::CreateTableStatementContext::RPARN() {
  return getToken(SQLParser::RPARN, 0);
}


size_t SQLParser::CreateTableStatementContext::getRuleIndex() const {
  return SQLParser::RuleCreateTableStatement;
}


antlrcpp::Any SQLParser::CreateTableStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCreateTableStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::CreateTableStatementContext* SQLParser::createTableStatement() {
  CreateTableStatementContext *_localctx = _tracker.createInstance<CreateTableStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, SQLParser::RuleCreateTableStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(SQLParser::CREATE);
    setState(85);
    match(SQLParser::TABLE);
    setState(86);
    dynamic_cast<CreateTableStatementContext *>(_localctx)->tableName = identifier();

    setState(87);
    match(SQLParser::LPARN);
    setState(88);
    columnElementList();
    setState(89);
    primaryKeyConstraint();
    setState(90);
    match(SQLParser::RPARN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropTableStatementContext ------------------------------------------------------------------

SQLParser::DropTableStatementContext::DropTableStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::DropTableStatementContext::DROP() {
  return getToken(SQLParser::DROP, 0);
}

tree::TerminalNode* SQLParser::DropTableStatementContext::TABLE() {
  return getToken(SQLParser::TABLE, 0);
}

SQLParser::IdentifierContext* SQLParser::DropTableStatementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}


size_t SQLParser::DropTableStatementContext::getRuleIndex() const {
  return SQLParser::RuleDropTableStatement;
}


antlrcpp::Any SQLParser::DropTableStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDropTableStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::DropTableStatementContext* SQLParser::dropTableStatement() {
  DropTableStatementContext *_localctx = _tracker.createInstance<DropTableStatementContext>(_ctx, getState());
  enterRule(_localctx, 10, SQLParser::RuleDropTableStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(SQLParser::DROP);
    setState(93);
    match(SQLParser::TABLE);
    setState(94);
    dynamic_cast<DropTableStatementContext *>(_localctx)->tableName = identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateIndexStatementContext ------------------------------------------------------------------

SQLParser::CreateIndexStatementContext::CreateIndexStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::CreateIndexStatementContext::CREATE() {
  return getToken(SQLParser::CREATE, 0);
}

tree::TerminalNode* SQLParser::CreateIndexStatementContext::INDEX() {
  return getToken(SQLParser::INDEX, 0);
}

tree::TerminalNode* SQLParser::CreateIndexStatementContext::ON() {
  return getToken(SQLParser::ON, 0);
}

std::vector<SQLParser::IdentifierContext *> SQLParser::CreateIndexStatementContext::identifier() {
  return getRuleContexts<SQLParser::IdentifierContext>();
}

SQLParser::IdentifierContext* SQLParser::CreateIndexStatementContext::identifier(size_t i) {
  return getRuleContext<SQLParser::IdentifierContext>(i);
}

tree::TerminalNode* SQLParser::CreateIndexStatementContext::LPARN() {
  return getToken(SQLParser::LPARN, 0);
}

tree::TerminalNode* SQLParser::CreateIndexStatementContext::RPARN() {
  return getToken(SQLParser::RPARN, 0);
}


size_t SQLParser::CreateIndexStatementContext::getRuleIndex() const {
  return SQLParser::RuleCreateIndexStatement;
}


antlrcpp::Any SQLParser::CreateIndexStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCreateIndexStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::CreateIndexStatementContext* SQLParser::createIndexStatement() {
  CreateIndexStatementContext *_localctx = _tracker.createInstance<CreateIndexStatementContext>(_ctx, getState());
  enterRule(_localctx, 12, SQLParser::RuleCreateIndexStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(SQLParser::CREATE);
    setState(97);
    match(SQLParser::INDEX);
    setState(98);
    dynamic_cast<CreateIndexStatementContext *>(_localctx)->indexName = identifier();
    setState(99);
    match(SQLParser::ON);
    setState(100);
    dynamic_cast<CreateIndexStatementContext *>(_localctx)->tableName = identifier();

    setState(101);
    match(SQLParser::LPARN);
    setState(102);
    dynamic_cast<CreateIndexStatementContext *>(_localctx)->columnName = identifier();
    setState(103);
    match(SQLParser::RPARN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropIndexStatementContext ------------------------------------------------------------------

SQLParser::DropIndexStatementContext::DropIndexStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::DropIndexStatementContext::DROP() {
  return getToken(SQLParser::DROP, 0);
}

tree::TerminalNode* SQLParser::DropIndexStatementContext::INDEX() {
  return getToken(SQLParser::INDEX, 0);
}

SQLParser::IdentifierContext* SQLParser::DropIndexStatementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}


size_t SQLParser::DropIndexStatementContext::getRuleIndex() const {
  return SQLParser::RuleDropIndexStatement;
}


antlrcpp::Any SQLParser::DropIndexStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDropIndexStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::DropIndexStatementContext* SQLParser::dropIndexStatement() {
  DropIndexStatementContext *_localctx = _tracker.createInstance<DropIndexStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, SQLParser::RuleDropIndexStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    match(SQLParser::DROP);
    setState(106);
    match(SQLParser::INDEX);
    setState(107);
    dynamic_cast<DropIndexStatementContext *>(_localctx)->indexName = identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectStatementContext ------------------------------------------------------------------

SQLParser::SelectStatementContext::SelectStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::SelectStatementContext::SELECT() {
  return getToken(SQLParser::SELECT, 0);
}

tree::TerminalNode* SQLParser::SelectStatementContext::STAR() {
  return getToken(SQLParser::STAR, 0);
}

tree::TerminalNode* SQLParser::SelectStatementContext::FROM() {
  return getToken(SQLParser::FROM, 0);
}

SQLParser::IdentifierContext* SQLParser::SelectStatementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}

SQLParser::WhereClauseContext* SQLParser::SelectStatementContext::whereClause() {
  return getRuleContext<SQLParser::WhereClauseContext>(0);
}


size_t SQLParser::SelectStatementContext::getRuleIndex() const {
  return SQLParser::RuleSelectStatement;
}


antlrcpp::Any SQLParser::SelectStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitSelectStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::SelectStatementContext* SQLParser::selectStatement() {
  SelectStatementContext *_localctx = _tracker.createInstance<SelectStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, SQLParser::RuleSelectStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(SQLParser::SELECT);
    setState(110);
    match(SQLParser::STAR);
    setState(111);
    match(SQLParser::FROM);
    setState(112);
    dynamic_cast<SelectStatementContext *>(_localctx)->tableName = identifier();
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::WHERE) {
      setState(113);
      whereClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertStatementContext ------------------------------------------------------------------

SQLParser::InsertStatementContext::InsertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::InsertStatementContext::INSERT() {
  return getToken(SQLParser::INSERT, 0);
}

tree::TerminalNode* SQLParser::InsertStatementContext::INTO() {
  return getToken(SQLParser::INTO, 0);
}

tree::TerminalNode* SQLParser::InsertStatementContext::VALUES() {
  return getToken(SQLParser::VALUES, 0);
}

SQLParser::IdentifierContext* SQLParser::InsertStatementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}

tree::TerminalNode* SQLParser::InsertStatementContext::LPARN() {
  return getToken(SQLParser::LPARN, 0);
}

SQLParser::AttributeListContext* SQLParser::InsertStatementContext::attributeList() {
  return getRuleContext<SQLParser::AttributeListContext>(0);
}

tree::TerminalNode* SQLParser::InsertStatementContext::RPARN() {
  return getToken(SQLParser::RPARN, 0);
}


size_t SQLParser::InsertStatementContext::getRuleIndex() const {
  return SQLParser::RuleInsertStatement;
}


antlrcpp::Any SQLParser::InsertStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitInsertStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::InsertStatementContext* SQLParser::insertStatement() {
  InsertStatementContext *_localctx = _tracker.createInstance<InsertStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, SQLParser::RuleInsertStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(SQLParser::INSERT);
    setState(117);
    match(SQLParser::INTO);
    setState(118);
    dynamic_cast<InsertStatementContext *>(_localctx)->tableName = identifier();
    setState(119);
    match(SQLParser::VALUES);

    setState(120);
    match(SQLParser::LPARN);
    setState(121);
    attributeList();
    setState(122);
    match(SQLParser::RPARN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteStatementContext ------------------------------------------------------------------

SQLParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::DeleteStatementContext::DELETE() {
  return getToken(SQLParser::DELETE, 0);
}

tree::TerminalNode* SQLParser::DeleteStatementContext::FROM() {
  return getToken(SQLParser::FROM, 0);
}

SQLParser::IdentifierContext* SQLParser::DeleteStatementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}

SQLParser::WhereClauseContext* SQLParser::DeleteStatementContext::whereClause() {
  return getRuleContext<SQLParser::WhereClauseContext>(0);
}


size_t SQLParser::DeleteStatementContext::getRuleIndex() const {
  return SQLParser::RuleDeleteStatement;
}


antlrcpp::Any SQLParser::DeleteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDeleteStatement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::DeleteStatementContext* SQLParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, SQLParser::RuleDeleteStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    match(SQLParser::DELETE);
    setState(125);
    match(SQLParser::FROM);
    setState(126);
    dynamic_cast<DeleteStatementContext *>(_localctx)->tableName = identifier();
    setState(128);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::WHERE) {
      setState(127);
      whereClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereClauseContext ------------------------------------------------------------------

SQLParser::WhereClauseContext::WhereClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::WhereClauseContext::WHERE() {
  return getToken(SQLParser::WHERE, 0);
}

SQLParser::ConditionListContext* SQLParser::WhereClauseContext::conditionList() {
  return getRuleContext<SQLParser::ConditionListContext>(0);
}


size_t SQLParser::WhereClauseContext::getRuleIndex() const {
  return SQLParser::RuleWhereClause;
}


antlrcpp::Any SQLParser::WhereClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitWhereClause(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::WhereClauseContext* SQLParser::whereClause() {
  WhereClauseContext *_localctx = _tracker.createInstance<WhereClauseContext>(_ctx, getState());
  enterRule(_localctx, 22, SQLParser::RuleWhereClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(SQLParser::WHERE);
    setState(131);
    conditionList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnElementContext ------------------------------------------------------------------

SQLParser::ColumnElementContext::ColumnElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::DataTypeContext* SQLParser::ColumnElementContext::dataType() {
  return getRuleContext<SQLParser::DataTypeContext>(0);
}

SQLParser::IdentifierContext* SQLParser::ColumnElementContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}

tree::TerminalNode* SQLParser::ColumnElementContext::UNIQUE() {
  return getToken(SQLParser::UNIQUE, 0);
}


size_t SQLParser::ColumnElementContext::getRuleIndex() const {
  return SQLParser::RuleColumnElement;
}


antlrcpp::Any SQLParser::ColumnElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitColumnElement(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ColumnElementContext* SQLParser::columnElement() {
  ColumnElementContext *_localctx = _tracker.createInstance<ColumnElementContext>(_ctx, getState());
  enterRule(_localctx, 24, SQLParser::RuleColumnElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    dynamic_cast<ColumnElementContext *>(_localctx)->columnName = identifier();
    setState(134);
    dataType();
    setState(136);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SQLParser::UNIQUE) {
      setState(135);
      dynamic_cast<ColumnElementContext *>(_localctx)->unique = match(SQLParser::UNIQUE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnElementListContext ------------------------------------------------------------------

SQLParser::ColumnElementListContext::ColumnElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SQLParser::ColumnElementListContext::COMMA() {
  return getTokens(SQLParser::COMMA);
}

tree::TerminalNode* SQLParser::ColumnElementListContext::COMMA(size_t i) {
  return getToken(SQLParser::COMMA, i);
}

std::vector<SQLParser::ColumnElementContext *> SQLParser::ColumnElementListContext::columnElement() {
  return getRuleContexts<SQLParser::ColumnElementContext>();
}

SQLParser::ColumnElementContext* SQLParser::ColumnElementListContext::columnElement(size_t i) {
  return getRuleContext<SQLParser::ColumnElementContext>(i);
}


size_t SQLParser::ColumnElementListContext::getRuleIndex() const {
  return SQLParser::RuleColumnElementList;
}


antlrcpp::Any SQLParser::ColumnElementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitColumnElementList(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ColumnElementListContext* SQLParser::columnElementList() {
  ColumnElementListContext *_localctx = _tracker.createInstance<ColumnElementListContext>(_ctx, getState());
  enterRule(_localctx, 26, SQLParser::RuleColumnElementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(138);
      dynamic_cast<ColumnElementListContext *>(_localctx)->columnElementContext = columnElement();
      dynamic_cast<ColumnElementListContext *>(_localctx)->elements.push_back(dynamic_cast<ColumnElementListContext *>(_localctx)->columnElementContext);
      setState(139);
      match(SQLParser::COMMA);
      setState(143); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == SQLParser::IDENTIFIER

    || _la == SQLParser::BACKTICK_QUOTED_ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryKeyConstraintContext ------------------------------------------------------------------

SQLParser::PrimaryKeyConstraintContext::PrimaryKeyConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::PrimaryKeyConstraintContext::PRIMARY() {
  return getToken(SQLParser::PRIMARY, 0);
}

tree::TerminalNode* SQLParser::PrimaryKeyConstraintContext::KEY() {
  return getToken(SQLParser::KEY, 0);
}

tree::TerminalNode* SQLParser::PrimaryKeyConstraintContext::LPARN() {
  return getToken(SQLParser::LPARN, 0);
}

tree::TerminalNode* SQLParser::PrimaryKeyConstraintContext::RPARN() {
  return getToken(SQLParser::RPARN, 0);
}

SQLParser::IdentifierContext* SQLParser::PrimaryKeyConstraintContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}


size_t SQLParser::PrimaryKeyConstraintContext::getRuleIndex() const {
  return SQLParser::RulePrimaryKeyConstraint;
}


antlrcpp::Any SQLParser::PrimaryKeyConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitPrimaryKeyConstraint(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::PrimaryKeyConstraintContext* SQLParser::primaryKeyConstraint() {
  PrimaryKeyConstraintContext *_localctx = _tracker.createInstance<PrimaryKeyConstraintContext>(_ctx, getState());
  enterRule(_localctx, 28, SQLParser::RulePrimaryKeyConstraint);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(SQLParser::PRIMARY);
    setState(146);
    match(SQLParser::KEY);
    setState(147);
    match(SQLParser::LPARN);
    setState(148);
    dynamic_cast<PrimaryKeyConstraintContext *>(_localctx)->columnName = identifier();
    setState(149);
    match(SQLParser::RPARN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

SQLParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::BinaryOperatorContext* SQLParser::ConditionContext::binaryOperator() {
  return getRuleContext<SQLParser::BinaryOperatorContext>(0);
}

SQLParser::IdentifierContext* SQLParser::ConditionContext::identifier() {
  return getRuleContext<SQLParser::IdentifierContext>(0);
}

SQLParser::LiteralContext* SQLParser::ConditionContext::literal() {
  return getRuleContext<SQLParser::LiteralContext>(0);
}


size_t SQLParser::ConditionContext::getRuleIndex() const {
  return SQLParser::RuleCondition;
}


antlrcpp::Any SQLParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ConditionContext* SQLParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 30, SQLParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    dynamic_cast<ConditionContext *>(_localctx)->columnName = identifier();
    setState(152);
    binaryOperator();
    setState(153);
    dynamic_cast<ConditionContext *>(_localctx)->value = literal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionListContext ------------------------------------------------------------------

SQLParser::ConditionListContext::ConditionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SQLParser::ConditionListContext::AND() {
  return getTokens(SQLParser::AND);
}

tree::TerminalNode* SQLParser::ConditionListContext::AND(size_t i) {
  return getToken(SQLParser::AND, i);
}

std::vector<SQLParser::ConditionContext *> SQLParser::ConditionListContext::condition() {
  return getRuleContexts<SQLParser::ConditionContext>();
}

SQLParser::ConditionContext* SQLParser::ConditionListContext::condition(size_t i) {
  return getRuleContext<SQLParser::ConditionContext>(i);
}


size_t SQLParser::ConditionListContext::getRuleIndex() const {
  return SQLParser::RuleConditionList;
}


antlrcpp::Any SQLParser::ConditionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitConditionList(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ConditionListContext* SQLParser::conditionList() {
  ConditionListContext *_localctx = _tracker.createInstance<ConditionListContext>(_ctx, getState());
  enterRule(_localctx, 32, SQLParser::RuleConditionList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(160);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(155);
        dynamic_cast<ConditionListContext *>(_localctx)->conditionContext = condition();
        dynamic_cast<ConditionListContext *>(_localctx)->conditions.push_back(dynamic_cast<ConditionListContext *>(_localctx)->conditionContext);
        setState(156);
        match(SQLParser::AND); 
      }
      setState(162);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }

    setState(163);
    dynamic_cast<ConditionListContext *>(_localctx)->conditionContext = condition();
    dynamic_cast<ConditionListContext *>(_localctx)->conditions.push_back(dynamic_cast<ConditionListContext *>(_localctx)->conditionContext);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeListContext ------------------------------------------------------------------

SQLParser::AttributeListContext::AttributeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SQLParser::LiteralContext *> SQLParser::AttributeListContext::literal() {
  return getRuleContexts<SQLParser::LiteralContext>();
}

SQLParser::LiteralContext* SQLParser::AttributeListContext::literal(size_t i) {
  return getRuleContext<SQLParser::LiteralContext>(i);
}

std::vector<tree::TerminalNode *> SQLParser::AttributeListContext::COMMA() {
  return getTokens(SQLParser::COMMA);
}

tree::TerminalNode* SQLParser::AttributeListContext::COMMA(size_t i) {
  return getToken(SQLParser::COMMA, i);
}


size_t SQLParser::AttributeListContext::getRuleIndex() const {
  return SQLParser::RuleAttributeList;
}


antlrcpp::Any SQLParser::AttributeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitAttributeList(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::AttributeListContext* SQLParser::attributeList() {
  AttributeListContext *_localctx = _tracker.createInstance<AttributeListContext>(_ctx, getState());
  enterRule(_localctx, 34, SQLParser::RuleAttributeList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(170);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(165);
        dynamic_cast<AttributeListContext *>(_localctx)->literalContext = literal();
        dynamic_cast<AttributeListContext *>(_localctx)->attributes.push_back(dynamic_cast<AttributeListContext *>(_localctx)->literalContext);
        setState(166);
        match(SQLParser::COMMA); 
      }
      setState(172);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(173);
    dynamic_cast<AttributeListContext *>(_localctx)->literalContext = literal();
    dynamic_cast<AttributeListContext *>(_localctx)->attributes.push_back(dynamic_cast<AttributeListContext *>(_localctx)->literalContext);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

SQLParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::IdentifierContext::IDENTIFIER() {
  return getToken(SQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* SQLParser::IdentifierContext::BACKTICK_QUOTED_ID() {
  return getToken(SQLParser::BACKTICK_QUOTED_ID, 0);
}


size_t SQLParser::IdentifierContext::getRuleIndex() const {
  return SQLParser::RuleIdentifier;
}


antlrcpp::Any SQLParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::IdentifierContext* SQLParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 36, SQLParser::RuleIdentifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    _la = _input->LA(1);
    if (!(_la == SQLParser::IDENTIFIER

    || _la == SQLParser::BACKTICK_QUOTED_ID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataTypeContext ------------------------------------------------------------------

SQLParser::DataTypeContext::DataTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::IntTypeContext* SQLParser::DataTypeContext::intType() {
  return getRuleContext<SQLParser::IntTypeContext>(0);
}

SQLParser::FloatTypeContext* SQLParser::DataTypeContext::floatType() {
  return getRuleContext<SQLParser::FloatTypeContext>(0);
}

SQLParser::CharTypeContext* SQLParser::DataTypeContext::charType() {
  return getRuleContext<SQLParser::CharTypeContext>(0);
}


size_t SQLParser::DataTypeContext::getRuleIndex() const {
  return SQLParser::RuleDataType;
}


antlrcpp::Any SQLParser::DataTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitDataType(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::DataTypeContext* SQLParser::dataType() {
  DataTypeContext *_localctx = _tracker.createInstance<DataTypeContext>(_ctx, getState());
  enterRule(_localctx, 38, SQLParser::RuleDataType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::INT: {
        enterOuterAlt(_localctx, 1);
        setState(177);
        intType();
        break;
      }

      case SQLParser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(178);
        floatType();
        break;
      }

      case SQLParser::CHAR: {
        enterOuterAlt(_localctx, 3);
        setState(179);
        charType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntTypeContext ------------------------------------------------------------------

SQLParser::IntTypeContext::IntTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::IntTypeContext::INT() {
  return getToken(SQLParser::INT, 0);
}


size_t SQLParser::IntTypeContext::getRuleIndex() const {
  return SQLParser::RuleIntType;
}


antlrcpp::Any SQLParser::IntTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitIntType(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::IntTypeContext* SQLParser::intType() {
  IntTypeContext *_localctx = _tracker.createInstance<IntTypeContext>(_ctx, getState());
  enterRule(_localctx, 40, SQLParser::RuleIntType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    match(SQLParser::INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatTypeContext ------------------------------------------------------------------

SQLParser::FloatTypeContext::FloatTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::FloatTypeContext::FLOAT() {
  return getToken(SQLParser::FLOAT, 0);
}


size_t SQLParser::FloatTypeContext::getRuleIndex() const {
  return SQLParser::RuleFloatType;
}


antlrcpp::Any SQLParser::FloatTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitFloatType(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::FloatTypeContext* SQLParser::floatType() {
  FloatTypeContext *_localctx = _tracker.createInstance<FloatTypeContext>(_ctx, getState());
  enterRule(_localctx, 42, SQLParser::RuleFloatType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(SQLParser::FLOAT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharTypeContext ------------------------------------------------------------------

SQLParser::CharTypeContext::CharTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::CharTypeContext::CHAR() {
  return getToken(SQLParser::CHAR, 0);
}

tree::TerminalNode* SQLParser::CharTypeContext::LPARN() {
  return getToken(SQLParser::LPARN, 0);
}

tree::TerminalNode* SQLParser::CharTypeContext::RPARN() {
  return getToken(SQLParser::RPARN, 0);
}

tree::TerminalNode* SQLParser::CharTypeContext::INT_NUMBER() {
  return getToken(SQLParser::INT_NUMBER, 0);
}


size_t SQLParser::CharTypeContext::getRuleIndex() const {
  return SQLParser::RuleCharType;
}


antlrcpp::Any SQLParser::CharTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitCharType(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::CharTypeContext* SQLParser::charType() {
  CharTypeContext *_localctx = _tracker.createInstance<CharTypeContext>(_ctx, getState());
  enterRule(_localctx, 44, SQLParser::RuleCharType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(SQLParser::CHAR);
    setState(187);
    match(SQLParser::LPARN);
    setState(188);
    dynamic_cast<CharTypeContext *>(_localctx)->length = match(SQLParser::INT_NUMBER);
    setState(189);
    match(SQLParser::RPARN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

SQLParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SQLParser::StringContext* SQLParser::LiteralContext::string() {
  return getRuleContext<SQLParser::StringContext>(0);
}

SQLParser::NumberContext* SQLParser::LiteralContext::number() {
  return getRuleContext<SQLParser::NumberContext>(0);
}


size_t SQLParser::LiteralContext::getRuleIndex() const {
  return SQLParser::RuleLiteral;
}


antlrcpp::Any SQLParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::LiteralContext* SQLParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 46, SQLParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(193);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SQLParser::DOUBLE_QUOTED_STRING:
      case SQLParser::SINGLE_QUOTED_STRING: {
        enterOuterAlt(_localctx, 1);
        setState(191);
        string();
        break;
      }

      case SQLParser::INT_NUMBER:
      case SQLParser::DECIMAL_NUMBER:
      case SQLParser::FLOAT_NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(192);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

SQLParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::StringContext::SINGLE_QUOTED_STRING() {
  return getToken(SQLParser::SINGLE_QUOTED_STRING, 0);
}

tree::TerminalNode* SQLParser::StringContext::DOUBLE_QUOTED_STRING() {
  return getToken(SQLParser::DOUBLE_QUOTED_STRING, 0);
}


size_t SQLParser::StringContext::getRuleIndex() const {
  return SQLParser::RuleString;
}


antlrcpp::Any SQLParser::StringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitString(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::StringContext* SQLParser::string() {
  StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 48, SQLParser::RuleString);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    _la = _input->LA(1);
    if (!(_la == SQLParser::DOUBLE_QUOTED_STRING

    || _la == SQLParser::SINGLE_QUOTED_STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

SQLParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::NumberContext::INT_NUMBER() {
  return getToken(SQLParser::INT_NUMBER, 0);
}

tree::TerminalNode* SQLParser::NumberContext::DECIMAL_NUMBER() {
  return getToken(SQLParser::DECIMAL_NUMBER, 0);
}

tree::TerminalNode* SQLParser::NumberContext::FLOAT_NUMBER() {
  return getToken(SQLParser::FLOAT_NUMBER, 0);
}


size_t SQLParser::NumberContext::getRuleIndex() const {
  return SQLParser::RuleNumber;
}


antlrcpp::Any SQLParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::NumberContext* SQLParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 50, SQLParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SQLParser::INT_NUMBER)
      | (1ULL << SQLParser::DECIMAL_NUMBER)
      | (1ULL << SQLParser::FLOAT_NUMBER))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BinaryOperatorContext ------------------------------------------------------------------

SQLParser::BinaryOperatorContext::BinaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::BinaryOperatorContext::EQUAL() {
  return getToken(SQLParser::EQUAL, 0);
}

tree::TerminalNode* SQLParser::BinaryOperatorContext::NOT_EQUAL() {
  return getToken(SQLParser::NOT_EQUAL, 0);
}

tree::TerminalNode* SQLParser::BinaryOperatorContext::LESS_THAN() {
  return getToken(SQLParser::LESS_THAN, 0);
}

tree::TerminalNode* SQLParser::BinaryOperatorContext::GREATER_THAN() {
  return getToken(SQLParser::GREATER_THAN, 0);
}

tree::TerminalNode* SQLParser::BinaryOperatorContext::LESS_THAN_OR_EQUAL() {
  return getToken(SQLParser::LESS_THAN_OR_EQUAL, 0);
}

tree::TerminalNode* SQLParser::BinaryOperatorContext::GREATER_THAN_OR_EQUAL() {
  return getToken(SQLParser::GREATER_THAN_OR_EQUAL, 0);
}


size_t SQLParser::BinaryOperatorContext::getRuleIndex() const {
  return SQLParser::RuleBinaryOperator;
}


antlrcpp::Any SQLParser::BinaryOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitBinaryOperator(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::BinaryOperatorContext* SQLParser::binaryOperator() {
  BinaryOperatorContext *_localctx = _tracker.createInstance<BinaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 52, SQLParser::RuleBinaryOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SQLParser::EQUAL)
      | (1ULL << SQLParser::NOT_EQUAL)
      | (1ULL << SQLParser::LESS_THAN)
      | (1ULL << SQLParser::GREATER_THAN)
      | (1ULL << SQLParser::LESS_THAN_OR_EQUAL)
      | (1ULL << SQLParser::GREATER_THAN_OR_EQUAL))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuitCommandContext ------------------------------------------------------------------

SQLParser::QuitCommandContext::QuitCommandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::QuitCommandContext::QUIT() {
  return getToken(SQLParser::QUIT, 0);
}


size_t SQLParser::QuitCommandContext::getRuleIndex() const {
  return SQLParser::RuleQuitCommand;
}


antlrcpp::Any SQLParser::QuitCommandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitQuitCommand(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::QuitCommandContext* SQLParser::quitCommand() {
  QuitCommandContext *_localctx = _tracker.createInstance<QuitCommandContext>(_ctx, getState());
  enterRule(_localctx, 54, SQLParser::RuleQuitCommand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(SQLParser::QUIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExecuteFileCommandContext ------------------------------------------------------------------

SQLParser::ExecuteFileCommandContext::ExecuteFileCommandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SQLParser::ExecuteFileCommandContext::EXEC_FILE() {
  return getToken(SQLParser::EXEC_FILE, 0);
}

SQLParser::StringContext* SQLParser::ExecuteFileCommandContext::string() {
  return getRuleContext<SQLParser::StringContext>(0);
}


size_t SQLParser::ExecuteFileCommandContext::getRuleIndex() const {
  return SQLParser::RuleExecuteFileCommand;
}


antlrcpp::Any SQLParser::ExecuteFileCommandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SQLVisitor*>(visitor))
    return parserVisitor->visitExecuteFileCommand(this);
  else
    return visitor->visitChildren(this);
}

SQLParser::ExecuteFileCommandContext* SQLParser::executeFileCommand() {
  ExecuteFileCommandContext *_localctx = _tracker.createInstance<ExecuteFileCommandContext>(_ctx, getState());
  enterRule(_localctx, 56, SQLParser::RuleExecuteFileCommand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    match(SQLParser::EXEC_FILE);
    setState(204);
    dynamic_cast<ExecuteFileCommandContext *>(_localctx)->filePath = string();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> SQLParser::_decisionToDFA;
atn::PredictionContextCache SQLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SQLParser::_atn;
std::vector<uint16_t> SQLParser::_serializedATN;

std::vector<std::string> SQLParser::_ruleNames = {
  "file", "query", "statement", "commands", "createTableStatement", "dropTableStatement", 
  "createIndexStatement", "dropIndexStatement", "selectStatement", "insertStatement", 
  "deleteStatement", "whereClause", "columnElement", "columnElementList", 
  "primaryKeyConstraint", "condition", "conditionList", "attributeList", 
  "identifier", "dataType", "intType", "floatType", "charType", "literal", 
  "string", "number", "binaryOperator", "quitCommand", "executeFileCommand"
};

std::vector<std::string> SQLParser::_literalNames = {
  "", "'.'", "','", "';'", "'_'", "'('", "')'", "'*'", "", "", "", "'create'", 
  "'drop'", "'select'", "'insert'", "'delete'", "'quit'", "'execfile'", 
  "'from'", "'where'", "'on'", "'into'", "'table'", "'key'", "'index'", 
  "'values'", "'primary'", "'unique'", "'int'", "'char'", "'float'", "'and'", 
  "'='", "'<>'", "'<'", "'>'", "'<='", "'>='"
};

std::vector<std::string> SQLParser::_symbolicNames = {
  "", "DOT", "COMMA", "SEMICOLON", "UNDERSCORE", "LPARN", "RPARN", "STAR", 
  "INT_NUMBER", "DECIMAL_NUMBER", "FLOAT_NUMBER", "CREATE", "DROP", "SELECT", 
  "INSERT", "DELETE", "QUIT", "EXEC_FILE", "FROM", "WHERE", "ON", "INTO", 
  "TABLE", "KEY", "INDEX", "VALUES", "PRIMARY", "UNIQUE", "INT", "CHAR", 
  "FLOAT", "AND", "EQUAL", "NOT_EQUAL", "LESS_THAN", "GREATER_THAN", "LESS_THAN_OR_EQUAL", 
  "GREATER_THAN_OR_EQUAL", "WHITESPACE", "IDENTIFIER", "BACKTICK_QUOTED_ID", 
  "DOUBLE_QUOTED_STRING", "SINGLE_QUOTED_STRING", "STRING"
};

dfa::Vocabulary SQLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SQLParser::_tokenNames;

SQLParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x2d, 0xd1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 
    0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x3, 0x2, 
    0x6, 0x2, 0x3e, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x3f, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x46, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0x51, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x55, 0xa, 0x5, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0x75, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x83, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x8b, 0xa, 0xe, 0x3, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x6, 0xf, 0x90, 0xa, 0xf, 0xd, 0xf, 0xe, 0xf, 0x91, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x7, 0x12, 0xa1, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xa4, 0xb, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xab, 0xa, 
    0x13, 0xc, 0x13, 0xe, 0x13, 0xae, 0xb, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0xb7, 0xa, 
    0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0xc4, 
    0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 
    0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x2, 0x2, 0x1f, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 
    0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x2, 0x6, 0x3, 0x2, 0x29, 
    0x2a, 0x3, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0xa, 0xc, 0x3, 0x2, 0x22, 0x27, 
    0x2, 0xc5, 0x2, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x4, 0x45, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x50, 0x3, 0x2, 0x2, 0x2, 0x8, 0x54, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x56, 0x3, 0x2, 0x2, 0x2, 0xc, 0x5e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x62, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x12, 0x6f, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x76, 0x3, 0x2, 0x2, 0x2, 0x16, 0x7e, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x84, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x87, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x93, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x99, 0x3, 0x2, 0x2, 0x2, 0x22, 0xa2, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0xac, 0x3, 0x2, 0x2, 0x2, 0x26, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x28, 0xb6, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xba, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x30, 0xc3, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x34, 0xc7, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x38, 0xcb, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3e, 0x5, 0x4, 0x3, 0x2, 0x3d, 
    0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 
    0x2, 0x2, 0x2, 0x41, 0x42, 0x7, 0x2, 0x2, 0x3, 0x42, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x43, 0x46, 0x5, 0x6, 0x4, 0x2, 0x44, 0x46, 0x5, 0x8, 0x5, 
    0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x7, 0x5, 0x2, 0x2, 0x48, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x49, 0x51, 0x5, 0xa, 0x6, 0x2, 0x4a, 0x51, 
    0x5, 0xc, 0x7, 0x2, 0x4b, 0x51, 0x5, 0xe, 0x8, 0x2, 0x4c, 0x51, 0x5, 
    0x10, 0x9, 0x2, 0x4d, 0x51, 0x5, 0x12, 0xa, 0x2, 0x4e, 0x51, 0x5, 0x14, 
    0xb, 0x2, 0x4f, 0x51, 0x5, 0x16, 0xc, 0x2, 0x50, 0x49, 0x3, 0x2, 0x2, 
    0x2, 0x50, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x50, 
    0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x52, 0x55, 0x5, 0x38, 0x1d, 0x2, 0x53, 0x55, 0x5, 
    0x3a, 0x1e, 0x2, 0x54, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x53, 0x3, 0x2, 
    0x2, 0x2, 0x55, 0x9, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x7, 0xd, 0x2, 
    0x2, 0x57, 0x58, 0x7, 0x18, 0x2, 0x2, 0x58, 0x59, 0x5, 0x26, 0x14, 0x2, 
    0x59, 0x5a, 0x7, 0x7, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0x1c, 0xf, 0x2, 0x5b, 
    0x5c, 0x5, 0x1e, 0x10, 0x2, 0x5c, 0x5d, 0x7, 0x8, 0x2, 0x2, 0x5d, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0xe, 0x2, 0x2, 0x5f, 0x60, 0x7, 
    0x18, 0x2, 0x2, 0x60, 0x61, 0x5, 0x26, 0x14, 0x2, 0x61, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0x62, 0x63, 0x7, 0xd, 0x2, 0x2, 0x63, 0x64, 0x7, 0x1a, 0x2, 
    0x2, 0x64, 0x65, 0x5, 0x26, 0x14, 0x2, 0x65, 0x66, 0x7, 0x16, 0x2, 0x2, 
    0x66, 0x67, 0x5, 0x26, 0x14, 0x2, 0x67, 0x68, 0x7, 0x7, 0x2, 0x2, 0x68, 
    0x69, 0x5, 0x26, 0x14, 0x2, 0x69, 0x6a, 0x7, 0x8, 0x2, 0x2, 0x6a, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0xe, 0x2, 0x2, 0x6c, 0x6d, 0x7, 
    0x1a, 0x2, 0x2, 0x6d, 0x6e, 0x5, 0x26, 0x14, 0x2, 0x6e, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x6f, 0x70, 0x7, 0xf, 0x2, 0x2, 0x70, 0x71, 0x7, 0x9, 0x2, 
    0x2, 0x71, 0x72, 0x7, 0x14, 0x2, 0x2, 0x72, 0x74, 0x5, 0x26, 0x14, 0x2, 
    0x73, 0x75, 0x5, 0x18, 0xd, 0x2, 0x74, 0x73, 0x3, 0x2, 0x2, 0x2, 0x74, 
    0x75, 0x3, 0x2, 0x2, 0x2, 0x75, 0x13, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 
    0x7, 0x10, 0x2, 0x2, 0x77, 0x78, 0x7, 0x17, 0x2, 0x2, 0x78, 0x79, 0x5, 
    0x26, 0x14, 0x2, 0x79, 0x7a, 0x7, 0x1b, 0x2, 0x2, 0x7a, 0x7b, 0x7, 0x7, 
    0x2, 0x2, 0x7b, 0x7c, 0x5, 0x24, 0x13, 0x2, 0x7c, 0x7d, 0x7, 0x8, 0x2, 
    0x2, 0x7d, 0x15, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0x11, 0x2, 0x2, 
    0x7f, 0x80, 0x7, 0x14, 0x2, 0x2, 0x80, 0x82, 0x5, 0x26, 0x14, 0x2, 0x81, 
    0x83, 0x5, 0x18, 0xd, 0x2, 0x82, 0x81, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 
    0x3, 0x2, 0x2, 0x2, 0x83, 0x17, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x7, 
    0x15, 0x2, 0x2, 0x85, 0x86, 0x5, 0x22, 0x12, 0x2, 0x86, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x87, 0x88, 0x5, 0x26, 0x14, 0x2, 0x88, 0x8a, 0x5, 0x28, 0x15, 
    0x2, 0x89, 0x8b, 0x7, 0x1d, 0x2, 0x2, 0x8a, 0x89, 0x3, 0x2, 0x2, 0x2, 
    0x8a, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x8c, 
    0x8d, 0x5, 0x1a, 0xe, 0x2, 0x8d, 0x8e, 0x7, 0x4, 0x2, 0x2, 0x8e, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x8f, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x91, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 
    0x2, 0x2, 0x92, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x7, 0x1c, 0x2, 
    0x2, 0x94, 0x95, 0x7, 0x19, 0x2, 0x2, 0x95, 0x96, 0x7, 0x7, 0x2, 0x2, 
    0x96, 0x97, 0x5, 0x26, 0x14, 0x2, 0x97, 0x98, 0x7, 0x8, 0x2, 0x2, 0x98, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x5, 0x26, 0x14, 0x2, 0x9a, 0x9b, 
    0x5, 0x36, 0x1c, 0x2, 0x9b, 0x9c, 0x5, 0x30, 0x19, 0x2, 0x9c, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x5, 0x20, 0x11, 0x2, 0x9e, 0x9f, 0x7, 
    0x21, 0x2, 0x2, 0x9f, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9d, 0x3, 0x2, 
    0x2, 0x2, 0xa1, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa0, 0x3, 0x2, 0x2, 
    0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x5, 0x20, 0x11, 0x2, 0xa6, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 0x5, 0x30, 0x19, 0x2, 0xa8, 0xa9, 
    0x7, 0x4, 0x2, 0x2, 0xa9, 0xab, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa7, 0x3, 
    0x2, 0x2, 0x2, 0xab, 0xae, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaa, 0x3, 0x2, 
    0x2, 0x2, 0xac, 0xad, 0x3, 0x2, 0x2, 0x2, 0xad, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0xae, 0xac, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 0x5, 0x30, 0x19, 0x2, 
    0xb0, 0x25, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x9, 0x2, 0x2, 0x2, 0xb2, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb7, 0x5, 0x2a, 0x16, 0x2, 0xb4, 0xb7, 
    0x5, 0x2c, 0x17, 0x2, 0xb5, 0xb7, 0x5, 0x2e, 0x18, 0x2, 0xb6, 0xb3, 
    0x3, 0x2, 0x2, 0x2, 0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb5, 0x3, 
    0x2, 0x2, 0x2, 0xb7, 0x29, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0x1e, 
    0x2, 0x2, 0xb9, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x20, 0x2, 
    0x2, 0xbb, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x7, 0x1f, 0x2, 0x2, 
    0xbd, 0xbe, 0x7, 0x7, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0xa, 0x2, 0x2, 0xbf, 
    0xc0, 0x7, 0x8, 0x2, 0x2, 0xc0, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc4, 
    0x5, 0x32, 0x1a, 0x2, 0xc2, 0xc4, 0x5, 0x34, 0x1b, 0x2, 0xc3, 0xc1, 
    0x3, 0x2, 0x2, 0x2, 0xc3, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0xc5, 0xc6, 0x9, 0x3, 0x2, 0x2, 0xc6, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0xc7, 0xc8, 0x9, 0x4, 0x2, 0x2, 0xc8, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0xc9, 0xca, 0x9, 0x5, 0x2, 0x2, 0xca, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0xcb, 0xcc, 0x7, 0x12, 0x2, 0x2, 0xcc, 0x39, 0x3, 0x2, 0x2, 0x2, 0xcd, 
    0xce, 0x7, 0x13, 0x2, 0x2, 0xce, 0xcf, 0x5, 0x32, 0x1a, 0x2, 0xcf, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x3f, 0x45, 0x50, 0x54, 0x74, 0x82, 0x8a, 0x91, 
    0xa2, 0xac, 0xb6, 0xc3, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SQLParser::Initializer SQLParser::_init;
