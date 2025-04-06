SELECT name, duration FROM Track
WHERE duration=(SELECT MAX(duration) FROM Track)
LIMIT 1;

SELECT name FROM Track
WHERE duration >= '00:03:30';

SELECT name FROM Сollection
WHERE release BETWEEN 2018 AND 2020;

SELECT performer FROM Performer
WHERE performer NOT LIKE '% %';

SELECT name FROM Track
WHERE name LIKE '%мой%' OR LIKE '%my%';