#include "album.h"
#include <cstdlib>

int Album::recordSize()
{
	return (strlen(UPC)+strlen(Artist)+strlen(Title)+5);
}

string Album::getUPC()
{
	return UPC;
}

Album::Album (String myUPC, String myArtist, String myTitle)
{
       strcpy (UPC, myUPC);  strcpy (Artist, myArtist);
       strcpy (Title, myTitle); 
}

Album::Album ()
{
        strcpy (UPC, "\0");
        strcpy (Artist, "\0");
        strcpy (Title, "\0");
}

Album & Album::operator = (const Album& otherAlbum)
{
       strcpy (UPC, otherAlbum.UPC);
       strcpy (Artist, otherAlbum.Artist);
       strcpy (Title, otherAlbum.Title);
       return *this;
}
       
Album::Album (const Album& otherAlbum)
{
       strcpy (UPC, otherAlbum.UPC);
       strcpy (Artist, otherAlbum.Artist);
       strcpy (Title, otherAlbum.Title);
}
       
bool operator < (const Album& a, const Album& b)
{
	return (strcmp(a.UPC, b.UPC) < 0);
}

istream & operator >> (istream & stream, Album & C)
{
       stream.getline(C.UPC, UpTo, '\n');  
       if (strlen(C.UPC) == 0)  return stream;
       stream.getline(C.Artist, UpTo, '\n'); 
       stream.getline(C.Title, UpTo, '\n');  
       return stream;
}
       
ostream & operator << (ostream & stream, Album & C)
{
       stream << C.UPC << "|";
       stream << C.Artist << "|";
       stream << C.Title << "|";
       return stream;
}
