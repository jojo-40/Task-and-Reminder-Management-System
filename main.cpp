#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Task {
protected:
    int id;
    string title;

public:
    Task(int i = 0, string t = "") {
        id = i;
        title = t;
    }

    virtual void show() {
        cout << "ID: " << id << " | Task: " << title << endl;
    }

    int getId() {
        return id;
    }

    string getTitle() {
        return title;
    }

    virtual string format() {
        return to_string(id) + "," + title;
    }

    virtual ~Task() {}
};


class Reminder : public Task {
    string time;

public:
    Reminder(int i = 0, string t = "", string tm = "") : Task(i, t) {
        time = tm;
    }

    void show() override {
        cout << "ID: " << id
             << " | Task: " << title
             << " | Time: " << time << endl;
    }

    string format() override {
        return to_string(id) + "," + title + "," + time;
    }
};

class FileManager {
public:
    friend void saveToFile(vector<Reminder> tasks);
    friend void loadFromFile(vector<Reminder> &tasks);
};

void saveToFile(vector<Reminder> tasks) {
    ofstream file("tasks.txt", ios::out); 

    for (auto &t : tasks) {
        file << t.format() << endl;
    }

    file.close();
    cout << "Data saved to file successfully!\n";
}

void loadFromFile(vector<Reminder> &tasks) {
    ifstream file("tasks.txt", ios::in);

    if (!file) {
        cout << "No file found, starting fresh...\n";
        return;
    }

    int id;
    string title, time;

    while (file >> id) {
        file.ignore();
        getline(file, title, ',');

        if (getline(file, time)) {
            tasks.push_back(Reminder(id, title, time));
        }
    }

    file.close();
}

int main() {
    vector<Reminder> tasks;
    int choice;

    loadFromFile(tasks);

    do {
        cout << "\n===== TASK MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. Show Tasks\n";
        cout << "3. Save to File\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, time;

            cout << "Enter ID: ";
            cin >> id;

            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);

            cout << "Enter Time: ";
            getline(cin, time);

            tasks.push_back(Reminder(id, title, time));
        }

        else if (choice == 2) {
            cout << "\n===== TASK LIST =====\n";
            for (auto &t : tasks) {
                t.show();
            }
        }

        else if (choice == 3) {
            saveToFile(tasks);
        }

    } while (choice != 4);

    saveToFile(tasks);

    cout << "Program exited. Goodbye!\n";
    return 0;
}