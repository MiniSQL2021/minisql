
// Generated from /Users/cobalt/Projects/courses/database-system/minisql/interpreter/minisql.g4 by ANTLR 4.8


#include "minisqlLexer.h"


using namespace antlr4;


minisqlLexer::minisqlLexer(CharStream *input) : Lexer(input) {
  _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

minisqlLexer::~minisqlLexer() {
  delete _interpreter;
}

std::string minisqlLexer::getGrammarFileName() const {
  return "minisql.g4";
}

const std::vector<std::string>& minisqlLexer::getRuleNames() const {
  return _ruleNames;
}

const std::vector<std::string>& minisqlLexer::getChannelNames() const {
  return _channelNames;
}

const std::vector<std::string>& minisqlLexer::getModeNames() const {
  return _modeNames;
}

const std::vector<std::string>& minisqlLexer::getTokenNames() const {
  return _tokenNames;
}

dfa::Vocabulary& minisqlLexer::getVocabulary() const {
  return _vocabulary;
}

const std::vector<uint16_t> minisqlLexer::getSerializedATN() const {
  return _serializedATN;
}

const atn::ATN& minisqlLexer::getATN() const {
  return _atn;
}




// Static vars and initialization.
std::vector<dfa::DFA> minisqlLexer::_decisionToDFA;
atn::PredictionContextCache minisqlLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN minisqlLexer::_atn;
std::vector<uint16_t> minisqlLexer::_serializedATN;

std::vector<std::string> minisqlLexer::_ruleNames = {
  u8"SELECT"
};

std::vector<std::string> minisqlLexer::_channelNames = {
  "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
};

std::vector<std::string> minisqlLexer::_modeNames = {
  u8"DEFAULT_MODE"
};

std::vector<std::string> minisqlLexer::_literalNames = {
  "", u8"'select'"
};

std::vector<std::string> minisqlLexer::_symbolicNames = {
  "", u8"SELECT"
};

dfa::Vocabulary minisqlLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> minisqlLexer::_tokenNames;

minisqlLexer::Initializer::Initializer() {
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

minisqlLexer::Initializer minisqlLexer::_init;
