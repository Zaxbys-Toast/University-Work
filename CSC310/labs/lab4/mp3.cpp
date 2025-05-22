
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;}
  friend ostream & operator<<(ostream& out, const Song& l);
};

//this operator writes out the song in the correct format
ostream & operator << (ostream& out, const Song & l){
    cout << "\t\t" << l.track << ".  " << l.title << ": " << l.time/60 << ":";
    if ((l.time % 60) < 10) cout << "0";
    cout << l.time % 60 << endl;
    return out;
}

class Album {
  public :
    mutable map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    mutable int time;     // Total time of all songs on album
    mutable int nsongs;   // Total number of songs on album

    bool operator < (Album another) const { return name < another.name;}
    bool operator == (string albumName) const { return name == albumName;}
    friend std::ostream& operator<<(std::ostream& out, const Album& al);
};

ostream & operator<<(ostream& out, const Album& al) {
    out << "\t" << al.name << ": " << al.nsongs << ", " 
        << al.time / 60 << ":";
    if ((al.time % 60) < 10) out << "0";
    out << al.time % 60 << endl;

    for (const auto& songPair : al.songs) {
        out << songPair.second;
    }

    return out;
}

class Artist {
   public :
     string name; // Artist's name
     set<Album> albums; // Artist's Albums
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist

     bool operator < (Artist another) const { return name < another.name;}
     bool operator == (string artistName) const { return name == artistName;}
     friend std::ostream& operator<<(std::ostream& out, const Artist& ar);
};

ostream & operator<<(ostream& out, const Artist& ar) {
    out << ar.name << ": " << ar.nsongs << ", " 
        << ar.time / 60 << ":";
    if ((ar.time % 60) < 10) out << "0";
    out << ar.time % 60 << endl;

    for (const auto& album : ar.albums) {
        out << album;
    }

    return out;

}
void replaceUnderscores(string& str);
int parseTime(const string& timeStr);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "mp3: missing filename 'mp3'" << endl;
        return 1;
    }
    
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "mp3: cannot open file '" << argv[1] << "'" << endl;
        return 1;
    }
    
    map<string, Artist> artists;
    string title, timeStr, artistName, albumName, genre;
    int track;
    
    while (infile >> title >> timeStr >> artistName >> albumName >> genre >> track) {
        replaceUnderscores(title);
        replaceUnderscores(artistName);
        replaceUnderscores(albumName);
        replaceUnderscores(genre);
        
        int time = parseTime(timeStr);
        
        Song song = {title, time, track};
        
        Artist& artist = artists[artistName];
        artist.name = artistName;
        artist.nsongs++;
        artist.time += time;
        
        Album album = { {}, albumName, artistName, genre };
        auto it = artist.albums.find(album);
        if (it == artist.albums.end()) {
            album.songs[track] = song;
            album.nsongs = 1;
            album.time = time;
            artist.albums.insert(album);
        } else {
            const_cast<map<int, Song>&>(it->songs)[track] = song;
            const_cast<int&>(it->nsongs)++;
            const_cast<int&>(it->time) += time;
        }
    }
    
    for (const auto& [_, artist] : artists) {
        cout << artist << endl;
    }
    
    return 0;
}

void replaceUnderscores(string& str) {
    replace(str.begin(), str.end(), '_', ' ');
}

int parseTime(const string& timeStr) {
    int minutes, seconds;
    sscanf(timeStr.c_str(), "%d:%d", &minutes, &seconds);
    return minutes * 60 + seconds;
}
