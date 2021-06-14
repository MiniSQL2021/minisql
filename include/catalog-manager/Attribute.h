//储存属性信息、并重载属性值的比较算术符\提供属性存入转出的临时变量

#ifndef Attribute_hpp
#define Attribute_hpp

#include <iostream>
#include <string>
#include <math.h>
#include<vector>
#include<cassert>

using namespace std;

enum class AttributeType {
    INT = 0, FLOAT, CHAR, UNDEFINE,
};

class Attribute {
public:
    int dataLength;               //定长数据
    AttributeType type;
    int intData;
    float floatData;
    char charData[255] = "";
    char rowData[255] = "";

    Attribute();

    ~Attribute();

    Attribute(const Attribute &);

    void getRowData();            //从attribute类中导入到rowData并转换为char类型
    void releaseRowData();        //从rowData导出到attribute并转换为原类型数据
    int compare(const Attribute &);  //比较数据大小，用于算术运算符重载
    int getDataLength();        //返回数据长度

    bool operator<(const Attribute &attr);

    bool operator==(const Attribute &attr);

    bool operator!=(const Attribute &attr);

    bool operator>(const Attribute &attr);

    bool operator<=(const Attribute &attr);

    bool operator>=(const Attribute &attr);

    int getOperator(char *);
};

#endif //Attribute_hpp

