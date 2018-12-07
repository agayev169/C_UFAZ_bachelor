#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Message {
public:
    int index;
    string author;
    vector<string> tags;

    Message(int index, string author, vector<string> tags): 
        index(index), author(author), tags(tags) {}

    Message(string message, int index): index(index) {
        author = "";
        int i = 1;
        while (i < message.size() && message[i] != ':') {
            author += message[i++];
        }
        while (i < message.size()) {
            while (i < message.size() && message[i++] != '@') {}
            string tag = "";
            while (i < message.size() && message[i] != ' ') {
                tag += message[i++];
            }
            tags.push_back(tag);
        }
    }

    void print() {
        cout << "Message #" << index << ":" << endl;
        cout << "\tAuthor: " << author << endl;
        cout << "\tTags:" << endl;
        cout << "\t\t";
        for (size_t i = 0; i < tags.size(); i++) {
            cout << tags[i] << " ";
        }
        cout << endl;
    }
};

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    cin.ignore();
    vector<Message> messages;
    messages.reserve(n);
    // cin.clear();
    for (int i = 0; i < n; i++) {
        string msg;
        getline(cin, msg);
        messages[i] = Message(msg, i);
    }

    for (size_t i = 0; i < n; i++) {
        messages[i].print();
    }

    return 0;
}

