drop view if exists fact_dim_all;

create view fact_dim_all as
select
  F.no,
  F.time,
  F.member,
  C.name as member_name,
  C.birthday,
  C.gender,
  C.city_no as c_city_no,
  C.city_name as c_city_name,
  C.pref_no as c_pref_no,
  C.pref_name as c_pref_name,
  A.age as c_age,
  F.store,
  S.name as store_name,
  S.city_no as s_city_no,
  S.city_name as s_city_name,
  S.pref_no as s_pref_no,
  S.pref_name as s_pref_name,
  F.product,
  P.name as product_name,
  P.price,
  P.category_s,
  P.category_s_name,
  P.category_l,
  P.category_l_name,
  F.count,
  F.campaign,
  CP.name as cp_name,
  CP.discount
 FROM
  fact_sales F
   inner join dim_store S on F.store=S.id
   inner join dim_product P on F.product=P.id
   left outer join dim_customer C on F.member=C.id
   left outer join dim_customer_age A on (F.member=A.id AND F.time::date=A.date)
   left outer join campaign CP on F.campaign=CP.id;
