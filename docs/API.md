# MiniSQL: API

API在本项目中起到统筹所有模块的作用，从Interpreter中得到查询信息，再调用CatalogManager, RecordManager, IndexManager的相应方法，完成相应查询。至于BufferManager模块，它对于API是不可见的，仅仅和上述三个模块进行交互。下面针对各个查询，简要地介绍其中的操作。

## Create Table

1. CatalogManager根据表名检查是否已经存在，若存在则提示错误。
2. 检查输入的表信息是否合法，若不合法则提示错误。
3. RecordManager建立一张空表。
4. CatalogManager记录新表的元数据。

## Drop Table

1. CatalogManager根据表名检查是否不存在，若不存在则提示错误。
2. IndexManager删除该表所有已建立的索引。
3. RecordManager删除该表。
4. CatalogManager删除该表的元数据。

## Create Index

1. CatalogManager根据表名检查该表是否不存在，若不存在则提示错误。
2. CatalogManager根据属性名检查该属性是否不存在，若不存在则提示错误。
3. CatalogManager根据属性名检查该属性是否不唯一，若不唯一则提示错误。
4. CatalogManager根据表名、属性名检查索引是否已经存在，若存在则提示错误。
5. RecordManager获得表内已有的所有记录。
6. IndexManager建立一个新索引，连同表内已有的记录。
7. CatalogManager记录新索引的元数据。

## Drop Index

1. CatalogManager根据表名、属性名检查索引是否不存在，若不存在则提示错误。
2. IndexManager删除该索引。
3. CatalogManager删除该索引的元数据。

## Select

1. CatalogManager根据表名检查该表是否不存在，若不存在则提示错误。
2. CatalogManager根据属性名检查所有属性是否都存在，若有一个不存在则提示错误。
3. CatalogManager根据所有属性名检查输入的每个字面量是否都符合对应属性的类型，若有一个不符合则提示错误。
4. 对输入的属性列表进行合并，其中涉及到合并同一属性的所有区间/点，以简化后续工作。下面的Delete操作也是类似。
5. 对于条件列表中的每一个属性，若存在索引则IndexManager利用索引搜索相应的记录位置，否则RecordManager扫描全部记录寻找记录位置，两者都返回一组记录位置。每次搜索后，对得到的记录位置取交集。
6. RecordManager根据最终的记录位置获取对应的所有记录，输出。

## Delete

1. CatalogManager根据表名检查该表是否不存在，若不存在则提示错误。
2. CatalogManager根据属性名检查所有属性是否都存在，若有一个不存在则提示错误。
3. CatalogManager根据所有属性名检查输入的每个字面量是否都符合对应属性的类型，若有一个不符合则提示错误。
4. 对输入的属性列表进行合并。
5. 对于条件列表中的每一个属性，若存在索引则IndexManager利用索引搜索相应的记录位置，否则RecordManager扫描全部记录寻找记录位置，两者都返回一组记录位置。每次搜索后，对得到的记录位置取交集。
6. RecordManager根据最终的记录位置获取对应的所有记录。
7. 对于该表每个已建立的索引，IndexManager根据最终的记录在索引中删除所有对应的键值。
8. RecordManager根据最终的记录位置删除对应的所有记录。

## Insert

1. CatalogManager根据表名检查该表是否不存在，若不存在则提示错误。
2. CatalogManager根据输入的字面量检查下列条件，若有一个不符合则提示错误。

- 个数是否正确
- 是否都符合对应属性的类型
- 若对应属性是唯一的，是否与表中已有的键值冲突

3. RecordManager插入该记录。
4. 对于该表每个已建立的索引，IndexManager在索引中插入对应的键值。
