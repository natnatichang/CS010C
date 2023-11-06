#pragma once //same as header files ifdef 

#include <string> //need string because u need string 
// check this before you send
// also note to self to add some comments or smth 
// delete later: should i be putting comments to explain what each thing does? 
//where to put comments? above or below ?? do i even need comments here lol
//comment spacing, indentation
//variable names, don't use name like temop, xyz, val 1 val2 comments 
//demo, optional
using namespace std;

class PlaylistNode {
public:
    //default constructor I dont really like this but nmaybe ill change it to tihs later 
    // PlaylistNode()
    //     :   uniqueID("none"), 
    //         songName("none"), 
    //         artistName("none"), 
    //         songLength(0), 
    //         nextNodePtr(nullptr)
    // { 
    // }


    PlaylistNode();
    //parameterized constructor
    PlaylistNode(string idToSet, string songNameToSet, string artistNameToSet, int songLengthToSet, PlaylistNode* nextNodeLoc = 0);

    //public member functions
    void InsertAfter(PlaylistNode* nodePtr);
    void SetNext(PlaylistNode* nodePtr);
    const string& GetID() const; // teacher said to make it const but the ta said to not make ti const D: 
    const string& GetSongName() const;
    const string& GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext(); // no constant because i promise to not release any data from itself that will change
    void PrintPlaylistNode() const;

private: 
    //private data members
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

class EditPlaylist {
public:
    EditPlaylist();
    ~EditPlaylist();
    void PrintMenu(string playlistTitle) const; // playlist print should be const 
    void PrintFullPlaylist() const;
    void AddSong(string idToSet, string songNameToSet, string artistNameToSet, int songLengthToSet);
    void RemoveSong(string idToSet); // are there specifics to this? is string typically pass by reference
    void ChangeSongPosition(int oldPos, int newPost);
    void OutputSpecArtistSong(string artistNameToSet);
    int OutputTotalTime(); // might be int
private:
    PlaylistNode* head;
    PlaylistNode* tail; 
};

//string pass by reference??? 
