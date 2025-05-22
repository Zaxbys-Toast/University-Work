#include "btree.h"
#include "album.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<Album> readAlbumsFromFile(const string& filename);
void createFileIfNotExists(const string& filename);


int main(int argc, char *argv[]) {
    if (argc < 3) {
	printf("Usage: %s <output_file> <input_file>\n", argv[0]);
 	return 0;
    }
    // Initialize BTree
    BTree btree;
    const string treeFileName = argv[1];
    btree.writeHeader((char*)treeFileName.c_str());
    
    // Read test data
    const string testFileName = (argv[2]);
    vector<Album> albums = readAlbumsFromFile(testFileName);
    
    // Insert albums into BTree
    cout << "Inserting albums into BTree..." << endl;
    for (const auto& album : albums) {
        btree.insert(album);
    }
    
    cout << "Number of leaves: " << btree.countLeaves() << endl;   
    // Display I/O statistics
    cout << "\nI/O Statistics:" << endl;
    btree.totalio();
    
    btree.printTree();
    return 0;
}

// Function to read albums from test file
vector<Album> readAlbumsFromFile(const string& filename) {
    ifstream infile(filename.c_str());
    vector<Album> albums;
    
    if (!infile) {
        cerr << "Error opening test file: " << filename << endl;
        return albums;
    }
    
    Album album;
    while (infile >> album) {
        albums.push_back(album);
    }
    
    return albums;
}

