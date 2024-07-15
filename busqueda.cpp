#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std; 

//Ejemplo de uso que ya testie: sr Film-Names.csv "OPEN"
void search_in_csv(const string &file_path, const string &search_term) {
    ifstream file(file_path);
    string line;
    while (getline(file, line)) {
        stringstream line_stream(line);
        string cell;
        if (getline(line_stream, cell, ',')) {
            if (cell.find(search_term) != string::npos) {
                cout << line << endl;
            }
        }
    }
    file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file_path> <search_term>" << endl;
        return 1;
    }

    string file_path = argv[1];
    string search_term = argv[2];

    search_in_csv(file_path, search_term);

    return 0;
}
