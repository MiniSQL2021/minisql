create table person
(
    pid      int,
    name     char(32),
    identity int,
    age      int,
    height   float,
    weight   float,
    address  char(128),
    primary key (pid)
);

drop table person;
