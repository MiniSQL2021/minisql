create table person ( 
	pid int primary key,
	name char(32),
	identity int,
	age int,
	height float,
	weight float,
	address char(128)
);

drop table person;
