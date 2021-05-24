#include "Interpreter.hpp"
#include "Queries.hpp"
#include "QueryParser.hpp"
#include "SQLLexer.h"
#include "SQLParser.h"
#include "SyntaxErrorListener.hpp"

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

std::unique_ptr<Query> Interpreter::parse(std::istream &stream) {
    antlr4::ANTLRInputStream input(stream);
    SQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SQLParser parser(&tokens);

    SyntaxErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    SQLParser::QueryContext *tree = parser.query();
    return QueryParser::parse(tree);
}

std::unique_ptr<Query> Interpreter::parse(const std::string &string) {
    std::stringstream stream(string);
    return parse(stream);
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
        default:
            break;
    }
}

void Interpreter::listen() {
    std::string line, buffer;
    while (std::getline(std::cin, line))
        try {
            buffer += ' ';
            buffer.append(line);
            buffer += ' ';
            auto query = parse(buffer);

            if (dynamic_cast<QuitQuery *>(query.get())) break;
            else if (auto executeFileQuery = dynamic_cast<ExecuteFileQuery *>(query.get()))
                processFile(executeFileQuery->path);
            else handleQuery(std::move(query));

            buffer.clear();
        } catch (const SyntaxError &error) {
            if (!error.hitEOF) {
                std::cout << error.message() << std::endl;
                buffer.clear();
            }
        }
}

void Interpreter::processFile(const std::string &path) {

}
