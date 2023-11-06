#include <iostream>
#include "Playlist.h"

using namespace std; 

// Default constructor initializes private data member of the object to default values
PlaylistNode::PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}

// Parameterized constructor of PlaylistNode class takes in arguments and intializes the private data members of object
PlaylistNode::PlaylistNode(string idToSet, string songNameToSet, string artistNameToSet, int songLengthToSet, PlaylistNode* nextNodeLoc)
    : uniqueID(idToSet), songName(songNameToSet), artistName(artistNameToSet), songLength(songLengthToSet), nextNodePtr(nextNodeLoc) {}

// InsertAfter function inserts a new node after the current node
void PlaylistNode::InsertAfter(PlaylistNode* nodePtr) {
    // Creates new node and assigns it to the current nodes next node pointer by calling GetNext method
    PlaylistNode* newNextNode = nullptr; 
    newNextNode = this->GetNext();
    // Set the next node of the current node to the new node
    this->SetNext(nodePtr); 
    // Set the next node of the new node to the current next node
    nodePtr->SetNext(newNextNode); 
}

// SetNext function sets the next node pointer to the given node pointer
void PlaylistNode::SetNext(PlaylistNode* nodePtr) {
    nextNodePtr = nodePtr;
}

// Getter functions to return the values of the private data members uniqueID, songName, artistName, songLength, and nextNodePtr
const string& PlaylistNode::GetID() const {
    return uniqueID;
}

const string& PlaylistNode::GetSongName() const {
    return songName;
}

const string& PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

// PrintPlaylistNode function helps to print the contents of a single node in the linked list
void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

// Playlist default constructor that initalizes head and tail pointers to nullptr
Playlist::Playlist() : head(nullptr), tail(nullptr) {}

// Destructor frees memory allocated for the PlaylistNode objects when Playlist object is destroyed
Playlist::~Playlist() {
    PlaylistNode* currNode = head;
    while (currNode != nullptr) {
        PlaylistNode* newNode = currNode;
        currNode = currNode->GetNext();
        delete newNode; 
    }
}

// PrintMenu function to help print the menu
void Playlist::PrintMenu(const string& playlistTitle) const {
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl;
}

// PrintFullPlaylist function to help print the full playlist
void Playlist::PrintFullPlaylist() const {
    if (head == nullptr) {
        cout << "Playlist is empty" << endl << endl;
    } else {
        // Create counter to count songs and new node to traverse through list
        PlaylistNode* currentNode = head;
        int listCount = 1;

        // Iterate through the linked list to print full playlist
        while (currentNode != nullptr) {
            cout << listCount++ << "." << endl;
            currentNode->PrintPlaylistNode(); 
            currentNode = currentNode->GetNext();
            cout << endl;
        }
    }
}

// AddSong function adds a new node to the end of the linked list
void Playlist::AddSong(const string& idToSet, const string& songNameToSet, const string& artistNameToSet, int songLengthToSet) {
    // Create a new node with the given parameters to add to list
    PlaylistNode* newSongNode = new PlaylistNode(idToSet, songNameToSet, artistNameToSet, songLengthToSet);

    // List is empty, add new node as the first node
    if (tail == nullptr) {
        head = newSongNode;
        tail = newSongNode;
    } else {
        // List is not empty, insert the new node after the current tail and update the tail pointer
        tail->InsertAfter(newSongNode);
        tail = newSongNode;
    }
}

// RemoveSong function removes a specific node based on user input within the linked list
void Playlist::RemoveSong(const string& idToSet) {
    // Check if the playlist is empty and return if it is
    if (head == nullptr) {
        return;
    }

    // Declare pointers for the current and previous nodes
    PlaylistNode* currNode = head;
    PlaylistNode* prevNode = nullptr;

    // Traverse the playlist to find the node with the specified ID
    while (currNode != nullptr) {
        // Check if the current node is the one to be removed
        if (currNode->GetID() == idToSet) {
            // Check if the node to be removed is the head node
            if (currNode == head) {
                head = currNode->GetNext();
            } else {
                // If not head node, set the next node of the previous node to the next node of the current node
                prevNode->SetNext(currNode->GetNext());
            }
            cout << "\"" << currNode->GetSongName() << "\" removed." << endl << endl;
            // Delete the current node to free memory then return
            delete currNode;
            return;
        }
        // Move to the next node in the list
        prevNode = currNode;
        currNode = currNode->GetNext();
    }
}

// ChangeSongPosition function modifies the current position of a song to a new position inputed by user 
void Playlist::ChangeSongPosition(int currPos, int newPos) {
    // Checks if current position and new position is same, then returns if so
    if (currPos == newPos) {
        return;
    }

    // Declare pointers to the current and previous nodes, and initialize the counter to count number of nodes
    PlaylistNode* currNode = head;
    PlaylistNode* prevNode = nullptr;
    int nodeCounter = 1;

    // Traverse the playlist to find the node at the current position
    while (currNode != nullptr && nodeCounter < currPos) {
        prevNode = currNode;
        currNode = currNode->GetNext();
        nodeCounter++;
    }

    // Make sure that current position is still valid
    if (currNode == nullptr) {
        return;
    }

    // Remove the node from its current position by changing the previous node and current node pointers
    if (prevNode == nullptr) {
        head = currNode->GetNext();
    } else {
        prevNode->SetNext(currNode->GetNext());
    }

    // Update the tail pointer of the linked list if the current node is the last node
    if (currNode == tail) {
        tail = prevNode;
    }

    // Declare pointers to the new and previous new nodes, and initialize the counter to count number of nodes
    PlaylistNode* newNode = head;
    PlaylistNode* prevNewNode = nullptr;
    nodeCounter = 1;

    // Handle the case where the new position is less than 1
    if (newPos <= 1) {
        // Set the new node as the head, and update the next node accordingly
        currNode->SetNext(head);
        head = currNode;
    } else {
        // Traverse the playlist again to find the node at the new position
        while (newNode != nullptr && nodeCounter < newPos) {
            prevNewNode = newNode;
            newNode = newNode->GetNext();
            nodeCounter++;
        }

        // Set the current node as the head if previous node is null
        if (prevNewNode == nullptr) {
            head = currNode;
        } else {
            // Otherwise, set the next node of the previous node to the current node
            prevNewNode->SetNext(currNode);
        }

        // Set the next node of the current node to the new node
        currNode->SetNext(newNode);

        // If the new node moved to the tail of the playlist, tail pointer is updated
        if (newNode == nullptr) {
            tail = currNode;
        }
    }

    cout << "\"" << currNode->GetSongName() << "\" moved to position " << newPos << endl << endl;
}

// OutputSpecArtistSong function outputs the playlist songs that match the given artist name
void Playlist::OutputSpecArtistSong(const string& artistNameToSet) const {
    // Playlist is empty, return 
    if (head == nullptr) {
        return;
    } else {
        // Declare pointer to current node and initialize the counter to 1 to count where the songs are
        PlaylistNode* current = head;
        int artistCount = 1;

        // Traverse the playlist
        while (current != nullptr) {
            // If the current song matches the given artist name, output the song info and artist count
            if (current->GetArtistName() == artistNameToSet) {
                cout << artistCount << "." << endl;
                current->PrintPlaylistNode();
                cout << endl;
            }
            artistCount++;
            current = current->GetNext();
        }
    }
}

// OutputTotalTime function calculates the total length of all songs in the playlist
int Playlist::OutputTotalTime() const {
    int totalTime = 0;  
    PlaylistNode* current = head;

    // Loop through the playlist until the end is reached
    while (current != nullptr) {
        // Add the length of the current song to the totalTime variable and move pointer to next node
        totalTime = totalTime + current->GetSongLength();
        current = current->GetNext();
    }

    return totalTime;
}