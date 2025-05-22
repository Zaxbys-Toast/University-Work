#include "album.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Album::Album() {
    strcpy(UPC, "");
    strcpy(Artist, "");
    strcpy(Title, "");
}

Album::Album(const Album& otherAlbum) {
    strcpy(UPC, otherAlbum.UPC);
    strcpy(Artist, otherAlbum.Artist);
    strcpy(Title, otherAlbum.Title);
}

Album::Album(String upcIn, String artistIn, String titleIn) {
    strcpy(UPC, upcIn);
    strcpy(Artist, artistIn);
    strcpy(Title, titleIn);
}

// Assignment operator, need to overload so we get deep copies instead of shallow copies
Album& Album::operator=(const Album& otherAlbum) {
    if (this != &otherAlbum) {
        strcpy(UPC, otherAlbum.UPC);
        strcpy(Artist, otherAlbum.Artist);
        strcpy(Title, otherAlbum.Title);
    }
    return *this;
}

bool operator<(const Album& a, const Album& b) {
    return (stoi(string(a.UPC)) < stoi(string(b.UPC)));
}

istream& operator>>(istream& stream, Album& C) {
    stream.get(C.UPC, UpTo, '\n');
    stream.ignore();
    stream.get(C.Title, UpTo, '\n');
    stream.ignore();
    stream.get(C.Artist, UpTo, '\n');
    stream.ignore();
    return stream;
}

ostream& operator<<(ostream& stream, Album& C) {
    stream << C.UPC << " | " << C.Artist << " | " << C.Title;
    return stream;
}

bool operator==(const Album& a, const Album& b) {
    return strcmp(a.UPC, b.UPC) == 0;
}

bool operator>(const Album& a, const Album& b) {
    return (stoi(string(a.UPC)) > stoi(string(b.UPC)));
}

string Album::getUPC() {
    return string(UPC);
}

int Album::recordSize() {
    return strlen(UPC) + strlen(Artist) + strlen(Title) + 5;   
}




