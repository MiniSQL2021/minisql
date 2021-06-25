create table person ( 
	height float unique,
	pid int,
	name char(32),
	identity char(128) unique,
	age int unique,
	primary key(pid)
);

insert into person values (171.1, 1, "Person1", "000001", 81);
insert into person values (162.1, 2, "Person2", "000002", 19);
insert into person values (163.3, 3, "Person3", "000003", 20);
insert into person values (174.9, 4, "Person4", "000004", 21);
insert into person values (175.0, 5, "Person5", "000005", 22);
insert into person values (176.1, 6, "Person6", "000006", 23);
insert into person values (177.2, 7, "Person7", "000007", 24);
insert into person values (178.1, 8, "Person8", "000008", 25);
insert into person values (179.1, 9, "Person9", "000009", 26);
insert into person values (180.1, 10, "Person10", "000010", 27);
insert into person values (181.1, 11, "Person11", "000011", 28);
insert into person values (182.1, 12, "Person12", "000012", 29);
insert into person values (183.1, 13, "Person13", "000013", 30);
insert into person values (184.3, 14, "Person14", "000014", 31);
insert into person values (185.1, 15, "Person15", "000015", 32);
insert into person values (186.4, 16, "Person16", "000016", 33);
insert into person values (187.1, 17, "Person17", "000017", 34);
insert into person values (188.1, 18, "Person18", "000018", 35);
insert into person values (189.1, 19, "Person19", "000019", 36);
insert into person values (190.1, 20, "Person20", "000020", 37);

create index idx_height on person(height);
create index idx_identity on person(identity);
create index idx_age on person(age);

select * from person where age > 24;
select * from person where name = "Person15";
select * from person where height <= 176.3;

drop index idx_height;
drop index idx_identity;
drop index idx_age;

drop table person;
