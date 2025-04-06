INSERT INTO Genre(musicGenre)
VALUES ('Поп');

INSERT INTO Genre(musicGenre)
VALUES ('Рэп');

INSERT INTO Genre(musicGenre)
VALUES ('Рок');

INSERT INTO Genre(musicGenre)
VALUES ('Электронная');

INSERT INTO Performer(performer)
VALUES ('Madonna');

INSERT INTO Performer(performer)
VALUES ('A-ha');

INSERT INTO Performer(performer)
VALUES ('50 Cent');

INSERT INTO Performer(performer)
VALUES ('Pitbull');

INSERT INTO Performer(performer)
VALUES ('Eminem');

INSERT INTO Performer(performer)
VALUES ('Delain');

INSERT INTO Performer(performer)
VALUES ('Martin Garrix');

INSERT INTO Performer(performer)
VALUES ('Don Diablo');

INSERT INTO Performer(performer)
VALUES ('Alan Walker');

INSERT INTO Performer(performer)
VALUES ('Ne-Yo');

INSERT INTO PerformerGenre
VALUES (1,1);

INSERT INTO PerformerGenre
VALUES (1,2);

INSERT INTO PerformerGenre
VALUES (2,3);

INSERT INTO PerformerGenre
VALUES (1,4);

INSERT INTO PerformerGenre
VALUES (2,4);

INSERT INTO PerformerGenre
VALUES (2,5);

INSERT INTO PerformerGenre
VALUES (3,6);

INSERT INTO PerformerGenre
VALUES (4,7);

INSERT INTO PerformerGenre
VALUES (4,8);

INSERT INTO PerformerGenre
VALUES (4,9);

INSERT INTO PerformerGenre
VALUES (1,10);

INSERT INTO PerformerGenre
VALUES (2,10);

INSERT INTO Albom(name, release)
VALUES ('Like a Virgin', 1984);

INSERT INTO Albom(name, release)
VALUES ('Ray of Light', 1998);

INSERT INTO Albom(name, release)
VALUES ('Confessions on a Dance Floor', 2005);

INSERT INTO Albom(name, release)
VALUES ('Hunting High and Low', 1985);

INSERT INTO Albom(name, release)
VALUES ('East of the Sun, West of the Moon', 1990);

INSERT INTO Albom(name, release)
VALUES ('Get Rich or Die Tryin’', 2003);

INSERT INTO Albom(name, release)
VALUES ('Planet Pit', 2014);

INSERT INTO Albom(name, release)
VALUES ('April Rain', 2009);

INSERT INTO Albom(name, release)
VALUES ('The Human Contradiction', 2014);

INSERT INTO Albom(name, release)
VALUES ('Gold Skies', 2014);

INSERT INTO Albom(name, release)
VALUES ('Future', 2018);

INSERT INTO Albom(name, release)
VALUES ('Different World', 2018);

INSERT INTO PerformerAlbom
VALUES (1,1);

INSERT INTO PerformerAlbom
VALUES (2,1);

INSERT INTO PerformerAlbom
VALUES (3,1);

INSERT INTO PerformerAlbom
VALUES (4,2);

INSERT INTO PerformerAlbom
VALUES (5,2);

INSERT INTO PerformerAlbom
VALUES (6,3);

INSERT INTO PerformerAlbom
VALUES (7,4);

INSERT INTO PerformerAlbom
VALUES (8,6);

INSERT INTO PerformerAlbom
VALUES (9,6);

INSERT INTO PerformerAlbom
VALUES (10,7);

INSERT INTO PerformerAlbom
VALUES (11,8);

INSERT INTO PerformerAlbom
VALUES (12,9);

INSERT INTO PerformerAlbom
VALUES (7,10);

INSERT INTO PerformerAlbom
VALUES (6,5);


INSERT INTO Track(name, albom_id, duration)
VALUES ('Like a Virgin', 1, '00:03:39');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Frozen', 2, '00:06:12');

INSERT INTO Track(name, albom_id, duration)
VALUES ('The Power of Good-Bye', 2, '00:04:10');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Sorry', 3, '00:04:41');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Get Together', 3, '00:05:29');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Take on me', 4, '00:03:48');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Crying in the Rain', 5, '00:04:24');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Don’t Push Me', 6, '00:04:08');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Give Me Everything', 7, '00:04:12');

INSERT INTO Track(name, albom_id, duration)
VALUES ('International Love', 7, '00:03:47');

INSERT INTO Track(name, albom_id, duration)
VALUES ('April Rain', 8, '00:04:37');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Virtue And Vice', 8, '00:03:56');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Stardust', 9, '00:03:57');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Animals', 10, '00:05:04');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Save A Little Love', 11, '00:03:23');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Everybody’s Somebody', 11, '00:03:18');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Alone', 12, '00:02:40');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Faded', 12, '00:03:32');

INSERT INTO Track(name, albom_id, duration)
VALUES ('Sing Me to Sleep', 12, '00:03:07');


INSERT INTO Сollection(name, release)
VALUES ('The Immaculate Collection', 1990);

INSERT INTO Сollection(name, release)
VALUES ('Celebration', 2009);

INSERT INTO Сollection(name, release)
VALUES ('Headlines and Deadlines', 1991);

INSERT INTO Сollection(name, release)
VALUES ('The Definitive Singles Collection', 2005);


INSERT INTO TrackСollection
VALUES (1, 1);

INSERT INTO TrackСollection
VALUES (1, 2);

INSERT INTO TrackСollection
VALUES (2, 2);

INSERT INTO TrackСollection
VALUES (4, 2);

INSERT INTO TrackСollection
VALUES (6, 3);

INSERT INTO TrackСollection
VALUES (6, 4);

INSERT INTO TrackСollection
VALUES (7, 3);