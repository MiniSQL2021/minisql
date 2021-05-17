
// Generated from /Users/cobalt/Projects/courses/database-system/minisql/src/SQL.g4 by ANTLR 4.8


#include "SQLLexer.h"


using namespace antlr4;


SQLLexer::SQLLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SQLLexer::~SQLLexer() {
  delete _interpreter;
}

std::string SQLLexer::getGrammarFileName() const {
  return "SQL.g4";
}

const std::vector<std::string>& SQLLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& SQLLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& SQLLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& SQLLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& SQLLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> SQLLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& SQLLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> SQLLexer::_decisionToDFA;
atn::PredictionContextCache SQLLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SQLLexer::_atn;
std::vector<uint16_t> SQLLexer::_serializedATN;

std::vector<std::string> SQLLexer::_ruleNames = {
  u8"SELECT"
};

std::vector<std::string> SQLLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> SQLLexer::_modeNames = {
  u8"DEFAULT_MODE"
};

std::vector<std::string> SQLLexer::_literalNames = {
  "", u8"'select'"
};

std::vector<std::string> SQLLexer::_symbolicNames = {
  "", u8"SELECT"
};

dfa::Vocabulary SQLLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SQLLexer::_tokenNames;

SQLLexer::Initializer::Initializer() {
  // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
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
    0x2, 0x3, 0xc, 0x8, 0x1, 0x4, 0x2, 0x9, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x2, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0xb, 0x2, 0x3, 0x3, 0x2, 0x2, 0x2, 0x3, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x5, 0x6, 0x7, 0x75, 0x2, 0x2, 0x6, 0x7, 0x7, 0x67, 0x2, 
    0x2, 0x7, 0x8, 0x7, 0x6e, 0x2, 0x2, 0x8, 0x9, 0x7, 0x67, 0x2, 0x2, 0x9, 
    0xa, 0x7, 0x65, 0x2, 0x2, 0xa, 0xb, 0x7, 0x76, 0x2, 0x2, 0xb, 0x4, 0x3, 
    0x2, 0x2, 0x2, 0x3, 0x2, 0x2, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SQLLexer::Initializer SQLLexer::_init;
