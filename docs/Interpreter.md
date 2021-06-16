# MiniSQL: Interpreter

Interpreter的任务是将用户输入的SQL文本转换为API可以理解的信息，是本项目程序排在最前面的一个模块。鉴于SQL本身是一门有语法词汇结构的语言，过程式地直接处理它是很不明智的。或许正则表达式也能够实现这一功能，但实际过程会非常繁琐。比较好的做法是利用SQL本身的语法词汇结构，使用语法词汇解析器框架来实现Interpreter。考虑到历史悠久而且影响力很大的框架bison和flex已经比较古老，虽是C++原生支持的工具，但使用方法不免有些老旧。本模块采用的是原生Java编写的框架ANTLR4，它提供了较为现代的解析器语法，无论在编写规则文件还是编写代码方面都比较简洁而强大，并且为众多流行的编程语言提供了支持。

## 接口

```cpp
class Interpreter {
public:
    void listen();

    void onCreateTableQuery(QueryHandler<CreateTableQuery> handler);

    void onDropTableQuery(QueryHandler<DropTableQuery> handler);

    void onCreateIndexQuery(QueryHandler<CreateIndexQuery> handler);

    void onDropIndexQuery(QueryHandler<DropIndexQuery> handler);

    void onSelectQuery(QueryHandler<SelectQuery> handler);

    void onInsertQuery(QueryHandler<InsertQuery> handler);

    void onDeleteQuery(QueryHandler<DeleteQuery> handler);
};
```

本模块的接口采用了委托模式。值得一提的是，利用`std::function`作为回调函数的容器，克服了这一语言原先传递函数指针的不便。API可以通过若干`onQuery()`方法传入各查询对应的回调函数，然后调用`listen()`方法就可以监听接下来来自标准输入以及文件的所有查询。
`Query`是查询信息的基类，其派生类对应着各种不同的查询。值得一提的是，在生成各个派生类的工厂方法和最终处理基类的`listen()`方法之间，使用了智能指针`std::unique_ptr`、以及移动语义`std::move()`，在避免任何可能的内存泄漏的同时，也避免了传递对象时复制所带来的额外性能损失，而且还使实现变得较为现代。过程涉及到将基类转换为相应的派生类，用到的是`dynamic_cast<Derived*>(Base*)`，但由于涉及到智能指针，过程还要复杂一些，在此不再赘述。

## 解释器

ANTLR4的解释文件分为词汇表和规则表两部分，其中规则表的语法大致如下。

```
createTableStatement:
 CREATE TABLE tableName = identifier (
  LPARN columnElementList primaryKeyConstraint RPARN
 );

columnElement:
 columnName = identifier dataType unique = UNIQUE?;

columnElementList: (elements += columnElement COMMA)+;

primaryKeyConstraint:
 PRIMARY KEY LPARN columnName = identifier RPARN;
```

这种规则的定义方式完全利用了待解释语言本身的结构性，给本模块的实现提供了很大的方便。至于代码方面，ANTLR4提供的类型安全也使编写过程十分现代。

```cpp
std::unique_ptr<CreateTableQuery>
QueryParser::parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx) {
    return std::make_unique<CreateTableQuery>(parseIdentifier(ctx->tableName),
        parseColumnElementList(ctx->columnElementList()),
        parsePrimaryKeyConstraint(ctx->primaryKeyConstraint()));
}
```

像`SQLParser::CreateTableStatementContext`这样的`Context`类提供了一个树状结构，实际上对应着SQL语句的AST (Abstract Syntax Tree)，这样一来就可以方便地遍历所有所需的节点，从而构建出相应的查询信息`Query`之派生类。

## 输入处理

本模块不仅需要处理标准输入的语句，也需要处理`execfile`语句所指定文件中的语句。处理文件是比较容易的，然而处理标准输入就有些实现上的小问题，因为程序并不知道标准输入何时结束，其相当于一个无限的输入流。程序需要分行处理，当前行如果是一条符合条件的语句可以直接执行；否则，要看错误出现在什么位置，如果是出现在语句中间，意味着语句本身不符合条件，用户输入有误；如果是出现在语句末尾，意味着用户可能没有输入完，要等待接下来的输入以求能否解决这个错误。这个过程用到一个辅助的字符串缓冲区，简化过后的代码表示如下。

```cpp
while (true) {
    try {
        std::getline(std::cin, line);
        parse(buffer);
        // No syntax error occurs, clear buffer
        buffer.empty();
        isWaitingForMoreInput = false;
    } catch (const SyntaxError &error) {
        if (!error.hitEOF) {
            // Didn't hit EOF, that is to say
            // there exists syntax error in the middle
            // Discard buffer, and print error message
            std::cout << error.message() << std::endl;
            buffer.empty();
            isWaitingForMoreInput = false;
        } else {
            // Hit EOF, that is to say
            // additional input is expected
            // Reset buffer's get pointer to the beginning
            buffer.seekg(0);
            isWaitingForMoreInput = true;
        }
    }
}
```

## References

- [ANTLR4 Documentation](https://github.com/antlr/antlr4/blob/master/doc/interpreters.md)
- [The ANTLR4 grammar of MySQL Workbench](https://github.com/mysql/mysql-workbench/tree/8.0/library/parsers/grammars)
