SELECT musicGenre, COUNT(performer) FROM Genre
JOIN PerformerGenre PG ON Genre.id = PG.genre_id
JOIN Performer ON PG.performer_id = Performer.id
GROUP BY musicGenre;

SELECT COUNT(*) FROM Track
JOIN Albom ON Track.albom_id = Albom.id
WHERE Albom.release BETWEEN 2019 AND 2020;

SELECT Albom.name, AVG(duration) FROM Track
JOIN Albom ON Track.albom_id = Albom.id
GROUP BY Albom.name;

SELECT performer FROM Performer P
JOIN PerformerAlbom PA ON P.id = PA.performer_id
JOIN Albom ON PA.albom_id = Albom.id
WHERE release != 2020;

SELECT name FROM Сollection Col
JOIN TrackСollection TC ON Col.id = TC.collection_id
JOIN Track ON TC.track_id = Track.id
JOIN Albom ON Track.albom_id = Albom.id
JOIN PerformerAlbom PA ON PA.albom_id = Albom.id
JOIN Performer P ON P.id = PA.performer_id
WHERE P.performer = 'A-ha';