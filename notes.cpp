#include <bits/stdc++.h>
using namespace std;

struct Note {
    int id;
    string title;
    string content;
    string tags;
};

vector<Note> notes;
const string FILENAME = "notes.txt";
void loadNotes() {
    notes.clear();
    ifstream fin(FILENAME);
    if (!fin) return;

    Note n;
    while (fin >> n.id) {
        fin.ignore();
        getline(fin, n.title);
        getline(fin, n.content);
        getline(fin, n.tags);
        notes.push_back(n);
    }
    fin.close();
}
void saveNotes() {
    ofstream fout(FILENAME);
    for (auto &n : notes) {
        fout << n.id << "\n";
        fout << n.title << "\n";
        fout << n.content << "\n";
        fout << n.tags << "\n";   // NEW LINE
    }
    fout.close();
}

int getNextId() {
    int mx = 0;
    for (auto &n : notes) mx = max(mx, n.id);
    return mx + 1;
}
int findIndexById(int id) {
    for (int i = 0; i < (int)notes.size(); i++) {
        if (notes[i].id == id) return i;
    }
    return -1;
}
void createNote() {
    Note n;
    n.id = getNextId();

    cout << "Enter title: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, n.title);

    cout << "Enter content: ";
    getline(cin, n.content);

    cout << "Enter tags (comma-separated): ";
getline(cin, n.tags);

    notes.push_back(n);
    saveNotes();
    cout << "Note added!\n";
}
void viewNotes() {
    if (notes.empty()) {
        cout << "No notes found.\n";
        return;
    }
    for (auto &n : notes) {
        cout << "\nID: " << n.id << "\nTitle: " << n.title << "\nContent: " << n.content << "\n";cout << "Tags: " << n.tags << "\n";
    }
}
void searchNotes() {
    cout << "Enter keyword: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string key;
    getline(cin, key);

    bool found = false;
    for (auto &n : notes) {
        if (n.title.find(key) != string::npos || n.content.find(key) != string::npos) {
            cout << "\nID: " << n.id << "\nTitle: " << n.title << "\nContent: " << n.content << "\n";
             n.tags.find(key) != string::npos;
        }
    }
    if (!found) cout << "No matching notes.\n";
}
void editNote() {
    cout << "Enter note ID to edit: ";
    int id;
    cin >> id;

    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "Note not found.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    Note &n = notes[idx];

    cout << "Current title: " << n.title << "\n";
    cout << "Enter new title (leave empty to keep): ";
    string newTitle;
    getline(cin, newTitle);
    if (!newTitle.empty()) n.title = newTitle;

    cout << "Current content: " << n.content << "\n";
    cout << "Enter new content (leave empty to keep): ";
    string newContent;
    getline(cin, newContent);
    if (!newContent.empty()) n.content = newContent;
    cout << "Current tags: " << n.tags << "\n";
    cout << "Enter new tags (leave empty to keep): ";
   string newTags;
    getline(cin, newTags);
if (!newTags.empty()) n.tags = newTags;

    saveNotes();
    cout << "Note updated.\n";
}
void deleteNote() {
    cout << "Enter note ID to delete: ";
    int id;
    cin >> id;

    for (int i = 0; i < notes.size(); i++) {
        if (notes[i].id == id) {
            notes.erase(notes.begin() + i);
            saveNotes();
            cout << "Note deleted!\n";
            return;
        }
    }
    cout << "Note not found.\n";
}

int main() {
    loadNotes();
    int choice;

    while (true) {
        cout << "\n=== Personal Knowledge Vault ===\n";
        cout << "1. Create Note\n2. View Notes\n3. Search Notes\n4. Edit Note\n5. Delete Note\n6. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: createNote(); break;
            case 2: viewNotes(); break;
            case 3: searchNotes(); break;
            case 4: editNote(); break;
            case 5: deleteNote(); break;
            case 6: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid option.\n";
        }
    }
}
