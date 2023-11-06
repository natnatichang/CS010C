#include <iostream>
using namespace std; 

#include "Playlist.h"

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

// EditPlaylist default constructor that initalizes head and tail pointers to nullptr
EditPlaylist::EditPlaylist() : head(nullptr), tail(nullptr) {}

// Destructor frees memory allocated for the PlaylistNode objects when EditPlaylist object is destroyed
EditPlaylist::~EditPlaylist() {
    PlaylistNode* currNode = head;
    while (currNode != nullptr) {
        PlaylistNode* newNode = currNode;
        currNode = currNode->GetNext();
        delete newNode; 
    }
}

// PrintMenu function to help print the menu
void EditPlaylist::PrintMenu(string playlistTitle) const {
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
void EditPlaylist::PrintFullPlaylist() const {
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
void EditPlaylist::AddSong(string idToSet, string songNameToSet, string artistNameToSet, int songLengthToSet) {
    // Create a new node with the given parameters to add to list
    PlaylistNode* newSongNode = new PlaylistNode(idToSet, songNameToSet, artistNameToSet, songLengthToSet);

    if (tail == nullptr) {
        // List is empty, add new node as the first node
        head = newSongNode;
        tail = newSongNode;
    } else {
        // List is not empty, add new node after the last node
        tail->InsertAfter(newSongNode);
        tail = newSongNode;
    }
}

// RemoveSong function removes a specific node within the linked list
void EditPlaylist::RemoveSong(string idToSet) {
    //make new nodes to traverse through the linked list 

    //note to self to check other stuff :()
    if (head == nullptr) {
        return;
    }

    //start at the beginning of the list
    PlaylistNode* currNode = head;

    //track prev node
    PlaylistNode* prevNode = nullptr;

    //go through list unitl end is reach or u find the song
    while (currNode != nullptr) {

        //check if curr node as the id
        if (currNode->GetID() == idToSet) {

            //curr is the head, then update the head to point to the next node
            if (currNode == head) {
                head = currNode->GetNext();
            } else {
                //if curr node is not head, update previous nodes "next" pointer to skip over the current node
                //curr node is being removed, prev node point to node thats after the current
                prevNode->SetNext(currNode->GetNext());

                /* playlistnode* nextnode = currNode ->getnext()
                delete currnode
                prevnode->setnext(nextnode);
                */
            }
            cout << "\"" << currNode->GetSongName() << "\" removed." << endl << endl;
            //delete current node
            delete currNode;
            //exist after removing song
            return;

        }
        //move onto the next node in the list
        prevNode = currNode;
        currNode = currNode->GetNext();
    }
}

// ChangeSongPosition function
void EditPlaylist::ChangeSongPosition(int currPos, int newPos) {

    if (currPos == newPos) {
        return;
    }

    // Find the node to be moved
    PlaylistNode* currNode = head;
    PlaylistNode* prevNode = nullptr;
    int nodeCounter = 1;

    while (currNode != nullptr && nodeCounter < currPos) {
        prevNode = currNode;
        currNode = currNode->GetNext();
        nodeCounter++;
    }

    if (currNode == nullptr) {
        return;
    }

    // Remove the node from its current position
    if (prevNode == nullptr) {
        head = currNode->GetNext();
    } else {
        prevNode->SetNext(currNode->GetNext());
    }

    if (currNode == tail) {
        tail = prevNode;
    }

    // Find the node to insert before
    PlaylistNode* newNode = head;
    PlaylistNode* prevNewNode = nullptr;
    nodeCounter = 1;

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

        // Insert the node at the new position
        if (prevNewNode == nullptr) {
            head = currNode;
        } else {
            prevNewNode->SetNext(currNode);
        }

        currNode->SetNext(newNode);

        if (newNode == nullptr) {
            tail = currNode;
        }
    }

    cout << "\"" << currNode->GetSongName() << "\" moved to position " << newPos << endl << endl;

}

void EditPlaylist::OutputSpecArtistSong(string artistNameToSet) {
    //do i need to check something ?? 
    if (head == nullptr) {
        return;
    } else {
        PlaylistNode* current = head;
        int artistCount = 1;

        while (current != nullptr) {
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

int EditPlaylist::OutputTotalTime() {
    int totalTime = 0;  
    PlaylistNode* current = head;
    while (current != nullptr) {
        totalTime = totalTime + current->GetSongLength();
        current = current->GetNext();
    }
    return totalTime;
}