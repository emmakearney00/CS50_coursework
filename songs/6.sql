--names of songs that are by Post Malone

SELECT name FROM songs
WHERE artist_id IN (SELECT id FROM artists WHERE name = "Post Malone")

--OR:

--SELECT songs.name FROM songs
--JOIN artists ON artists.id = songs.artist_id
--WHERE artists.name = "Post Malone";