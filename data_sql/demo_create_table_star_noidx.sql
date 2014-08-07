-- Drop tables if exists

DROP TABLE IF EXISTS fact_sales;
DROP TABLE IF EXISTS dim_store;
DROP TABLE IF EXISTS dim_customer;
DROP TABLE IF EXISTS dim_customer_age;
DROP TABLE IF EXISTS dim_product;
DROP TABLE IF EXISTS campaign;

-- Create Tables

CREATE TABLE dim_store (
  id smallint NOT NULL,
  name text NOT NULL,
  city_no smallint NOT NULL,
  city_name text NOT NULL,
  pref_no smallint NOT NULL,
  pref_name text NOT NULL
);

CREATE TABLE dim_customer (
  id smallint NOT NULL,
  name text NOT NULL,
  birthday date NOT NULL,
  gender "char" NOT NULL,
  city_no smallint NOT NULL,
  city_name text NOT NULL,
  pref_no smallint NOT NULL,
  pref_name text NOT NULL
);

CREATE TABLE dim_customer_age (
  id smallint NOT NULL,
  date date NOT NULL,
  age int NOT NULL
);

CREATE TABLE dim_product (
  id smallint NOT NULL,
  name text NOT NULL,
  price bigint NOT NULL,
  category_s smallint NOT NULL,
  category_s_name text NOT NULL,
  category_l smallint NOT NULL,
  category_l_name text NOT NULL
);

CREATE TABLE campaign (
  id int NOT NULL,
  name text NOT NULL,
  discount int NOT NULL
);

CREATE TABLE fact_sales (
  no bigint NOT NULL,
  time timestamp NOT NULL,
  member smallint,
  store smallint NOT NULL,
  product smallint NOT NULL,
  count int NOT NULL,
  campaign int
);

