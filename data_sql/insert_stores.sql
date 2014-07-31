BEGIN;

INSERT INTO store VALUES (1, 'Arm Station Store', 1);
INSERT INTO store VALUES (2, 'Arm Banshee Street Store', 1);
INSERT INTO store VALUES (3, 'Arm 3rd Corner Store', 1);
INSERT INTO store VALUES (4, 'Bishop Station Store', 2);
INSERT INTO store VALUES (5, 'Cloud 1st Street Store', 3);
INSERT INTO store VALUES (6, 'Denzel Store', 4);
INSERT INTO store VALUES (7, 'Effision Store', 5);
INSERT INTO store VALUES (8, 'Firebird Station Store', 6);
INSERT INTO store VALUES (9, 'George Station Store', 7);
INSERT INTO store VALUES (10, 'George 4th Corner Store', 7);
INSERT INTO store VALUES (11, 'Henry Bridge North Store', 8);
INSERT INTO store VALUES (12, 'Island Center Store', 9);
INSERT INTO store VALUES (13, 'Denzel Shopping Center Store', 4);
INSERT INTO store VALUES (14, 'Henry Store', 8);
INSERT INTO store VALUES (15, 'John Airport Store', 10);

COMMIT;

BEGIN;

INSERT INTO city VALUES (1, 1, 'Arm');
INSERT INTO city VALUES (2, 1, 'Bishop');
INSERT INTO city VALUES (3, 1, 'Cloud');
INSERT INTO city VALUES (4, 1, 'Denzel');
INSERT INTO city VALUES (5, 1, 'Effision');
INSERT INTO city VALUES (6, 1, 'Firebird');
INSERT INTO city VALUES (7, 2, 'George');
INSERT INTO city VALUES (8, 2, 'Henry');
INSERT INTO city VALUES (9, 2, 'Island');
INSERT INTO city VALUES (10, 2, 'John');

COMMIT;

BEGIN;

INSERT INTO pref VALUES (1, 'Cloudia');
INSERT INTO pref VALUES (2, 'Georgia');

COMMIT;
