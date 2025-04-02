CREATE TABLE IF NOT EXISTS Genre (
	id SERIAL PRIMARY KEY,
	musicGenre VARCHAR(20) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS Performer (
	id SERIAL PRIMARY KEY,
	performer VARCHAR(20) UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS PerformerGenre (
	genre_id INTEGER REFERENCES Genre(id),
	performer_id INTEGER REFERENCES Performer(id),
	CONSTRAINT keyPG PRIMARY KEY (genre_id, performer_id)
);

CREATE TABLE IF NOT EXISTS Albom (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	release date NOT NULL
);

CREATE TABLE IF NOT EXISTS PerformerAlbom (
	albom_id INTEGER REFERENCES Albom(id),
	performer_id INTEGER REFERENCES Performer(id),
	CONSTRAINT keyPA PRIMARY KEY (albom_id, performer_id)
);


CREATE TABLE IF NOT EXISTS Track (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	albom_id INTEGER NOT NULL REFERENCES Albom(id),
	duration TIME NOT NULL
);

CREATE TABLE IF NOT EXISTS TrackPerformer (
	track_id INTEGER REFERENCES Track(id),
	performer_id INTEGER REFERENCES Performer(id),
	CONSTRAINT keyPT PRIMARY KEY (track_id, performer_id)
);

CREATE TABLE IF NOT EXISTS Сollection (
	id SERIAL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	release data NOT NULL
);

CREATE TABLE IF NOT EXISTS TrackСollection (
	track_id INTEGER REFERENCES Track(id),
	collection_id INTEGER REFERENCES Сollection(id),
	CONSTRAINT keyCT PRIMARY KEY (collection_id, track_id)
);
