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
    cout << l.title << " on track #" << l.track << endl;
    return out;
}

class Album {
  public :
    mutable map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    mutable int time;    
    mutable int nsongs;  
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "missing filename" << endl;
        return 1;
    }
    
    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "cannot open file '" << argv[1] << "'" << endl;
        return 1;
    }
    
    set<Song> songs;
    string title, timeStr, artistName, albumName, genre;
    int track;

    while (infile >> title >> timeStr >> artistName >> albumName >> genre >> track) {
        replaceUnderscores(title);
        replaceUnderscores(artistName);
        replaceUnderscores(albumName);
        replaceUnderscores(genre);
        
        int time = parseTime(timeStr);
        
        Song song = {title, time, track};
	songs.insert(song);
	
    }
    
    set<Song>::iterator i;
    for (i = songs.begin(); i != songs.end(); i++)
	cout << *i;

}

void replaceUnderscores(string& str) {
    replace(str.begin(), str.end(), '_', ' ');
}

int parseTime(const string& timeStr) {
    int minutes, seconds;
    sscanf(timeStr.c_str(), "%d:%d", &minutes, &seconds);
    return minutes * 60 + seconds;
}


