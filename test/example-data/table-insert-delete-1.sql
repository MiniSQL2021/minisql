create table person ( 
	height float,
	pid int,
	name char(32),
	identity char(128) unique,
	age int,
	primary key(pid)
);

insert into person values (175.1, 1, "Person1", "000001", 18);
insert into person values (165.1, 2, "Person2", "000002", 19);
insert into person values (165.3, 3, "Person3", "000003", 20);
insert into person values (175.9, 4, "Person4", "000004", 21);
insert into person values (175.0, 5, "Person5", "000005", 22);
insert into person values (172.1, 6, "Person6", "000006", 23);
insert into person values (175.2, 7, "Person7", "000007", 24);
insert into person values (175.1, 8, "Person8", "000008", 25);
insert into person values (174.1, 9, "Person9", "000009", 26);
insert into person values (175.1, 10, "Person10", "000010", 27);
insert into person values (172.1, 11, "Person11", "000011", 28);
insert into person values (175.1, 12, "Person12", "000012", 29);
insert into person values (174.1, 13, "Person13", "000013", 30);
insert into person values (175.1, 14, "Person14", "000014", 31);
insert into person values (175.1, 15, "Person15", "000015", 32);
insert into person values (173.1, 16, "Person16", "000016", 33);
insert into person values (175.1, 17, "Person17", "000017", 34);
insert into person values (175.1, 18, "Person18", "000018", 35);
insert into person values (179.1, 19, "Person19", "000019", 36);
insert into person values (171.1, 20, "Person20", "000020", 37);

delete from person where pid >= 15;
delete from person where height < 173.5;
delete from person where age <= 20 and height < 170 and identity = "000016";
delete from person where age <= 20 and height >= 175;
delete from person where age <= 20 and height < 170 and name = "Person16";

select * from person;

drop table persion;
