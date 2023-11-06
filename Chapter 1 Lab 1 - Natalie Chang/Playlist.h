#pragma once 
#include <string> 

using namespace std;

// PlaylistNode class that represents a node in the playlist.
class PlaylistNode {
public:
    // Default constructor for PlaylistNode
    PlaylistNode();
    // Parameterized constructor for PlaylistNode
    PlaylistNode(string idToSet, string songNameToSet, string artistNameToSet, int songLengthToSet, PlaylistNode* nextNodeLoc = 0);
    // Public member functions for PlaylistNode
    void InsertAfter(PlaylistNode* nodePtr);
    void SetNext(PlaylistNode* nodePtr);
    const string& GetID() const; 
    const string& GetSongName() const;
    const string& GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext(); 
    void PrintPlaylistNode() const;
private: 
    // Private data members to create PlaylistNode object
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

// Playlist class that represents a playlist and its operations.
class Playlist {
public:
    // Default constructor for Playlist
    Playlist();
    // Destructor for Playlist
    ~Playlist();
    // Public member functions for Playlist
    void PrintMenu(const string& playlistTitle) const;
    void PrintFullPlaylist() const;
    void AddSong(const string& idToSet, const string& songNameToSet, const string& artistNameToSet, int songLengthToSet);
    void RemoveSong(const string& idToSet);
    void ChangeSongPosition(int oldPos, int newPost);
    void OutputSpecArtistSong(const string& artistNameToSet) const;
    int OutputTotalTime() const; 
private:
    // Private data members to track first and last node in playlist
    PlaylistNode* head;
    PlaylistNode* tail; 
};

