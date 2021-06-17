#include "Interpreter.hpp"
#include "query/Queries.hpp"
#include "parser/QueryParser.hpp"
#include "parser/SyntaxErrorListener.hpp"
#include "antlr/SQLLexer.h"
#include "antlr/SQLParser.h"

template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> dynamic_unique_ptr_cast(std::unique_ptr<Base, Del> &p);

// Listen to standard input
// Required to use ANTLR to work on the "infinite" stream, and interactively
// See also: https://stackoverflow.com/questions/14864777/using-antlr-for-parsing-data-from-never-ending-stream
void Interpreter::listen() {
    std::cout << "Welcome to the MiniSQL monitor. Commands end with semicolon." << std::endl;
    std::cout << "Copyright (c) 2021, Wang, Hu, Chen, Huang." << std::endl;

    std::string line;
    std::stringstream buffer;
    bool isWaitingForMoreInput = false;
    while (true) {
        try {
            std::cout << (isWaitingForMoreInput ? "      -> " : "minisql> ");
            std::getline(std::cin, line);

            buffer << " " << line;
            parse(buffer);

            // No syntax error occurs, clear buffer
            buffer.str("");
            isWaitingForMoreInput = false;
        } catch (const SyntaxError &error) {
            if (!error.hitEOF) {
                // Didn't hit EOF, that is to say there exists syntax error in the middle
                // Discard buffer, and print error message
                std::cout << error.message() << std::endl;
                buffer.str("");
                isWaitingForMoreInput = false;
            } else {
                // Hit EOF, that is to say additional input is expected
                // Reset buffer's get pointer to the beginning
                buffer.clear();
                buffer.seekg(0);
                isWaitingForMoreInput = true;
            }
        }
    }
}

void Interpreter::processFile(const std::string &path) {
    std::ifstream stream(path);
    if (stream.is_open())
        parse(stream);
    else
        std::cout << "File Error: cannot open file '" << path << "'" << std::endl;
    stream.close();
}

void Interpreter::parse(std::istream &stream) {
    antlr4::ANTLRInputStream input(stream);
    SQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SQLParser parser(&tokens);

    SyntaxErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    SQLParser::QueryContext *tree;
    while (!parser.isMatchedEOF()) {
        tree = parser.query();
        handleQuery(QueryParser::parse(tree));
    }
}

void Interpreter::handleQuery(std::unique_ptr<Query> query) {
    switch (query->type) {
        case QueryType::CreateTable:
            if (createTableQueryHandler)
                createTableQueryHandler(std::move(dynamic_unique_ptr_cast<CreateTableQuery>(query)));
            break;
        case QueryType::DropTable:
            if (dropTableQueryHandler)
                dropTableQueryHandler(std::move(dynamic_unique_ptr_cast<DropTableQuery>(query)));
            break;
        case QueryType::CreateIndex:
            if (createIndexQueryHandler)
                createIndexQueryHandler(std::move(dynamic_unique_ptr_cast<CreateIndexQuery>(query)));
            break;
        case QueryType::DropIndex:
            if (dropIndexQueryHandler)
                dropIndexQueryHandler(std::move(dynamic_unique_ptr_cast<DropIndexQuery>(query)));
            break;
        case QueryType::Select:
            if (selectQueryHandler)
                selectQueryHandler(std::move(dynamic_unique_ptr_cast<SelectQuery>(query)));
            break;
        case QueryType::Insert:
            if (insertQueryHandler)
                insertQueryHandler(std::move(dynamic_unique_ptr_cast<InsertQuery>(query)));
            break;
        case QueryType::Delete:
            if (deleteQueryHandler)
                deleteQueryHandler(std::move(dynamic_unique_ptr_cast<DeleteQuery>(query)));
            break;
        case QueryType::ExecuteFile: {
            auto executeFileQuery = dynamic_unique_ptr_cast<ExecuteFileQuery>(query);
            processFile(executeFileQuery->path);
            break;
        }
        case QueryType::Quit:
            exit(0);
    }
}

// Util function: dynamically downcast unique_ptr of base class to derived class
// See also: https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived
template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> dynamic_unique_ptr_cast(std::unique_ptr<Base, Del> &p) {
    if (auto *result = dynamic_cast<Derived *>(p.get())) {
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}
