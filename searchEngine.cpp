#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <filesystem>
#include <conio.h>
#include <chrono>
#include <iomanip>

using namespace std;
namespace fs = filesystem;
using namespace std::chrono;

const string folderPath = "C:\\search-engine\\Project1\\Project1\\2";
string blue = "\033[34m";
string red = "\033[31m";
string yellow = "\033[33m";
string green = "\033[32m";
string reset = "\033[0m";

void gotoRowCol(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void displayGoogle(int startRow, int startCol) {
    string blue = "\033[34m";
    string red = "\033[31m";
    string yellow = "\033[33m";
    string green = "\033[32m";
    string reset = "\033[0m";

    cout << "\033[2J";
    int row = startRow;
    int col = startCol;

    gotoRowCol(row, col);
    cout << blue << "  GGGG ";
    gotoRowCol(row + 1, col);
    cout << " G     ";
    gotoRowCol(row + 2, col);
    cout << " G  GG ";
    gotoRowCol(row + 3, col);
    cout << " G   G ";
    gotoRowCol(row + 4, col);
    cout << "  GGGG " << reset;

    col += 7; 

    gotoRowCol(row, col);
    cout << red << "  OOO  ";
    gotoRowCol(row + 1, col);
    cout << " O   O ";
    gotoRowCol(row + 2, col);
    cout << " O   O ";
    gotoRowCol(row + 3, col);
    cout << " O   O ";
    gotoRowCol(row + 4, col);
    cout << "  OOO  " << reset;

    col += 7;

    gotoRowCol(row, col);
    cout << yellow << "  OOO  ";
    gotoRowCol(row + 1, col);
    cout << " O   O ";
    gotoRowCol(row + 2, col);
    cout << " O   O ";
    gotoRowCol(row + 3, col);
    cout << " O   O ";
    gotoRowCol(row + 4, col);
    cout << "  OOO  " << reset;

    col += 7;

    gotoRowCol(row, col);
    cout << blue << "  GGGG ";
    gotoRowCol(row + 1, col);
    cout << " G     ";
    gotoRowCol(row + 2, col);
    cout << " G  GG ";
    gotoRowCol(row + 3, col);
    cout << " G   G ";
    gotoRowCol(row + 4, col);
    cout << "  GGGG " << reset;

    col += 7;



    gotoRowCol(row, col);
    cout << green << " L    ";
    gotoRowCol(row + 1, col);
    cout << " L    ";
    gotoRowCol(row + 2, col);
    cout << " L    ";
    gotoRowCol(row + 3, col);
    cout << " L    ";
    gotoRowCol(row + 4, col);
    cout << " LLLLL" << reset;

    col += 7;

    gotoRowCol(row, col);
    cout << red << " EEEE ";
    gotoRowCol(row + 1, col);
    cout << " E    ";
    gotoRowCol(row + 2, col);
    cout << " EEEE ";
    gotoRowCol(row + 3, col);
    cout << " E    ";
    gotoRowCol(row + 4, col);
    cout << " EEEE " << reset;
}
bool isClickInRange(int clickX, int clickY, int targetX, int targetY, int tolerance) {
    return (abs(clickX - targetX) <= tolerance) && (abs(clickY - targetY) <= tolerance);
}
void displaySearchBar() {

    string yellow = "\033[33m";
    string red = "\033[31m";

    gotoRowCol(11, 1);
    cout << yellow << "_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________";

    gotoRowCol(17, 100);
    cout << red << "|Search|";

    gotoRowCol(15, 1);
    cout << yellow << "_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________";
}
void logoMain(long long fileProcessingTime = 0, long long lastQueryTime = -1, long long totalQueryTime = 0, int queryCount = 0) {
    system("cls");
    displayGoogle(5, 85);
    displaySearchBar();

    cout << red;
    gotoRowCol(1, 1);
    // << "File Processing Time: " << fileProcessingTime << " ms";

    /*if (lastQueryTime >= 0) {
        gotoRowCol(2, 1);
        cout << "Last Query Execution Time: " << lastQueryTime << " ms";
    }*/
    cout << reset;
}
void displayLoadingBar2() {

    system("cls");
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177;
    int bar2 = 219;

    cout << "\n\n\n\t\t\t\Setting Up The Search Engine...";
    cout << "\n\n\n\t\t\t\t";

    for (int i = 0; i < 25; i++) {
        cout << (char)bar1;
    }

    cout << "\r";
    cout << "\t\t\t\t";

    for (int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(150);
    }

    cout << "\n\t\t\t\t" << (char)1 << "!";
}
void searchBarInput(string& input) {
    int row = 13, col = 1;
    char ch;
    input.clear();
    gotoRowCol(row, col);
    cout << "                                                                 "; 
    gotoRowCol(row, col);
    gotoRowCol(17, 100);
    cout << red << "|Search|";
    gotoRowCol(row, col);

    while (true) {
        ch = _getch(); 
        if (ch == '\r') { // enter key
            break;
        }
        else if (ch == '\b') { // backspace key
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b"; 
            }
        }
        else {
            input += ch;
            cout << ch;
        }
    }
}
void displayResults(const vector<string>& results, int startRow) {
    int col = 10;
    for (const auto& line : results) {
        gotoRowCol(startRow++, col);
        cout << line;
    }
}

//specifically for + based input
vector<string> parseInput(const string& input) {
    vector<string> words;
    int start = 0, end;
    while ((end = input.find('+', start)) != string::npos) {
        words.push_back(input.substr(start, end - start));
        start = end + 1;
    }
    words.push_back(input.substr(start)); 
    return words;
}     
vector<string> parseInput_V2(const string& input) {
    vector<string> words;
    string word;
    for (char ch : input) {
        if (ch == '+') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();          
            }
        }
        else {
            word += ch; 
        }
    }
    if (!word.empty()) {
        words.push_back(word); 
    }
    return words;
}

//specifically for - based input
vector<string> parseInputMinus(const string& input) {
    vector<string> words;
    int start = 0, end;
    while ((end = input.find('-', start)) != string::npos) {
        words.push_back(input.substr(start, end - start));
        start = end + 1;
    }
    words.push_back(input.substr(start));
    return words;
}
vector<string> parseSentence(const string& sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

class WordInDocument {
public:
    unordered_map<string, vector<int>> documentPositions; //docName --> docPositions

    WordInDocument() = default;

    void addPosition(const string& docName, int pos) {
        documentPositions[docName].push_back(pos);
    }
};
void processFile(const string& fileName, unordered_map<string, WordInDocument>& wordMap) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string word;
    int position = 0;

    while (file >> word) {
        position++;

        transform(word.begin(), word.end(), word.begin(), ::tolower);
        wordMap[word].addPosition(fileName, position);
    }

    file.close();
}
void crawlAndDump(const string& folderPath, const string& dumpFile) {
    ofstream outFile(dumpFile);
    if (!outFile.is_open()) {
        cerr << "Error creating dump file!" << endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            outFile << entry.path().string() << endl;
        }
    }

    outFile.close();
    cout << "Crawling complete. File list saved to " << dumpFile << endl;
}
vector<string> loadDump(const string& dumpFile) {
    vector<string> fileNames;
    ifstream inFile(dumpFile);
    if (!inFile.is_open()) {
        cerr << "Error opening dump file!" << endl;
        return fileNames;
    }

    string fileName;
    while (getline(inFile, fileName)) {
        fileNames.push_back(fileName);
    }

    inFile.close();
    return fileNames;
}
bool compareDocuments(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second; //sort wrt to frequenct in this version
}
bool compareDocuments_V2(const pair<string, pair<int, int>>& a, const pair<string, pair<int, int>>& b) {

    if (a.second.first != b.second.first) {
        return a.second.first > b.second.first;     //compare based on matched words 
    }
    return a.second.second > b.second.second;       //now compare wrt to total occurences
}
void displayResultsAsPaginatedCards(const vector<pair<string, int>>& documents) {

    const int maxCardsPerLine = 6;
    const int cardsPerPage = 36;     
    const int cardHeight = 6;
    const int cardWidth = 30;
    const int verticalSpacing = cardHeight + 2;
    const int horizontalSpacing = cardWidth + 4;
    int currentPage = 0;
    char choice;

    int totalPages = (documents.size() + cardsPerPage - 1) / cardsPerPage;

    do {
        logoMain();

        int startIdx = currentPage * cardsPerPage;
        int endIdx = min(startIdx + cardsPerPage, static_cast<int>(documents.size()));

        int currentRow = 19;  
        int currentCol = 2;  
        int cardCount = 0;

        gotoRowCol(1, 1);
        cout << "\nPage " << (currentPage + 1) << " of " << totalPages << endl;

        for (int i = startIdx; i < endIdx; ++i) {
            const auto& doc = documents[i];
            bool isHighlighted = doc.second > 1000;

            if (isHighlighted) {
                cout << "\033[32m"; 
            }

            int r = currentRow;
            int c = currentCol;

            gotoRowCol(r, c);
            cout << "+";
            for (int i = 0; i < cardWidth - 2; i++) cout << "-";
            cout << "+";
            r++;

            gotoRowCol(r, c);
            cout << "|";
            int padding = (cardWidth - 2 - doc.first.size()) / 2;
            for (int i = 0; i < padding; i++) cout << " ";
            cout << doc.first;
            for (int i = 0; i < cardWidth - 2 - padding - doc.first.size(); i++) cout << " ";
            cout << "|";
            r++;

            string occurrencesText = "Occurrences: " + to_string(isHighlighted ? doc.second - 1000 : doc.second);
            gotoRowCol(r, c);
            cout << "|";
            int occurrencesPadding = (cardWidth - 2 - occurrencesText.size()) / 2;
            for (int i = 0; i < occurrencesPadding; i++) cout << " ";
            cout << occurrencesText;
            for (int i = 0; i < cardWidth - 2 - occurrencesPadding - occurrencesText.size(); i++) cout << " ";
            cout << "|";
            r++;

            gotoRowCol(r, c);
            cout << "|";
            for (int i = 0; i < cardWidth - 2; i++) cout << " ";
            cout << "|";
            r++;

            gotoRowCol(r, c);
            cout << "+";
            for (int i = 0; i < cardWidth - 2; i++) cout << "-";
            cout << "+";

            if (isHighlighted) {
                cout << "\033[0m"; 
            }

            cardCount++;
            currentCol += horizontalSpacing; 

            if (cardCount % maxCardsPerLine == 0) {
                currentCol = 2;
                currentRow += verticalSpacing;
            }
        }
        cout << "\n\nUse [n] for next page, [p] for previous page, [q] to quit.\n";
        choice = _getch();
        if (choice == 'n' && currentPage < totalPages - 1) {
            currentPage++;
        }
        else if (choice == 'p' && currentPage > 0) {
            currentPage--;
        }
        else if (choice == 'q') {
            break;
        }
    } while (choice != 'q');
}
void displayResultsAsCards_V2(const vector<pair<string, pair<int, int>>>& documents) {

    const int maxCardsPerLine = 6;
    const int maxCardsPerPage = 36; 
    const int cardHeight = 6;
    const int cardWidth = 30;
    const int horizontalSpacing = cardWidth + 4;

    int totalCards = documents.size();
    int totalPages = (totalCards + maxCardsPerPage - 1) / maxCardsPerPage;

    int currentPage = 0;
    char choice;

    do {
        logoMain();

        int currentRow = 19; 
        int currentCol = 2; 
        int cardCount = 0;

        gotoRowCol(1, 1);
        cout << "Page " << currentPage + 1 << " of " << totalPages << "\n\n";

        for (int i = currentPage * maxCardsPerPage; i < min((currentPage + 1) * maxCardsPerPage, totalCards); ++i) {
            const string& fileName = documents[i].first;
            int matchedWords = documents[i].second.first;
            int occurrences = documents[i].second.second;

            int r = currentRow;
            int c = currentCol;

            gotoRowCol(r, c);
            cout << "+";
            for (int j = 0; j < cardWidth - 2; j++) cout << "-";
            cout << "+";
            r++;

            gotoRowCol(r, c);
            cout << "|";
            int padding = (cardWidth - 2 - fileName.size()) / 2;
            for (int j = 0; j < padding; j++) cout << " ";
            cout << fileName;
            for (int j = 0; j < cardWidth - 2 - padding - fileName.size(); j++) cout << " ";
            cout << "|";
            r++;

            string matchedText = "Matched: " + to_string(matchedWords);
            gotoRowCol(r, c);
            cout << "|";
            int matchedPadding = (cardWidth - 2 - matchedText.size()) / 2;
            for (int j = 0; j < matchedPadding; j++) cout << " ";
            cout << matchedText;
            for (int j = 0; j < cardWidth - 2 - matchedPadding - matchedText.size(); j++) cout << " ";
            cout << "|";
            r++;

            string occurrencesText = "Occurrences: " + to_string(occurrences);
            gotoRowCol(r, c);
            cout << "|";
            int occurrencesPadding = (cardWidth - 2 - occurrencesText.size()) / 2;
            for (int j = 0; j < occurrencesPadding; j++) cout << " ";
            cout << occurrencesText;
            for (int j = 0; j < cardWidth - 2 - occurrencesPadding - occurrencesText.size(); j++) cout << " ";
            cout << "|";
            r++;

            gotoRowCol(r, c);
            cout << "|";
            for (int j = 0; j < cardWidth - 2; j++) cout << " ";
            cout << "|";
            r++;

            gotoRowCol(r, c);
            cout << "+";
            for (int j = 0; j < cardWidth - 2; j++) cout << "-";
            cout << "+";

            cardCount++;
            currentCol += horizontalSpacing;

            if (cardCount % maxCardsPerLine == 0) {
                currentCol = 1;
                currentRow += cardHeight + 1;
            }
        }

        cout << "\nUse 'n' for next page, 'p' for previous page, or 'q' to quit.\n";

        choice = _getch(); 
        if (choice == 'n' && currentPage < totalPages - 1) {
            currentPage++;
        }
        else if (choice == 'p' && currentPage > 0) {
            currentPage--;
        }
    } while (choice != 'q');
}
string normalizeWord(const string& word) {
    string normalized;
    for (char c : word) {
        if (isalnum(c)) {
            normalized += tolower(c);
        }
    }
    return normalized;
}

void queryWord(const string& word, const unordered_map<string, WordInDocument>& wordMap) {

    auto it = wordMap.find(word);
    if (it == wordMap.end()) {
        gotoRowCol(13, 1);
        cout << "Sorry!! no documents with such word found:/";
        return;
    }

    vector<pair<string, int>> documents;
    for (const auto& doc : it->second.documentPositions) {
        fs::path filePath(doc.first);
        string fileName = filePath.filename().string();
        int occurences = doc.second.size();
        pair<string, int> p = make_pair(fileName, occurences);
        documents.push_back(p);
    }

    sort(documents.begin(), documents.end(), compareDocuments);
    cout << reset;
    gotoRowCol(19,1);

    displayResultsAsPaginatedCards(documents);

   /* const int filenameWidth = 30;
    const int occurrenceWidth = 10;
    cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';

    cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';

    for (const auto& doc : documents) {
        cout << left << setw(filenameWidth) << doc.first
            << " | "
            << setw(occurrenceWidth) << doc.second << '\n';

        cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';
    }*/
}
void queryTwoWords(const string& word1, const string& word2, const unordered_map<string, WordInDocument>& wordMap) {
    unordered_map<string, pair<int, int>> documentScores; 
    //docname --> word1Score , word2Score

    bool f1 = true, f2 = true;
    auto it = wordMap.find(word1);
    if (it == wordMap.end()) {
       
        f1 = false;
    }

    it = wordMap.find(word2);
    if (it == wordMap.end()) {
        f2 = false;
    }

    if (!f1 && !f2) {
        gotoRowCol(13, 1);
        cout << "Sorry!! no documents with such words found:/";
        return;
    }


    auto it1 = wordMap.find(word1);

    if (it1 != wordMap.end()) {

        for (const auto& doc : it1->second.documentPositions) { //traverse through the doc positions for the corresponding word

            string docName = doc.first;
            int occurences = doc.second.size();

            if (documentScores.find(docName) == documentScores.end()) {

                documentScores[docName] = { 0,0 };
            }
            documentScores[docName].first = occurences;
        }
    }

    auto it2 = wordMap.find(word2);

    if (it2 != wordMap.end()) {

        for (const auto& doc : it2->second.documentPositions) {

            string docName = doc.first;
            int occurrences = doc.second.size();

            if (documentScores.find(docName) == documentScores.end()) {
                documentScores[docName] = { 0, 0 };
            }
            documentScores[docName].second = occurrences;
        }
    }


    vector<pair<string, int>> documents;

    for (const auto& doc : documentScores) {
        string docName = doc.first;
        int totalOccurrences = doc.second.first + doc.second.second; 

        bool containsBoth = (doc.second.first > 0 && doc.second.second > 0); 
        fs::path filePath(doc.first);
        string fileName = filePath.filename().string();

        int finalOccurrences = totalOccurrences;
        if (containsBoth) {
            finalOccurrences += 1000; 
        }

        pair<string, int> p = make_pair(fileName, finalOccurrences);
        documents.push_back(p);
    }

    sort(documents.begin(), documents.end(), compareDocuments);

    cout << reset;
    gotoRowCol(19,1);

    displayResultsAsPaginatedCards(documents);

   /* const int filenameWidth = 30;
    const int occurrenceWidth = 10;
    cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';

    cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';

    for (auto& doc : documents) {

        if (doc.second > 1000) {
            cout << "\033[32m";
            doc.second -= 1000;
        }

        cout << left << setw(filenameWidth) << doc.first
            << " | "
            << setw(occurrenceWidth) << doc.second << '\n';


        cout << "\033[0m";


        cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';
    }*/
}
void queryMultipleWords(const vector<string>& words, const unordered_map<string, WordInDocument>& wordMap) {

    unordered_map<string, pair<int, int>> documentScores; //made a custom map that will help with finding the doc
                                                          //with corresponding word and its scores

    for (const auto& word : words) {

        auto it = wordMap.find(word);       //main map iterator 

        if (it != wordMap.end()) {         

            for (const auto& doc : it->second.documentPositions) {
                
                string docName = doc.first;
                int occurrences = doc.second.size();

                if (documentScores.find(docName) == documentScores.end()) {
                    documentScores[docName] = { 0, 0 }; //if docname was not found than simply init the score 0,0
                }

                //if found than simply update the matched score and overall score
                documentScores[docName].first += 1;  
                documentScores[docName].second += occurrences; 
            }
        }
    }


    vector<pair<string, pair<int, int>>> sortedDocuments;
    for (const auto& doc : documentScores) {

        fs::path filePath(doc.first);
        string fileName = filePath.filename().string();                     //dont want the entire path only the filename
        
        sortedDocuments.push_back({ fileName, doc.second });
    }

    sort(sortedDocuments.begin(), sortedDocuments.end(), compareDocuments_V2); //for this case sort the docs based on words matched and then occurences


    //printing stuff 
    cout << reset;
    gotoRowCol(19,1);

    //displayResultsAsCards_V2(sortedDocuments);
    displayResultsAsCards_V2(sortedDocuments);
    /*const int filenameWidth = 30;
    const int matchedWidth = 10;
    const int occurrenceWidth = 10;
    cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(matchedWidth) << "Matched"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';

    cout << string(filenameWidth + matchedWidth + occurrenceWidth + 6, '-') << '\n';

    for (const auto& doc : sortedDocuments) {
        cout << left << setw(filenameWidth) << doc.first
            << " | "
            << setw(matchedWidth) << doc.second.first
            << " | "
            << setw(occurrenceWidth) << doc.second.second << '\n';

        cout << string(filenameWidth + matchedWidth + occurrenceWidth + 6, '-') << '\n';
    }*/
}

//the "+" operation functions 
void queryTwoWordsPlus(const string& word1, const string& word2, const unordered_map<string, WordInDocument>& wordMap) {

    unordered_map<string, pair<int, int>> documentScores;
    //docname --> word1Score , word2Score

    bool f1 = true, f2 = true;
    auto it = wordMap.find(word1);
    if (it == wordMap.end()) {

        f1 = false;
    }

    it = wordMap.find(word2);
    if (it == wordMap.end()) {
        f2 = false;
    }

    if (!f1 || !f2) {
        gotoRowCol(13, 1);
        cout << "Sorry!! no documents with both words found:/";
        return;
    }

    auto it1 = wordMap.find(word1);

    if (it1 != wordMap.end()) {

        for (const auto& doc : it1->second.documentPositions) { //traverse through the doc positions for the corresponding word

            string docName = doc.first;
            int occurences = doc.second.size();

            if (documentScores.find(docName) == documentScores.end()) {

                documentScores[docName] = { 0,0 };
            }
            documentScores[docName].first = occurences;
        }
    }

    auto it2 = wordMap.find(word2);

    if (it2 != wordMap.end()) {

        for (const auto& doc : it2->second.documentPositions) {

            string docName = doc.first;
            int occurrences = doc.second.size();

            if (documentScores.find(docName) == documentScores.end()) {
                documentScores[docName] = { 0, 0 }; 
            }
            documentScores[docName].second = occurrences; 
        }
    }

    vector<pair<string, int>> documents;

    for (const auto& doc : documentScores) {

        if (doc.second.first > 0 && doc.second.second > 0) {

            //this doc contains both the words
            fs::path filePath(doc.first);
            string fileName = filePath.filename().string();

            int totalOccurences = doc.second.first + doc.second.second;

            pair<string, int> p = make_pair(fileName, totalOccurences);
            documents.push_back(p);
        }
    }

    if (documents.empty()) {
        gotoRowCol(13, 1);
        cout << red << "Sorry!! no documents with both words found:/";
        cout << reset;
        return;
    }

    sort(documents.begin(), documents.end(), compareDocuments);

    cout << reset;
    gotoRowCol(19,1);

    displayResultsAsPaginatedCards(documents);

   /* const int filenameWidth = 30;
    const int occurrenceWidth = 10;
    cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';

    cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';

    for (const auto& doc : documents) {
        cout << green;
        cout << left << setw(filenameWidth) << doc.first
            << " | "
            << setw(occurrenceWidth) << doc.second << '\n';

        cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';
    }
    cout << reset;*/

   
}
void queryMultipleWordsPlus(const vector<string>& words, const unordered_map<string, WordInDocument>& wordMap) {

    unordered_map<string, vector<int>> documentScores;   //documentName ---> occurences of each word ( mapping )

    for (int i = 0; i < words.size(); i++) {

        string word = words[i];

        auto it = wordMap.find(word);

        if (it == wordMap.end()) {

            gotoRowCol(13, 1);
            cout << "Sorry!! No documents with all these words found :/";
            return;
        }

        //now for the word extracted find the docs where the word exists

        for (const auto& doc : it->second.documentPositions) {

            string docName = doc.first;
            int occurences = doc.second.size();

            if (documentScores.find(docName) == documentScores.end()) {  //doc not found

                documentScores[docName] = vector<int>(words.size(), 0);
            }

            //now update the extracted word occurrences in the document's score vector
            documentScores[docName][i] = occurences;                    //update the occurences
        }
    }

    //filter the docs now that contain all the words

    vector<pair<string, int>> filteredDocs;

    for (const auto& doc : documentScores) {

        bool containsAll = true;
        int totalOccurences = 0;

        for (int count : doc.second) {

            if (count == 0) {
                containsAll = false;
                break;
            }
            totalOccurences += count;
        }

        if (containsAll) {
            fs::path filePath(doc.first);
            string fileName = filePath.filename().string();
            pair<string, int> p = make_pair(fileName, totalOccurences);
            filteredDocs.push_back(p);
        }
    }

    if (filteredDocs.empty()) {
        gotoRowCol(13, 1);
        cout << "Sorry!! No documents with all these words found :/";
        return;
    }

    sort(filteredDocs.begin(), filteredDocs.end(), compareDocuments);

    const int filenameWidth = 30;
    const int occurrenceWidth = 10;

    cout << reset;
    gotoRowCol(19,1);
   /* cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';
    cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';

    for (const auto& doc : filteredDocs) {
        cout << left << setw(filenameWidth) << doc.first
            << " | "
            << setw(occurrenceWidth) << doc.second << '\n';
        cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';
    }*/

    displayResultsAsPaginatedCards(filteredDocs);
}

//sentence based searches
void querySentence(const string& sentence, unordered_map<string, WordInDocument>& wordMap) {

    unordered_map<string, vector<int>> matchedDocs;     //document name --> position where the sentence starts

    for (unordered_map<string, WordInDocument>::iterator it = wordMap.begin(); it != wordMap.end(); it++) {

        string word = it->first;
        WordInDocument wordData = it->second;


        //now for each docment traverse and find which doc has the first word of the sentence and if any does process more to find the complete sentence
        for (unordered_map<string, vector<int>>::iterator docIt = wordData.documentPositions.begin(); docIt != wordData.documentPositions.end(); docIt++) {

            string docName = docIt->first;
            vector<int> positions = docIt->second;

            stringstream ss(sentence);
            vector<string> wordsFromSentence;
            string temp;

            while (ss >> temp) {
                wordsFromSentence.push_back(temp); //get all the words from the sentence
            }

            if (word != wordsFromSentence[0]) { //skip those which dont have the first word of the sentence as we need the complete sentence if it exits
                continue;
            }

            //now check if all words exits if they does the required doc found

            for (int i = 0; i < positions.size(); i++) {
                int startPos = positions[i];
                bool isMatch = true;
                int currentPos = startPos;

                for (int j = 1; j < wordsFromSentence.size(); j++) {
                    string nextWord = wordsFromSentence[j];

                    if (wordMap.find(nextWord) == wordMap.end() ||
                        wordMap.at(nextWord).documentPositions.find(docName) == wordMap.at(nextWord).documentPositions.end()) {
                        isMatch = false;
                        break;
                    }
                }

                if (isMatch) {
                    matchedDocs[docName].push_back(startPos);
                }
            }
        }
    }

    if (matchedDocs.empty()) {
        gotoRowCol(13, 1);
        cout << "Sorry!! No documents with the sentence found:/";
        return;
    }

    gotoRowCol(20, 1);
    cout << green <<"Documents containing the sentence: " << blue <<"'"<<sentence << "'" << endl;

    for (unordered_map<string, vector<int>>::const_iterator matchIt = matchedDocs.begin(); matchIt != matchedDocs.end(); ++matchIt) {
        string docName = matchIt->first;
        vector<int> positions = matchIt->second;
        fs::path filePath(docName);
        string fileName = filePath.filename().string();

        cout <<green<<"Document: " << fileName << "\n"<<reset;

       /* for (int i = 0; i < positions.size(); i++) {
            cout << "(" << positions[i] << ")";
        }
        cout << "\n";*/
    }
}

//the "-" based functions
void queryTwoWordsMinus(const string& word1, const string& word2, unordered_map<string, WordInDocument>& wordMap) {

    unordered_map<string, int> documentScores;  //documentName --> occurence of W1

    bool f1 = true, f2 = true;

    auto it = wordMap.find(word1);

    if (it == wordMap.end()) {
        f1 = false;
    }

    it = wordMap.find(word2);

    if (it == wordMap.end()) {
        f2 = false;
    }

    if (!f1) {
        gotoRowCol(13, 1);
        cout << "Sorry!! no documents with both words found:/";
        return;
    }

    it = wordMap.find(word1);

    if (it != wordMap.end()) {

        for (const auto doc : it->second.documentPositions) {

            string docName = doc.first;
            int occurences = doc.second.size();

            //now create mapping 
            documentScores[docName] = occurences;
        }
    }

    //now we simply have to remove those docs that contain W2 in addition to W1
    it = wordMap.find(word2);

    if (it != wordMap.end()) {

        for (const auto doc : it->second.documentPositions) {

            string docName = doc.first;

            if (documentScores.find(docName) != documentScores.end()) {  //meaning this doc contains W2

                //dont include this doc
                documentScores.erase(docName);
            }
        }
    }

    //push to the vector and sort it
    vector<pair<string, int>> documents;

    for (const auto& doc : documentScores) {
        fs::path filePath(doc.first);
        string fileName = filePath.filename().string();
        int occurences = doc.second;

        pair<string, int> p = make_pair(fileName, occurences);
        documents.push_back(p);
    }

    sort(documents.begin(), documents.end(), compareDocuments);

    if (documents.empty()) {
        gotoRowCol(13, 1);
        cout << red << "Sorry!! no documents with both words found:/";
        cout << reset;
        return;
    }
    //printing stuff

    cout << reset;
    gotoRowCol(19, 1);

    /*const int filenameWidth = 30;
    const int occurrenceWidth = 10;
    cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';

    cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';

    for (const auto& doc : documents) {
        cout << green;
        cout << left << setw(filenameWidth) << doc.first
            << " | "
            << setw(occurrenceWidth) << doc.second << '\n';

        cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';
    }
    cout << reset;*/

    displayResultsAsPaginatedCards(documents);
}
void queryWithExclusions(const string& word1, const string& word2, unordered_map<string, WordInDocument>& wordMap) {

    if (word1.empty() || word2.empty()) {
        gotoRowCol(13, 1);
        cout << red << "Invalid query: words cannot be empty.\n" << reset;
        return;
    }

    vector<string> word2Variations;
    word2Variations.push_back(word2);

    vector<string> suffixes = { ".", "!", "?", ",", "..", ",,", "!!", "??" };
    for (const string& suffix : suffixes) {
        word2Variations.push_back(word2 + suffix);
    }

    for (int i = 0; i < 26; i++) {
        char c = 'a' + i;
        word2Variations.push_back(word2 + c);
    }
    for (int i = 0; i < 10; i++) {
        char digit = '0' + i;
        word2Variations.push_back(word2 + digit);
    }
    for (const string& prefix : suffixes) {
        word2Variations.push_back(prefix + word2);
    }
    for (int i = 0; i < 26; i++) {
        char c = 'a' + i;
        word2Variations.push_back(c + word2);
    }
    for (int i = 0; i < 10; i++) {
        char digit = '0' + i;
        word2Variations.push_back(digit + word2);
    }

    unordered_map<string, int> documentScores;  // documentName --> occurrence of word1

    auto it = wordMap.find(word1);
    if (it != wordMap.end()) {
        for (const auto& doc : it->second.documentPositions) {
            string docName = doc.first;
            int occurrences = doc.second.size();
            documentScores[docName] = occurrences; // map document to occurrences of word1
        }
    }

    for (const string& variation : word2Variations) {
        auto variationIt = wordMap.find(variation);
        if (variationIt != wordMap.end()) {
            for (const auto& doc : variationIt->second.documentPositions) {
                string docName = doc.first;
                documentScores.erase(docName); // Remove documents containing variation
            }
        }
    }
    if (documentScores.empty()) {
        gotoRowCol(13, 1);
        cout << red << "No documents found containing \"" << word1
            << "\" but not \"" << word2 << "\" or its variations.\n" << reset;
        return;
    }

    gotoRowCol(19, 1);

    const int filenameWidth = 30;
    const int occurrenceWidth = 10;

    cout << reset;
    cout << left << setw(filenameWidth) << "Filename"
        << " | "
        << setw(occurrenceWidth) << "Occurrences" << '\n';
    cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';

    for (const auto& doc : documentScores) {
        fs::path filePath(doc.first);
        string fileName = filePath.filename().string();
        int occurrences = doc.second;

        cout << green;
        cout << left << setw(filenameWidth) << fileName
            << " | "
            << setw(occurrenceWidth) << occurrences << '\n';
        cout << string(filenameWidth + occurrenceWidth + 3, '-') << '\n';
    }
    cout << reset;
}

void findMatchingDocs(const string& sentence, unordered_map<string, vector<int>>& matchedDocs, unordered_map<string, WordInDocument>& wordMap) {

    //traverse the entire wordMap
    for (unordered_map<string, WordInDocument>::iterator globalIT = wordMap.begin(); globalIT != wordMap.end(); globalIT++) {

        string word = globalIT->first;
        WordInDocument wordData = globalIT->second;

        //now for each word we need to traverse the document and check if which doc contains the first word of the input sentence

        for (unordered_map<string, vector<int>>::iterator docIT = wordData.documentPositions.begin(); docIT != wordData.documentPositions.end(); docIT++) {

            string docName = docIT->first;
            vector<int> positions = docIT->second;

            stringstream ss(sentence);
            vector<string> wordsFromSentence;
            string temp;

            while (ss >> temp) {
                wordsFromSentence.push_back(temp);
            }

            //skip the docs which donot contain the first word of the input sentence

            if (word != wordsFromSentence[0]) {
                continue;
            }

            //now check if the entire sentence exists or not
            for (int i = 0; i < positions.size(); i++) {
                int startPos = positions[i];
                bool isMatch = true;
                int currentPos = startPos;

                for (int j = 1; j < wordsFromSentence.size(); j++) {
                    string nextWord = wordsFromSentence[j];


                    if (wordMap.find(nextWord) == wordMap.end() ||
                        wordMap.at(nextWord).documentPositions.find(docName) == wordMap.at(nextWord).documentPositions.end()) {
                        isMatch = false;
                        break;
                    }
                }
                if (isMatch) {
                    matchedDocs[docName].push_back(startPos);
                }
            }
        }
    }
}
void querySentenceMinus(const string& sentence1, const string& sentence2, unordered_map<string, WordInDocument>& wordMap) {
    unordered_map<string, vector<int>> matchedDocs1;
    unordered_map<string, vector<int>> matchedDocs2;

    findMatchingDocs(sentence1, matchedDocs1, wordMap);
    findMatchingDocs(sentence2, matchedDocs2, wordMap);

    // now simply remove the documents with sentence 2 in the results of sentence 1
    for (unordered_map<string, vector<int>>::iterator it = matchedDocs2.begin(); it != matchedDocs2.end(); ++it) {
        string docName = it->first;
        matchedDocs1.erase(docName);
    }

    if (matchedDocs1.empty()) {
        gotoRowCol(13, 1);
        cout << red << "No documents found containing \"" << sentence1
            << "\" but not \"" << sentence2 << "\".\n" << reset;
        return;
    }

    gotoRowCol(20, 1);
    cout << green << "Documents containing \"" << sentence1
        << "\" but not \"" << sentence2 << "\":\n" << reset;

    for (unordered_map<string, vector<int>>::iterator it = matchedDocs1.begin(); it != matchedDocs1.end(); ++it) {
        string docName = it->first;
        vector<int> positions = it->second;

        fs::path filePath(docName);
        string fileName = filePath.filename().string();

        cout << green << "Document: " << fileName << "\n" << reset;
    }
}

using namespace std;

//driver function
int main() {
    string folderPath = "C:\\DSA-SEM-3\\Search Engine Final Project\\review_text";
    string dumpFile = "dump.txt";
    unordered_map<string, WordInDocument> wordMap;
    char ch;
    int maxFiles = 1000;

    if (!fs::exists(dumpFile)) {
        crawlAndDump(folderPath, dumpFile);
    }

    vector<string> fileNames = loadDump(dumpFile);
    int fileCount = 0;

    auto startFileProcessing = high_resolution_clock::now();

    cout << "Processing files...\n";
    for (const string& filePath : fileNames) {
        processFile(filePath, wordMap);
        fileCount++;
        if (fileCount >= maxFiles) {
            break;
        }
    }

    auto endFileProcessing = high_resolution_clock::now();
    auto fileProcessingDuration = duration_cast<milliseconds>(endFileProcessing - startFileProcessing).count();

    system("cls");
    gotoRowCol(1, 1);
    cout << "File processing time: " << fileProcessingDuration << " ms" << endl;

    bool run = true;
    long long totalQueryTime = 0;
    int queryCount = 0;

    while (run) {
        logoMain(fileProcessingDuration, (queryCount > 0 ? totalQueryTime / queryCount : -1), totalQueryTime, queryCount);

        string input;
        searchBarInput(input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        ch = _getch();

        if (input == "exit") {
            system("cls");
            int centerRow = 25;
            int centerCol = 85;
            gotoRowCol(centerRow, centerCol);
            cout << green << "Thank you for surfing our browser!";
            gotoRowCol(centerRow + 1, centerCol);
            cout << "We hope to see you again soon. :)";

            gotoRowCol(centerRow + 5, centerCol);
            cout << "Summary of Execution Times:\n";
            gotoRowCol(centerRow + 6, centerCol);
            cout << "-----------------------------------\n";
            gotoRowCol(centerRow + 7, centerCol);
            cout << "File Processing Time: " << fileProcessingDuration << " ms\n";
            gotoRowCol(centerRow + 8, centerCol);
            cout << "Total Query Execution Time: " << totalQueryTime << " ms\n";
            if (queryCount > 0) {
                double averageQueryTime = static_cast<double>(totalQueryTime) / queryCount;
                gotoRowCol(centerRow + 9, centerCol);
                cout << "Average Query Execution Time: " << fixed << setprecision(2) << averageQueryTime << " ms\n";
            }
            else {
                gotoRowCol(centerRow + 5, centerCol);
                cout << "No queries executed.\n";
            }
            gotoRowCol(centerRow + 10, centerCol);
            cout << "-----------------------------------\n";

            _getch();
            exit(0);
        }

        bool validClick = false;
        while (!validClick) {
            int r, c;
            getRowColbyLeftClick(r, c);

            if (isClickInRange(r, c, 17, 100, 3) || ch == 'r') {
                validClick = true;

                auto startQuery = high_resolution_clock::now();

                if (input.find("-\"") != string::npos && input.front() == '"' && input.back() == '"') {
                    int minusPos = input.find("-\"");
                    string sentence1 = input.substr(1, minusPos - 2);
                    string sentence2 = input.substr(minusPos + 2, input.size() - minusPos - 3);
                    querySentenceMinus(sentence1, sentence2, wordMap);
                }
                else if (input.front() == '"' && input.back() == '"') {
                    string sentence = input.substr(1, input.size() - 2);
                    querySentence(sentence, wordMap);
                }
                else if (input.find('+') != string::npos) {
                    vector<string> words = parseInput(input);
                    if (words.size() == 2) {
                        queryTwoWordsPlus(words[0], words[1], wordMap);
                    }
                    else if (words.size() > 2) {
                        queryMultipleWordsPlus(words, wordMap);
                    }
                    else {
                        gotoRowCol(13, 1);
                        cout << "Please enter valid words separated by '+'!";
                    }
                }
                else if (input.find('-') != string::npos) {
                    vector<string> words = parseInputMinus(input);
                    if (words.size() == 2) {
                        queryWithExclusions(words[0], words[1], wordMap);
                    }
                }
                else {
                    vector<string> words;
                    stringstream ss(input);
                    string word;
                    while (ss >> word) {
                        words.push_back(word);
                    }

                    if (words.size() == 1) {
                        queryWord(words[0], wordMap);
                    }
                    else if (words.size() == 2) {
                        queryTwoWords(words[0], words[1], wordMap);
                    }
                    else if (word.size() > 2) {
                        queryMultipleWords(words, wordMap);
                    }
                    else {
                        gotoRowCol(13, 1);
                        cout << "Please enter up to two words only!";
                    }
                }

                auto endQuery = high_resolution_clock::now();
                auto queryDuration = duration_cast<milliseconds>(endQuery - startQuery).count();
                totalQueryTime += queryDuration;
                queryCount++;
            }
        }

        _getch();
        system("cls");
    }

    return 0;
}
int main1() {
    unordered_map<string, WordInDocument> wordMap;
    string folderPath = "C:\\DSA-SEM-3\\Search Engine Final Project\\review_text";

    const int maxFiles = 1000;
    int fileCount = 0;

    cout << "Processing files...\n";

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string filePath = entry.path().string();
            processFile(filePath, wordMap);
            fileCount++;
            if (fileCount >= maxFiles) {
                break;
            }
        }
    }
    cout << "\nProcessed " << fileCount << " files successfully!\n";
    system("cls");

    string word1, word2;
    cout << "Enter the number of words to search (1 or 2): \n";
    int numWords;
    cin >> numWords;

    if (numWords == 1) {
        cout << "Enter the word to search: \n";
        cin >> word1;
        queryWord(word1, wordMap);  // Call the function for a single word
    }
    else if (numWords == 2) {
        cout << "Enter the two words to search: \n";
        cin >> word1 >> word2;
        queryTwoWords(word1, word2, wordMap);  // Call the function for two words
    }
    else {
        cout << "Invalid input! Please enter 1 or 2 for the number of words.\n";
    }

    return 0;
}
int main2() {
    unordered_map<string, WordInDocument> wordMap;
    const string folderPath = "C:\\search-engine\\Project1\\Project1\\2";

    const int maxFiles = 100;
    int fileCount = 0;
    char ch;
    cout << "Processing files...\n";

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string filePath = entry.path().string();
            processFile(filePath, wordMap);
            fileCount++;
            if (fileCount >= maxFiles) {
                break;
            }
        }
    }
    system("cls");

    while (true) {
        logoMain();

        string input;
        searchBarInput(input);
        ch = _getch();

        if (input.find('+') != string::npos) {
            vector<string> words = parseInput(input);

            int r, c;
            getRowColbyLeftClick(r, c);

            if (isClickInRange(r, c, 13, 130, 3) || ch == 'r') {
                if (words.size() == 2) {
                    queryTwoWordsPlus(words[0], words[1], wordMap);
                }
                else if (words.size() > 2) {
                    queryMultipleWordsPlus(words, wordMap);
                }
                else {
                    gotoRowCol(13, 1);
                    cout << "Please enter valid words separated by '+'.";
                }
            }
        }
        else {

            vector<string> words;
            stringstream ss(input);
            string word;
            while (ss >> word) {
                words.push_back(word);
            }

            gotoRowCol(20, 10);
            cout << string(100, ' ');

            int r, c;
            getRowColbyLeftClick(r, c);
            if (isClickInRange(r, c, 13, 130, 3) || ch == 'r') {
                if (words.size() == 1) {
                    queryWord(words[0], wordMap);
                }
                else if (words.size() == 2) {
                    queryTwoWords(words[0], words[1], wordMap);
                }
                else if (word.size() > 2) {
                    queryMultipleWords(words, wordMap);
                }
                else {
                    gotoRowCol(13, 1);
                    cout << "Please enter up to two words only.";
                }
            }
        }
        _getch();
        system("cls");
    }

    return 0;
}

//algo for poppulating the map
//extract the word from the file 
//check whether the word exists in the map if it does than simply update the position 
//if it does not exits than create a new mapping of that word with a wordclass instance ( based on filename and position/index of that word )

//algo for processing word 
//for each word in the input bar 
//check whether the word exits or not
//if it exists than traverse the documents ( docPositions )
//for each doc extract the doc name and occurences
//if doc name not found with corresponding to that word than init the score  0 0
//if docname found with corresponding word than simply update the scores 

//fix the ui of the search engine to see off the delay ( check )
//keep on asking for mouse clicks until correct mouse click key activated  ( check )
//add a timer after user searches till the results appear ( compare the trie based with hashmaps based )