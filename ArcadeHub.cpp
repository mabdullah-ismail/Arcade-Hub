#include <iostream> 
#include <fstream> 
#include <vector> 
#include <map> 
#include <algorithm> 
#include <cstdlib> 
#include <ctime> 
#include <string> 
#define RESET   "\033[0m" 
#define RED     "\033[31m" 
#define GREEN   "\033[32m" 
#define YELLOW  "\033[33m" 
#define BLUE    "\033[34m" 

using namespace std; 


struct User {
    string username; 
    int geoGuesserScore = 0; 
    int problemSolverScore = 0; 
    int hangManScore = 0; 

 
    int getTotalScore() const {
        return geoGuesserScore + problemSolverScore + hangManScore; 
    }
};


struct Location {
    string name; 
    vector<string> hints; 
};


vector<User> users; 
User* currentUser = nullptr; 


void clearScreen(); 
void showFullScreenLoading(); 
void login(); 
void gameMenu(); 
void playGeoGuesser(); 
void playProblemSolver(); 
void playHangMan(); 
void displayHighScores(); 
void exportLeaderboards(); 
string trim(const string& str); 
string toLower(const string& str); 


int main() {
    showFullScreenLoading(); 

    while (true) { 
      
        cout << "\nWelcome to the "  
             << RED << "A" << RESET 
             << GREEN << "r" << RESET 
             << BLUE << "c" << RESET 
             << RED << "a" << RESET 
             << GREEN << "d" << RESET 
             << BLUE << "e" << RESET 
             << RED << "H" << RESET 
             << GREEN << "u" << RESET 
             << BLUE << "b" << RESET 
             << RED << "!" << RESET 
             << " \n";
        cout << "1. Login/Register\n";
        cout << "2. Game Menu\n";
        cout << "3. High Scores\n";
        cout << "4. Export Leaderboards\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        int choice; 
        cin >> choice;
        system("cls"); 

        switch (choice) { 
            case 1:
                login(); 
                break;
            case 2:
                if (currentUser) { 
                    gameMenu(); 
                } else {
                    cout << RED << "Please log in first!\n" << RESET << endl; 
                }
                break;
            case 3:
                displayHighScores(); 
                break;
            case 4:
                exportLeaderboards(); 
                break;
            case 5:
                cout << "Exiting... Goodbye!\n"; 
                return 0;
            default:
                cout << "Invalid option. Try again.\n"; 
        }
    }
}


void clearScreen() {
    system("cls");
}


void showFullScreenLoading() {
    const int totalSteps = 20; 

    for (int frame = 0; frame <= totalSteps; frame++) { 
        clearScreen();

        
        cout << "\n\n\n";
        cout <<  "==============================\n" ;
        cout << "         LOADING...           \n";
        cout << "==============================\n\n";

        cout << "Loading: [";
        for (int i = 0; i < totalSteps; i++) {
            if (i < frame) {
                cout << YELLOW << "#" << RESET; 
            } else {
                cout << YELLOW << " " << RESET; 
            }
        }
        cout << "]\n";
    }

    clearScreen(); 
    cout << "\n\n\n" << RESET; 
    cout << "==============================\n" ;
    cout << "      LOADING COMPLETE        \n" ;
    cout << "==============================\n" ;
}


void login() {
    cout << "\nEnter your username: "; 
    string username; 
    cin.ignore(); 
    getline(cin, username); 

    
    for (auto& user : users) {
        if (user.username == username) {
            currentUser = &user; 
            cout << "Welcome back, " << GREEN << username << RESET << "!\n"; 
            return;
        }
    }

    
    User newUser; 
    newUser.username = username; 
    users.push_back(newUser); 
    currentUser = &users.back(); 
    cout << "Account created. Welcome, " << GREEN << username << RESET << "!\n"; 
}



void gameMenu() {
    while (true) { 
        
        cout << "\nGame Menu:\n";
        cout << RED << "1." << RESET << " Play " << GREEN << "Geo" << RESET << " " << BLUE << "Guesser" << RESET << "\n";
        cout << RED << "2." << RESET << " Play " << GREEN << "Problem" << RESET << " " << BLUE << "Solver" << RESET << "\n";
        cout << RED << "3." << RESET << " Play " << GREEN << "Hang" << RESET << " " << BLUE << "Man" << RESET << "\n";

        cout << RED << "4. Back to Main Menu\n" <<RESET;
        cout <<   "Choose a game: " ;
        int choice; 
        cin >> choice; 

        switch (choice) { 
            case 1:
                showFullScreenLoading(); 
                playGeoGuesser(); 
                break;
            case 2:
                showFullScreenLoading(); 
                playProblemSolver(); 
                break;
            case 3:
                showFullScreenLoading(); 
                playHangMan();
                break;
            case 4:
                return;
            default:
                cout << RED <<  "Invalid option. Try again.\n" << RESET << endl; 
        }
    }
}


string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r"); 
    size_t end = str.find_last_not_of(" \t\n\r");   
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1); 
}


string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower); 
    return lowerStr;
}

void playGeoGuesser() {
    
    vector<Location> locations = {
        {"Paris", {"This City is famous for tourists.", "It has the Eiffel Tower.", "It's in France."}},
        {"Tokyo", {"This city is in Asia.", "It hosted the 2020 Olympics.", "It's the capital of Japan."}},
        {"New York", {"This city is called the Big Apple.", "It has Times Square.", "It's in the USA."}},
        {"Cairo", {"This city is in Africa.", "It has the pyramids of Giza.", "It's the capital of Egypt."}},
        {"Sydney", {"This city has a famous Opera House.", "It's in Australia.", "It has a famous Harbour Bridge."}},
        {"Karachi", {"This city is known as City Of Lights.", "Its in Pakistan.", "It's one of the most populated cities in the World."}},
        {"Mumbai", {"This city is the financial capital of India.", "It is home to Bollywood.", "The Gateway of India is a famous landmark here."}},
        {"Istanbul", {"This city spans two continents, Europe and Asia.", "It was formerly known as Constantinople.", "The Hagia Sophia is a major attraction here."}},
        {"Moscow", {"This city is the capital of Russia.", "It is known for the Kremlin and Red Square.", "It experiences long, snowy winters."}}
    };

    
    random_shuffle(locations.begin(), locations.end());
    const int totalRounds = 5; 
    int roundsPlayed = 0;      

    while (roundsPlayed < totalRounds) {
        Location currentLocation = locations[roundsPlayed]; 
        int hintsShown = 0;                                
        bool correctGuess = false;                       

        cout << "\nRound " << (roundsPlayed + 1) << "\n";

        
        while (hintsShown < currentLocation.hints.size() && !correctGuess) {
            cout << "Hint " << (hintsShown + 1) << ": " << currentLocation.hints[hintsShown] << "\n";
            hintsShown++;

            cout << "Your guess: ";
            string guess;
            cin >> ws; 
            getline(cin, guess); 

            
            guess = toLower(trim(guess));
            string correctAnswer = toLower(currentLocation.name);

            if (guess == correctAnswer) {
                
                cout << GREEN << "Correct! The location is " << currentLocation.name << RESET << ".\n";
                currentUser->geoGuesserScore += (3 - hintsShown + 1) * 10; 
                correctGuess = true;
            } else {
                
                cout << RED << "Incorrect! Try again.\n" << RESET;
            }
        }

        if (!correctGuess) {
           
            cout << "Out of hints! The correct answer was " << currentLocation.name << ".\n";
        }

        roundsPlayed++; 
    }

   
    cout << "\nGame Over!\n";
    cout << "Your total score: " << currentUser->geoGuesserScore << "\n";
}



double generateQuestion(int level) {
    double num1 = rand() % (10 * level) + 1; 
    double num2 = rand() % (10 * level) + 1; 
    char operators[] = {'+', '-', '*', '/'}; 
    char op = operators[rand() % 4];        

    double correctAnswer;

    if (level > 5) {
       
        double num3 = rand() % (10 * level) + 1; 
        char op2 = operators[rand() % 4];      

        cout << "Solve: " << num1 << " " << op << " " << num2 << " " << op2 << " " << num3 << " = ?\n";

        
        switch (op) {
            case '+':
                correctAnswer = num1 + num2;
                break;
            case '-':
                correctAnswer = num1 - num2;
                break;
            case '*':
                correctAnswer = num1 * num2;
                break;
            case '/':
                while (num2 == 0) {
                    num2 = rand() % (10 * level) + 1; 
                }
                correctAnswer = num1 / num2;
                break;
        }

        
        switch (op2) {
            case '+':
                correctAnswer += num3;
                break;
            case '-':
                correctAnswer -= num3;
                break;
            case '*':
                correctAnswer *= num3;
                break;
            case '/':
                while (num3 == 0) {
                    num3 = rand() % (10 * level) + 1; 
                }
                correctAnswer /= num3;
                break;
        }
    } else {
        
        cout << "Solve: " << num1 << " " << op << " " << num2 << " = ?\n";

        
        switch (op) {
            case '+':
                correctAnswer = num1 + num2;
                break;
            case '-':
                correctAnswer = num1 - num2;
                break;
            case '*':
                correctAnswer = num1 * num2;
                break;
            case '/':
                while (num2 == 0) {
                    num2 = rand() % (10 * level) + 1; 
                }
                correctAnswer = num1 / num2;
                break;
        }
    }

    return correctAnswer; 
}


void playProblemSolver() {
    srand(time(0)); 

    int score = 0;                  
    const int totalLevels = 10;    

    cout << "Welcome to the Problem Solver Game!\n";
    cout << "You will face 10 levels of increasing difficulty.\n";

    for (int level = 1; level <= totalLevels; ++level) {
        cout << "\nLevel " << level << ":\n";

        double correctAnswer = generateQuestion(level); 
        double userAnswer;

        cout << "Your answer: ";
        cin >> userAnswer;

       
        if (abs(userAnswer - correctAnswer) < 0.001) {
            cout << GREEN << "Correct!\n" << RESET;
            score += level * 10; 
        } else {
            cout << RED << "Wrong! " << RESET << "The correct answer was " << correctAnswer << ".\n";
        }
    }

    
    cout << "\nGame Over!\n";
    cout << "Your final score is: " << score << "\n";

    if (score == totalLevels * 10 * (totalLevels + 1) / 2) {
        cout << "Amazing! You got all the answers correct!\n";
    } else if (score >= totalLevels * 5 * (totalLevels + 1) / 2) {
        cout << "Great job! You scored above average!\n";
    } else {
        cout << "Good effort! Keep practicing to improve!\n";
    }

    currentUser->problemSolverScore += score; 
}


void playHangMan() {
    
    vector<pair<string, string>> words = {
        {"apple", "A red or green fruit often found in pies"},
        {"banana", "A yellow fruit, often found in bunches"},
        {"cherry", "A small, red, sweet fruit with a pit"},
        {"grape", "A small, round, purple or green fruit often used in wine"},
        {"orange", "A citrus fruit that's also a color"},
        {"pear", "A green or yellow fruit with a unique shape"},
        {"peach", "A fuzzy fruit with a pit, often associated with Georgia"},
        {"lemon", "A sour yellow citrus fruit"},
        {"lime", "A small green citrus fruit often used in drinks"},
        {"melon", "A large, sweet fruit with a hard rind"},
        {"cat", "A common household pet that purrs"},
        {"dog", "Man's best friend"},
        {"bird", "An animal with feathers and the ability to fly"},
        {"fish", "An aquatic animal with fins and gills"},
        {"cow", "A large animal often raised for milk or beef"},
        {"pig", "An animal known for its curly tail and love of mud"},
        {"horse", "A large animal often used for riding"},
        {"duck", "A waterfowl known for its quack"},
        {"sheep", "An animal known for its woolly coat"},
        {"goat", "An animal often found on farms, known for climbing"},
        {"sun", "The star at the center of our solar system"},
        {"moon", "Earth's natural satellite"},
        {"star", "A luminous point in the night sky"},
        {"sky", "The expanse of air over the Earth"},
        {"cloud", "A mass of condensed water vapor in the sky"},
        {"rain", "Precipitation in liquid form"},
        {"snow", "Frozen precipitation in the form of flakes"},
        {"wind", "Air in motion"},
        {"tree", "A tall plant with leaves and a trunk"},
        {"bush", "A small, dense, woody plant"},
        {"leaf", "A green part of a plant that absorbs sunlight"},
        {"flower", "The colorful reproductive part of a plant"},
        {"grass", "A green plant that covers lawns and fields"},
        {"rock", "A hard, natural mineral material"},
        {"sand", "Small grains of mineral found on beaches"},
        {"soil", "The upper layer of Earth in which plants grow"},
        {"beach", "A sandy or pebbly shore by a body of water"},
        {"mountain", "A large natural elevation of the Earth's surface"},
        {"valley", "A low area of land between hills or mountains"},
        {"forest", "A large area covered with trees"},
        {"door", "An entryway that opens and closes"},
        {"window", "An opening in a wall to let in light or air"},
        {"chair", "A piece of furniture for sitting"},
        {"table", "A flat surface with legs used for work or dining"},
        {"bed", "A piece of furniture used for sleeping"},
        {"lamp", "A device that produces light"},
        {"rug", "A floor covering made of fabric"},
        {"clock", "A device used to measure and display time"},
        {"phone", "A device used for communication"},
    };

  
    auto getRandomWordAndHint = [&]() -> pair<string, string> {
        srand(static_cast<unsigned int>(time(0)));
        int randomIndex = rand() % words.size();
        return words[randomIndex];
    };

    do {
        
        clearScreen();
        cout << R"(
        ===================================
               Welcome to Hangman Game!
        ===================================
        )" << endl;

        
        auto [selectedWord, hint] = getRandomWordAndHint();
        string guessedWord(selectedWord.length(), '_'); 
        int attempts = selectedWord.length();         
        bool wordGuessed = false;

        
        while (attempts > 0 && !wordGuessed) {
            cout << "\nWord: ";
            for (char c : guessedWord) {
                cout << c << " "; 
            }
            cout << "\nHint: " << hint; 
            cout << "\nAttempts left: " << attempts << "\n";

           
            cout << "Enter your guess (a single letter): ";
            char guess;
            cin >> guess;

           
            bool found = false;
            for (size_t i = 0; i < selectedWord.length(); i++) {
                if (tolower(selectedWord[i]) == tolower(guess) && guessedWord[i] == '_') {
                    guessedWord[i] = selectedWord[i];
                    found = true;
                }
            }

            if (!found) {
                cout << RED << "Wrong guess!\n" << RESET;
            } else {
                cout << GREEN << "Correct guess!\n" << RESET;
            }

           
            if (guessedWord == selectedWord) {
                wordGuessed = true;
            }
        }

      
        clearScreen();
        if (wordGuessed) {
            cout << "CONGRATULATIONS! You guessed the word: " << selectedWord << endl;
            currentUser->hangManScore += attempts * 10; 
        } else {
            cout << RED << "GAME OVER!" << RESET << " The word was: " << selectedWord << endl;
        }

    
        cout << "Your current Hangman score: " << currentUser->hangManScore << "\n";

      
        cout << "\nDo you want to play again? (y/n): ";
        char choice;
        cin >> choice;
        if (tolower(choice) != 'y') {
            break;
        }
    } while (true);

    cout << "\nThank you for playing Hangman! Goodbye!\n";
}


void displayHighScores() {
    if (users.empty()) {
        cout << "\nNo scores available yet. Start playing to create a leaderboard!\n";
        return;
    }


    vector<User> sortedUsers = users;
    sort(sortedUsers.begin(), sortedUsers.end(), [](const User& a, const User& b) {
        return a.getTotalScore() > b.getTotalScore();
    });

 
    cout << GREEN << "\nHigh Scores:\n" << RESET;
    cout << "-----------------------------------------------------------------\n";
    cout << "Position | User  | GeoGuesser | ProblemSolver | HangMan | Total\n";
    cout << "-----------------------------------------------------------------\n";

    int position = 1;
    for (const auto& user : sortedUsers) {
        cout << position << "         | " 
             << user.username
             << "    | " << user.geoGuesserScore
             << "     | " << user.problemSolverScore
             << "      | " << user.hangManScore
             << "       | " << user.getTotalScore() << "\n";
        position++;
    }

    cout << "-----------------------------------------------------------------\n";
}


void exportLeaderboards() {
    ofstream file("leaderboards.txt");
    if (file.is_open()) {
        
        vector<User> sortedUsers = users;
        sort(sortedUsers.begin(), sortedUsers.end(), [](const User& a, const User& b) {
            return a.getTotalScore() > b.getTotalScore();
        });

        
        file << "High Scores:\n";
        file << "-----------------------------------------------------------------------\n";
        file << "Position | User       | GeoGuesser | ProblemSolver | HangMan | Total\n";
        file << "-----------------------------------------------------------------------\n";

        int position = 1;
        for (const auto& user : sortedUsers) {
            file << position << "         | " 
                 << user.username
                 << "     | " << user.geoGuesserScore
                 << "     | " << user.problemSolverScore
                 << "     | " << user.hangManScore
                 << "     | " << user.getTotalScore() << "\n";
            position++;
        }

        file << "-----------------------------------------------------------------------\n";
        file.close();
        cout << "Leaderboards exported to leaderboards.txt!\n";
    } else {
        cout << "Error: Could not open file for writing.\n";
    }
}

  
