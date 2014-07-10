DROP VIEW IF EXISTS store_city;
DROP VIEW IF EXISTS customer_city;
DROP TABLE IF EXISTS store;
DROP TABLE IF EXISTS product_master;
DROP TABLE IF EXISTS member_customer;
DROP TABLE IF EXISTS sales;
DROP TABLE IF EXISTS sales_details;
DROP TABLE IF EXISTS city;


CREATE TABLE store (
  id smallint PRIMARY KEY,
  name text NOT NULL,
  city smallint NOT NULL
);

CREATE TABLE product_master (
  ID smallint PRIMARY KEY,
  name text NOT NULL
);

CREATE TABLE member_customer (
  id smallint PRIMARY KEY,
  last_name text NOT NULL,
  first_name text NOT NULL,
  city smallint NOT NULL
);

CREATE TABLE sales (
  no bigint PRIMARY KEY,
  time timestamp NOT NULL,
  member smallint,
  store smallint NOT NULL
);

CREATE TABLE sales_details (
  no bigint NOT NULL,
  product smallint NOT NULL,
  count int NOT NULL,
  PRIMARY KEY(no, product)
);

CREATE TABLE city (
  no smallint PRIMARY KEY,
  name text not null
);

CREATE VIEW store_city AS 
 SELECT store.id, store.name, city.no, city.name AS city_name
  FROM store INNER JOIN city ON store.city = city.no;

CREATE VIEW customer_city AS
 SELECT
  member_customer.id,
  (member_customer.first_name||' '||member_customer.last_name)::text as name,
  city.no, 
  city.name AS city_name
  FROM 
   member_customer INNER JOIN city ON member_customer.city = city.no;
