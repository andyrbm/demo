-- Drop tables and views if exists

DROP VIEW IF EXISTS fact_sales;
DROP VIEW IF EXISTS dim_store;
DROP VIEW IF EXISTS dim_customer;
DROP VIEW IF EXISTS dim_customer_age;
DROP VIEW IF EXISTS dim_product;

DROP TABLE IF EXISTS store;
DROP TABLE IF EXISTS product_master;
DROP TABLE IF EXISTS category_small;
DROP TABLE IF EXISTS category_large;
DROP TABLE IF EXISTS member_customer;
DROP TABLE IF EXISTS sales;
DROP TABLE IF EXISTS sales_details;
DROP TABLE IF EXISTS campaign;
DROP TABLE IF EXISTS city;
DROP TABLE IF EXISTS pref;
-- DROP TABLE IF EXISTS weather;


-- Create Tables

CREATE TABLE store (
  id smallint NOT NULL,
  name text NOT NULL,
  city smallint NOT NULL
);

CREATE TABLE product_master (
  id smallint NOT NULL,
  name text NOT NULL,
  price bigint NOT NULL,
  category smallint NOT NULL
);

CREATE TABLE category_small (
  category smallint NOT NULL,
  name text NOT NULL,
  super smallint NOT NULL
);

CREATE TABLE category_large (
  category smallint NOT NULL,
  name text NOT NULL
);

CREATE TABLE member_customer (
  id smallint NOT NULL,
  last_name text NOT NULL,
  first_name text NOT NULL,
  city smallint NOT NULL,
  birthday date NOT NULL,
  gender "char" NOT NULL
);

CREATE TABLE sales (
  no bigint NOT NULL,
  time timestamp NOT NULL,
  member smallint,
  store smallint NOT NULL,
  campaign int
);

CREATE TABLE sales_details (
  no bigint NOT NULL,
  product smallint NOT NULL,
  count int NOT NULL
);

CREATE TABLE campaign (
  id int NOT NULL,
  name text NOT NULL,
  discount int NOT NULL
);

CREATE TABLE city (
  no smallint NOT NULL,
  pref smallint not null,
  name text not null
);

CREATE TABLE pref (
  no smallint NOT NULL,
  name text not null
);


-- Create Views

CREATE VIEW fact_sales AS
 SELECT S.no, S.time, S.member, S.store, D.product, D.count, S.campaign
  FROM sales S INNER JOIN sales_details D ON S.no = D.no;

CREATE VIEW dim_store AS
 SELECT
  store.id,
  store.name,
  city.no AS city_no,
  city.name AS city_name,
  pref.no AS pref_no,
  pref.name AS pref_name
   FROM store INNER JOIN city ON store.city = city.no
    INNER JOIN pref ON city.pref = pref.no;

CREATE VIEW dim_customer AS
 SELECT
  member_customer.id,
  (member_customer.first_name||' '||member_customer.last_name)::text as name,
  birthday,
  gender,
  city.no AS city_no, 
  city.name AS city_name,
  pref.no AS pref_no,
  pref.name AS pref_name
  FROM 
   member_customer INNER JOIN city ON member_customer.city = city.no
    INNER JOIN pref ON city.pref = pref.no;

CREATE VIEW dim_customer_age AS
 SELECT
  DISTINCT ON (id, date)
   member_customer.id,
   sales.time::date as date,
   date_part('year', age(sales.time::date, member_customer.birthday)) as age
 FROM
  sales INNER JOIN member_customer ON sales.member = member_customer.id;

CREATE VIEW dim_product AS
 SELECT
  P.id,
  P.name,
  P.price,
  CS.category AS category_s,
  CS.name AS category_s_name,
  CL.category AS category_l,
  CL.name AS category_l_name
   FROM
    product_master P INNER JOIN category_small CS ON P.category = CS.category
                     INNER JOIN category_large CL ON CS.super = CL.category;
