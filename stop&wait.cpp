#include <iostream>
#include <string>

using namespace std;

int main() {
    int total_frames;

    // Get total number of frames from the user
    cout << "Enter the total number of frames to send: ";
    if (!(cin >> total_frames) || total_frames <= 0) {
        cout << "Invalid number of frames." << endl;
        return 1;
    }

    cout << "\n--- Starting Stop & Wait Protocol Simulation ---\n" << endl;

    int current_frame = 1;

    // Loop until all requested frames are successfully acknowledged
    while (current_frame <= total_frames) {
        cout << " Sending Frame " << current_frame << "..." << endl;

        // Rule 1 & 2: First 2 transmissions succeed (Frame 1 and Frame 2)
        if (current_frame == 1 || current_frame == 2) {
            cout << " Frame " << current_frame << " received successfully." << endl;
            
            cout << " ACK " << current_frame << " received successfully!\n" << endl;
            current_frame++; // Move to next frame
        }
        // Rule 3: 3rd frame transmission is lost
        else if (current_frame == 3) {
            cout << " Frame 3  LOST !" << endl;
            cout << " Timeout timer expired! No ACK received." << endl;
            cout << " Retransmitting Frame 3..." << endl;
            
            // Retransmission attempt succeeds
            cout << " Sending Frame 3 (Retransmission)..." << endl;
            cout << " Frame 3 received successfully." << endl;
           
            cout << " ACK 3 received successfully!\n" << endl;
            current_frame++; // Move to next frame
        }
        // Rule 4: 4th frame acknowledgement is lost
        else if (current_frame == 4) {
            cout << " Frame 4 received successfully." << endl;
            cout << " Sending ACK 4..." << endl;
            cout << " ACK 4  LOST in transit!" << endl;
            cout << " Timeout timer expired! ACK not received." << endl;
            cout << " Retransmitting Frame 4...\n" << endl;

            // Retransmission attempt succeeds
            cout << " Sending Frame 4 (Retransmission)..." << endl;
            cout << " Duplicate Frame 4 detected! Discarding frame copy." << endl;
           
            cout << " ACK 4 received successfully!\n" << endl;
            current_frame++; // Move to next frame
        }
        // General Rule: Any subsequent frames (5+) clear normally
        else {
            cout << " Frame " << current_frame << " received successfully." << endl;
           
            cout << " ACK " << current_frame << " received successfully!\n" << endl;
            current_frame++;
        }
    }

    cout << "--- Transmission Completed Successfully ---" << endl;
    cout << "All " << total_frames << " frames sent and acknowledged." << endl;
    
}