DROP TABLE IF EXISTS fact_dim_all;

CREATE TABLE fact_dim_all (
  no bigint NOT NULL,
  time timestamp NOT NULL,
  member smallint,
  member_name text,
  birthday date,
  gender "char",
  c_city_no smallint,
  c_city_name text,
  c_pref_no smallint,
  c_pref_name text,
  c_age integer,
  store smallint NOT NULL,
  store_name text NOT NULL,
  s_city_no smallint NOT NULL,
  s_city_name text NOT NULL,
  s_pref_no smallint NOT NULL,
  s_pref_name text NOT NULL,
  product smallint NOT NULL,
  product_name text NOT NULL,
  price bigint NOT NULL,
  category_s smallint NOT NULL,
  category_s_name text NOT NULL,
  category_l smallint NOT NULL,
  category_l_name text NOT NULL,
  count integer NOT NULL,
  campaign integer,
  cp_name text,
  discount integer
);

