#include <iostream>
#include <string>
#include <iomanip>
#include<ctime>
#include<regex>
using namespace std;

struct Candidate {
    string name;
    string party;
    string symbol;
    int votes;
};

class Admin {
private:
    string admnPaswrd;

protected:
    Candidate c[10];
    bool elect_start;
    string elect_SdateTime;
    string elect_EdateTime;
    int candidateCount = 0;

public:
    Admin(string password) : admnPaswrd(password), elect_start(false) {}

    string login(string password) {
        return (password == admnPaswrd) ? "Login successful!" : "Incorrect password!";
    }

    string crnt_dateTime;
                                                   // Function to validate the date and time format
    bool isValidDateTime(const string& dateTime) {
       regex p(R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})");
       return regex_match(dateTime, p);
    }

void startElection() {
    cout << "\n----------------------------------\n";
    cout << "|        START ELECTION          |\n";
    cout << "----------------------------------\n";
    do{
        cout << "\nEnter current date (YYYY-MM-DD) and Time (HH:MM:SS) for 24-hour schedule:  ";
    getline(cin , crnt_dateTime); 
	cin.ignore();

    // Validate current date and time
    if (!isValidDateTime(crnt_dateTime)) {
        cout << "Invalid current date or time format. Please use YYYY-MM-DD HH:MM:SS." << endl;   }
    }while(!isValidDateTime(crnt_dateTime));

    do{
        cout << "Enter election start date and time (YYYY-MM-DD HH:MM:SS): ";
    getline(cin , elect_SdateTime);
    cin.ignore();

    // Validate election start date and time
    if (!isValidDateTime(elect_SdateTime)) {
        cout << "Invalid election start date or time format. Please use YYYY-MM-DD HH:MM:SS." << endl;   }
    }while(!isValidDateTime(elect_SdateTime));

    do{
        cout << "Enter election end date and time (YYYY-MM-DD HH:MM:SS): ";
    getline(cin , elect_EdateTime);
    cin.ignore();
    // Validate election end date and time
    if (!isValidDateTime(elect_EdateTime)) {
        cout << "Invalid election end date or time format. Please use YYYY-MM-DD HH:MM:SS." << endl;   }
    }while(!isValidDateTime(elect_EdateTime));

    bool elect_start = false;

    // Logic to determine election status
    if (crnt_dateTime < elect_SdateTime) {
        cout << "Election has not started yet!\n";
    } else if (crnt_dateTime > elect_SdateTime && crnt_dateTime < elect_EdateTime) {
        cout << "Election is open. You can cast your vote.";
        elect_start = true;
    } else if (elect_EdateTime == crnt_dateTime ) {
        cout << "You can cast your vote\n";
        elect_start = true;
    } else if (elect_EdateTime == crnt_dateTime ) {
        cout << "Election finished!\n";    }
}

    void manageCandidates() {
        int n;
        cout << "\n----------------------------------\n";
        cout << "|      MANAGE CANDIDATES         |\n";
        cout << "----------------------------------\n";
        cout << "How many candidates do you want to enter? ";
        cin >> n;
        cin.ignore();

        for (int i = 0; i < n && candidateCount < 10; ++i) {
            Candidate newCandidate;
            cout << "\nEnter Candidate Name: "; getline(cin, newCandidate.name);
            cout << "Enter Candidate Party: "; getline(cin, newCandidate.party);
            cout << "Enter Party Symbol: "; getline(cin, newCandidate.symbol);
            newCandidate.votes = 0;

            c[candidateCount++] = newCandidate;
            cout << "Candidate " << newCandidate.name << " added successfully!\n";
        }
    }

    void ElectionStatus() {
        cout << "\n----------------------------------\n";
        cout << "|       ELECTION STATUS          |\n";
        cout << "----------------------------------\n";
        if (elect_start) {
            cout << "Election is ongoing from " << elect_SdateTime << " to " << elect_EdateTime << endl;
        } else {
            cout << "Election has not started yet.\n";
        }
    }

    void resetElectionData() {
        elect_start = false;
        candidateCount = 0;
        cout << "\nElection data has been reset!\n";
    }

    void changePassword(string newPassword) {
        admnPaswrd = newPassword;
        cout << "\nPassword changed successfully!\n";
    }

    void displayCandidates() {
    cout << "\n-------------------------------------------\n";
    cout << "|         CANDIDATE INFORMATION           |\n";
    cout << "-------------------------------------------\n";

    if (candidateCount == 0) {
        cout << "No candidates available!\n";
    } else {
        cout << left
		     << setw(20) << "Name"
             << setw(15) << "Party"
             << setw(10) << "Symbol"
             << setw(10) << "Votes" << endl;

        cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;

        for (int i = 0; i < candidateCount; ++i) {
            cout << left
                 << setw(20) << c[i].name
                 << setw(15) << c[i].party
                 << setw(10) << c[i].symbol
                 << setw(10) << c[i].votes << endl;           }
     }
    }

    int getCandidateCount() { return candidateCount; }
    bool isElectionStarted() { return elect_start; }
    Candidate* getCandidates() { return c; }
};

class User {
private:
    string voterID, name, password;
    bool hasVoted;

public:
    User() : hasVoted(false) {}

    void signUp(string id, string nm, string pass) {
        voterID = id;
        name = nm;
        password = pass;
        hasVoted = false;
        cout << "\nRegistration successful for " << name << "!\n";
    }

    bool signIn(string id, string pass) {
        return (voterID == id && password == pass);
    }

    bool canVote() const { return !hasVoted; }

    void vote() {
        if (!hasVoted) {
            hasVoted = true;
            cout << "\nVote cast successfully!\n";
        } else {
            cout << "\nYou have already voted!\n";
        }
    }

    string getID() { return voterID; }
    string getName() { return name; }
};

class VotingSystem : public Admin {
private:
    static const int max_USERS = 100;
    User u[max_USERS];
    int userCount;

public:
    VotingSystem() : Admin("admin123"), userCount(0) {}
    char choice;
    bool setElectionRules() {
        cout << "\n----------------------------------\n";
        cout << "|       ELECTION RULES           |\n";
        cout << "----------------------------------\n";
        cout << "1. Only users above 18 are allowed.\n";
        cout << "2. Must be a citizen of Pakistan.\n";
        cout << "3. Must hold a valid NIC.\n";
        cout << "Do you accept these rules? (Y/N): ";
        char choice;
        cin >> choice;
        return (choice == 'Y' || choice == 'y');
    }
    
    void announceWinner() {
      int maxVotes = 0;
      string winner;

        for (int i = 0; i < getCandidateCount(); ++i) {
            if (c[i].votes > maxVotes) {
                maxVotes = c[i].votes;
                winner = c[i].name;
            }
        }

        if (maxVotes == 0) {
            cout << "\nNo votes have been cast yet.\n";
        } else {
            cout << "\nWinner Announcement:\n";
            cout << "The winner is " << winner << " with " << maxVotes << " votes!\n";        }
    }
     
    void displayVotingPercentage() {
        int totalVotes = 0;
        for (int i = 0; i < getCandidateCount(); ++i) {
            totalVotes += c[i].votes;
        }

        if (totalVotes == 0) {
            cout << "\nNo votes have been cast yet.\n";
            return;
        }

        cout << "\nVoting Percentage Report:\n";
        for (int i = 0; i < getCandidateCount(); ++i) {
            double percentage = (double)c[i].votes / totalVotes * 100;
            cout << c[i].name << " (" << c[i].party << "): " 
                 << fixed << setprecision(2) << percentage << "%\n";        }
    }
    
    void signUp() {
        cout << "\n----------------------------------\n";
        cout << "|      VOTER REGISTRATION        |\n";
        cout << "----------------------------------\n";
        if (userCount >= max_USERS) {
            cout << "User limit reached. Cannot register more voters.\n";
            return;
        }

        while (!setElectionRules()) {
            cout << "Please read and accept the rules to proceed.\n";
        }

        string id, name, pass;
        
        do {
        cout << "Please enter your 13-digit CNIC (numbers only, no dashes): ";
        cin >> id;

        if (id.length() == 13) {												// Check NIC length
            cout << "NIC " << id << " entered successfully.\n";
            break;
        } 
        else if (id.length() < 13) {
            cout << "Your digits in CNIC are less than 13.\n";
        } 
        else {
            cout << "Your digits in CNIC are greater than 13.\n";
        }

        cout << "You have to put CNIC again (Y/y for yes, any other key for no): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        } while (choice == 'Y' || choice == 'y');
        cin.ignore();

        for (int i = 0; i < userCount; ++i) {
            if (u[i].getID() == id) {
                cout << "User already registered!\n";
                return;
            }
        }

        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Password: "; cin >> pass;

        u[userCount++].signUp(id, name, pass);
    }

    void signIn_Vote() {
        cout << "\n----------------------------------\n";
        cout << "|         VOTING PORTAL          |\n";
        cout << "----------------------------------\n";

        string id, pass;
        cout << "Enter Voter ID: "; cin >> id;

    do {
        cout << "Please enter NIC for confirmation (numbers only, no dashes): ";
        cin >> id;

        if (id.length() == 13) {												// Check NIC length
            cout << "NIC " << id << " entered successfully.\n";
            break;
        } 
        else if (id.length() < 13) {
            cout << "Your digits in CNIC are less than 13.\n";
        } 
        else {
            cout << "Your digits in CNIC are greater than 13.\n";
        }

        cout << "You have to put CNIC again (Y/y for yes, any other key for no): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

    } while (choice == 'Y' || choice == 'y');
        
        cout << "Enter Password: "; 		cin >> pass;

        for (int i = 0; i < userCount; ++i) {     //Checking the voters id & password
            if (u[i].signIn(id, pass)) {
                cout << "\nWelcome, " << u[i].getName() << "!\n";

                if (u[i].canVote()) {
                    if (isElectionStarted() && getCandidateCount() > 1) {
                        Candidate* candidates = getCandidates();
                        cout << "\nAvailable Candidates:\n";
                        for (int j = 0; j < getCandidateCount(); ++j) {
                            cout << j + 1 << ". " << candidates[j].name << " - " << candidates[j].party << endl;
                        }

                        int choice;
                        cout << "Select candidate number to vote: ";
                        cin >> choice;

                        if (choice >= 1 && choice <= getCandidateCount()) {
                            candidates[choice - 1].votes++;
                            u[i].vote();
                        } else {
                            cout << "Invalid choice!\n";
                        }
                    } else {
                        cout << "Election not started or no candidates available!\n";
                    }
                } else {
                    cout << "You have already voted!\n";
                }
                return;
            }
        }
        cout << "Invalid ID or Password!\n";
    }

    void checkUserVoteByID() {
        cout << "\n----------------------------------\n";
        cout << "|     CHECK VOTING STATUS        |\n";
        cout << "----------------------------------\n";

        string id;
        cout << "Enter your Voter ID: ";
        cin >> id;

        for (int i = 0; i < userCount; ++i) {
            if (u[i].getID() == id) {
                cout << "Hello, " << u[i].getName() << "!\n";
                cout << "Status: " << (u[i].canVote() ? "NOT VOTED" : "ALREADY VOTED") << endl;
                return;
            }
        }

        cout << "No user found with the entered Voter ID.\n";
    }

    void deleteUserByID() {
        cout << "\n----------------------------------\n";
        cout << "|     DELETE USER ACCOUNT        |\n";
        cout << "----------------------------------\n";

        string id, pass;
        cout << "Enter your Voter ID: ";
        cin >> id;
        cout << "Enter your Password: ";
        cin >> pass;

                for (int i = 0; i < userCount; ++i) {
            if (u[i].signIn(id, pass)) {
                string deletedName = u[i].getName();
                // Shift users left to fill the gap
                for (int j = i; j < userCount - 1; ++j) {
                    u[j] = u[j + 1];
                }
                userCount--;
                cout << "Your account has been deleted successfully. Goodbye, " << deletedName << "!\n";
                return;
            }
        }
        cout << "Invalid ID or Password! Cannot delete account.\n";
    }

    void Exit() {
        cout << "\n----------------------------------\n";
        cout << "|     EXITING VOTING SYSTEM      |\n";
        cout << "----------------------------------\n";
        cout << "Thank you for using the system. Goodbye!\n";
    }
};

int main() {
    VotingSystem vs;
    int mainChoice;

    do {
        cout << "\n==================================\n";
        cout << "|        VOTING SYSTEM MENU      |\n";
        cout << "==================================\n";
        cout << "1. Admin Portal\n";
        cout << "2. Voter/User Portal\n";
        cout << "3. Candidate Information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                string password;
                cout << "\nEnter Admin Password: ";
                cin >> password;
                string result = vs.login(password);
                cout << result << endl;

                if (result == "Login successful!") {
                    int adminChoice;
                    do {
                        cout << "\n----------- ADMIN MENU -----------\n";
                        cout << "1. Start Election\n";
                        cout << "2. Manage Candidates\n";
                        cout << "3. Check Election Status\n";
                        cout << "4. Reset Election Data\n";
                        cout << "5. Change Admin Password\n";
                        cout << "6. Display Voting Percentages\n";
                        cout << "7. Announce Winner\n"; 
                        cout << "8. Back to Main Menu\n";
                        cout << "Enter your choice: ";
                        cin >> adminChoice;

                        switch (adminChoice) {
                            case 1: vs.startElection(); break;
                            case 2: vs.manageCandidates(); break;
                            case 3: vs.ElectionStatus(); break;
                            case 4: vs.resetElectionData(); break;
                            case 5: {
                                string newPassword;
                                cout << "Enter New Password: ";
                                cin >> newPassword;
                                vs.changePassword(newPassword);
                                break;
                            }
                            case 6: vs.displayVotingPercentage(); break;
                            case 7: vs.announceWinner(); break;
                            case 8: cout << "Returning to Main Menu...\n"; break;
                            default: cout << "Invalid choice!\n"; break;
                        }
                    } while (adminChoice != 8);
                }
                break;
            }

            case 2: {
                int voterChoice;
                do {
                    cout << "\n--------- VOTER/USER PORTAL ---------\n";
                    cout << "1. Sign Up\n";
                    cout << "2. Sign In & Vote\n";
                    cout << "3. Check Vote Status by Voter ID\n";
                    cout << "4. Delete My Account\n";
                    cout<< " 5. Display Voting Percentages\n";
                    cout << "6. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> voterChoice;

                    switch (voterChoice) {
                        case 1: vs.signUp(); break;
                        case 2: vs.signIn_Vote(); break;
                        case 3: vs.checkUserVoteByID(); break;
                        case 4: vs.deleteUserByID(); break;
                        case 5: vs.displayVotingPercentage(); break;
                        case 6: cout << "Returning to Main Menu...\n"; break;
                        default: cout << "Invalid choice!\n"; break;
                    }
                } while (voterChoice != 6);
                break;
            }

            case 3: {
                vs.displayCandidates();
                break;
            }

            case 4: {
                vs.Exit();
                break;
            }

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

    } while (mainChoice != 4);

    return 0;
}

