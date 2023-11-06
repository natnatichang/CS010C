#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

int main() {
    // Declare variables to store user input
    string playlistTitle, idToSet, songNameToSet, artistNameToSet;
    int songLengthToSet, currPos, newPos;

    // Prompt user to enter playlist title
    cout << "Enter playlist's title:" << endl;
    if(!getline(cin, playlistTitle)) return 1;
    cout << endl;

    // Create an object of the Playlist class
    Playlist myPlaylist;

    // Declare a variable to store user input for menu selection
    char userInput;

    // Display the menu and accept user input until user enters 'q' to quit
    do {
        // Display menu options and prompt user to select an option
        myPlaylist.PrintMenu(playlistTitle);
        if(!(cin >> userInput)) return 1;

        // Ignore the newline character left in the input buffer
        cin.ignore();  
        
        if (userInput == 'a') {
            // Prompt user to enter details to add a new song to the playlist
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            if(!(cin >> idToSet)) return 1;
            cin.ignore();
            
            cout << "Enter song's name:" << endl; 
            if(!getline(cin, songNameToSet)) return 1;

            cout << "Enter artist's name:" << endl;
            if(!getline(cin, artistNameToSet)) return 1;
            
            cout << "Enter song's length (in seconds):" << endl; 
            while (!(cin >> songLengthToSet)) {
                // Check that the user enters an integer for song length
                cin.clear();
                cin.ignore();
            }

            // Call the AddSong method to add the new song
            myPlaylist.AddSong(idToSet, songNameToSet, artistNameToSet, songLengthToSet);
            cout << endl;

        } else if (userInput == 'd') {
            // Prompt user to enter ID of the song to be removed
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            if(!(cin >> idToSet)) return 1;

            // Call the RemoveSong method to remove the song
            myPlaylist.RemoveSong(idToSet);

        } else if (userInput == 'c') {
            // Prompt user to enter the current position and new position of the song to be moved
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            if(!(cin >> currPos)) return 1;

            cout << "Enter new position for song:" << endl;
            if(!(cin >> newPos)) return 1;
            
            // Call the ChangeSongPosition method to change the position of the song
            myPlaylist.ChangeSongPosition(currPos, newPos);

        } else if (userInput == 's') {
            // Prompt user to enter the artist name and display songs by that artist
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            if(!getline(cin, artistNameToSet)) return 1;
            cout << endl;

            // Call the OutputSpecArtistSong method to find the songs by artist
            myPlaylist.OutputSpecArtistSong(artistNameToSet);

        } else if (userInput == 't') {
            // Display the total time of the playlist in seconds
            cout << endl;
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;

            // Call the OutputTotalTime method to output total time in seconds
            cout << "Total time: " << myPlaylist.OutputTotalTime() << " seconds" << endl << endl;

        } else if (userInput == 'o') {
            // Call the PrintFullPlaylist method to output all the songs in playlist
            cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
            myPlaylist.PrintFullPlaylist(); 

        } 
    } while (userInput != 'q');

    return 0;
}
