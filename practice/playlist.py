import cs50
import csv

def main():
    min_tempo = cs50.get_int("Minimum tempo: ")
    max_tempo = cs50.get_int("Maximum tempo: ")

    playlist = []
    # TODO: Read songs from 2018_top100.csv into playlist
    with open("2018_top100.csv") as songs_file:
        file_reader = csv.DictReader(songs_file)
        for row in file_reader:
            if(float(row["tempo"]) >= min_tempo and float(row["tempo"]) <= max_tempo):
                playlist.append(row)

    # TODO: Print song titles from playlist
    for row in playlist:
        print(row["name"])
main()

