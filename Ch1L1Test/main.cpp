#include <iostream>
#include <string>

using namespace std;
#include "Playlist.h"

//note to self that () {} should have a space
//note to self should i be checking for the cin?
int main() {
    //note to self that this should probably have better names lol
    string playlistTitle, idToSet, songNameToSet, artistNameToSet;
    int songLengthToSet, currPos, newPos;

    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    cout << endl;

    EditPlaylist myPlaylist;
    char userInput;

    do {
        myPlaylist.PrintMenu(playlistTitle);
        cin >> userInput;
        cin.ignore();  
        
        if (userInput == 'a') {
            
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> idToSet;
            cin.ignore();
            
            cout << "Enter song's name:" << endl; 
            getline(cin, songNameToSet);
           
            cout << "Enter artist's name:" << endl;
            getline(cin, artistNameToSet);
            
            cout << "Enter song's length (in seconds):" << endl; // why does this end need to be here?? 
            cin >> songLengthToSet; //NTS: if not a number, then it goes infinite loop so maybe need to check her 
            //cin.get(songLengthToSet);

            //checks to make sure that an integer is put into the input
            while(!cin.good()) {
                cin.clear();
                cin.ignore();
                cin >> songLengthToSet;
            }

            myPlaylist.AddSong(idToSet, songNameToSet, artistNameToSet, songLengthToSet);
            cout << endl; // do i really need this here? 

        } else if (userInput == 'd') {
            //note to self, does this go inside the other file ? 
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> idToSet;
            myPlaylist.RemoveSong(idToSet);
        } else if (userInput == 'c') {
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> currPos;
            cout << "Enter new position for song:" << endl;
            cin >> newPos;
            myPlaylist.ChangeSongPosition(currPos, newPos);
        } else if (userInput == 's') {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            getline(cin, artistNameToSet);
            cout << endl;
            myPlaylist.OutputSpecArtistSong(artistNameToSet);
        } else if (userInput == 't') {
            cout << endl;
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout << "Total time: " << myPlaylist.OutputTotalTime() << " seconds" << endl << endl;
        } else if (userInput == 'o') {
            cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
            myPlaylist.PrintFullPlaylist(); 
        } 
    } while (userInput != 'q');
    return 0;
}
