--number of movies with an IMDb rating of 10.0
SELECT count(id) FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10.0);

