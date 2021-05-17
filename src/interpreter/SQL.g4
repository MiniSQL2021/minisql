grammar SQL;

DOT: '.';
COMMA: ',';
SEMICOLON: ';';
UNDERSCORE: '_';
LPARN: '(';
RPARN: ')';
STAR: '*';

fragment DIGIT: [0-9];
fragment DIGITS: DIGIT+;
INT_NUMBER: [+\-]? DIGITS;
DECIMAL_NUMBER: [+\-]? DIGITS? DOT DIGITS;
FLOAT_NUMBER: (INT_NUMBER | DECIMAL_NUMBER) [eE] (INT_NUMBER);

// Verb
CREATE: 'create';
DROP: 'drop';
SELECT: 'select';
INSERT: 'insert';
DELETE: 'delete';
QUIT: 'quit';
EXEC_FILE: 'execfile';

// Preposition & Adverb
FROM: 'from';
WHERE: 'where';
ON: 'on';
INTO: 'into';

// Noun & Adjective
TABLE: 'table';
KEY: 'key';
INDEX: 'index';
VALUES: 'values';
PRIMARY: 'primary';
UNIQUE: 'unique';

// Type
INT: 'int';
CHAR: 'char';
FLOAT: 'float';

// Operator
AND: 'and';
EQUAL: '=';
NOT_EQUAL: '<>';
LESS_THAN: '<';
GREATER_THAN: '>';
LESS_OR_EQUAL_THAN: '<=';
GREATER_OR_EQUAL_THAN: '>=';

// White space handling: ignore whitespaces
WHITESPACE: [ \t\f\r\n] -> channel(HIDDEN);

fragment LETTER: [a-zA-Z_\u0080-\uffff];

// Identifiers should start with a letter, but are allowed to contain digit and underscore after it.
// Unicode characters are also supported.
IDENTIFIER: LETTER (LETTER | DIGIT)*;

// String
BACKTICK_QUOTED_ID: '`' (. | '\\`')*? '`';
DOUBLE_QUOTED_STRING: '"' (. | '\\"')*? '"';
SINGLE_QUOTED_STRING: '\'' (. | '\\\'')*? '\'';
STRING: DOUBLE_QUOTED_STRING | SINGLE_QUOTED_STRING;

/* Rules */

// Top structure
query: EOF | (statement | commands) (SEMICOLON EOF? | EOF);

statement:
	createTableStatement
	| dropTableStatement
	| createIndexStatement
	| dropIndexStatement;

commands: quitCommand | executeFileCommand;

// Statements
createTableStatement:
	CREATE TABLE tableName = identifier (
		LPARN columnElementList primaryKeyConstraint RPARN
	);

dropTableStatement: DROP TABLE tableName = identifier;

createIndexStatement:
	CREATE INDEX indexName = identifier ON tableName = identifier (
		LPARN columnName = identifier RPARN
	);

dropIndexStatement: DROP INDEX indexName = identifier;

selectStatement:
	SELECT STAR FROM tableName = identifier whereClause?;

insertStatement:
	INSERT INTO tableName = identifier VALUES (
		LPARN attributeList RPARN
	);

deleteStatement:
	DELETE FROM tableName = identifier whereClause?;

// Clauses
whereClause: WHERE conditionList;

// Secondary expression
columnElement:
	columnName = identifier dataType unique = UNIQUE?;
columnElementList: (elements += columnElement COMMA)+;

primaryKeyConstraint:
	PRIMARY KEY LPARN columnName = identifier RPARN;

condition:
	columnName = identifier binaryOperator value = literal;
conditionList: (conditions += condition AND)* (
		conditions += condition
	);

attributeList: (attributes += literal COMMA)* attributes += literal;

// Small parts
identifier: IDENTIFIER | BACKTICK_QUOTED_ID;

dataType: intType | floatType | charType;
intType: INT;
floatType: FLOAT;
charType: CHAR LPARN length = INT_NUMBER RPARN;

literal: string | number;
string: SINGLE_QUOTED_STRING | DOUBLE_QUOTED_STRING;
number: INT_NUMBER | DECIMAL_NUMBER | FLOAT_NUMBER;

binaryOperator:
	EQUAL
	| NOT_EQUAL
	| LESS_THAN
	| GREATER_THAN
	| LESS_OR_EQUAL_THAN
	| GREATER_OR_EQUAL_THAN;

filePath: .*?;

// System commands
quitCommand: QUIT;

executeFileCommand: EXEC_FILE filePath;