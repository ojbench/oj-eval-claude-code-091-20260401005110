#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class ESet {
private:
    map<long long, set<long long>> sets;
    long long nextId = 0;

public:
    // Create a new empty set and return its ID
    long long create() {
        sets[nextId] = set<long long>();
        return nextId++;
    }

    // Insert an element into a set
    void insert(long long setId, long long value) {
        if (sets.find(setId) != sets.end()) {
            sets[setId].insert(value);
        }
    }

    // Remove an element from a set
    void erase(long long setId, long long value) {
        if (sets.find(setId) != sets.end()) {
            sets[setId].erase(value);
        }
    }

    // Check if an element exists in a set
    bool contains(long long setId, long long value) {
        if (sets.find(setId) != sets.end()) {
            return sets[setId].find(value) != sets[setId].end();
        }
        return false;
    }

    // Get the size of a set
    long long size(long long setId) {
        if (sets.find(setId) != sets.end()) {
            return sets[setId].size();
        }
        return 0;
    }

    // Union of two sets into a new set
    long long unionSets(long long setId1, long long setId2) {
        long long newId = create();
        if (sets.find(setId1) != sets.end() && sets.find(setId2) != sets.end()) {
            sets[newId] = sets[setId1];
            for (auto val : sets[setId2]) {
                sets[newId].insert(val);
            }
        }
        return newId;
    }

    // Intersection of two sets into a new set
    long long intersectSets(long long setId1, long long setId2) {
        long long newId = create();
        if (sets.find(setId1) != sets.end() && sets.find(setId2) != sets.end()) {
            set_intersection(sets[setId1].begin(), sets[setId1].end(),
                           sets[setId2].begin(), sets[setId2].end(),
                           inserter(sets[newId], sets[newId].begin()));
        }
        return newId;
    }

    // Difference of two sets (setId1 - setId2)
    long long differenceSets(long long setId1, long long setId2) {
        long long newId = create();
        if (sets.find(setId1) != sets.end() && sets.find(setId2) != sets.end()) {
            set_difference(sets[setId1].begin(), sets[setId1].end(),
                         sets[setId2].begin(), sets[setId2].end(),
                         inserter(sets[newId], sets[newId].begin()));
        }
        return newId;
    }

    // Delete a set
    void deleteSet(long long setId) {
        sets.erase(setId);
    }

    // Get minimum element
    long long getMin(long long setId) {
        if (sets.find(setId) != sets.end() && !sets[setId].empty()) {
            return *sets[setId].begin();
        }
        return -1;
    }

    // Get maximum element
    long long getMax(long long setId) {
        if (sets.find(setId) != sets.end() && !sets[setId].empty()) {
            return *sets[setId].rbegin();
        }
        return -1;
    }

    // Print set elements
    void printSet(long long setId) {
        if (sets.find(setId) != sets.end()) {
            bool first = true;
            for (auto val : sets[setId]) {
                if (!first) cout << " ";
                cout << val;
                first = false;
            }
            cout << "\n";
        } else {
            cout << "\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ESet eset;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "CREATE") {
            cout << eset.create() << "\n";
        }
        else if (cmd == "INSERT") {
            long long setId, value;
            iss >> setId >> value;
            eset.insert(setId, value);
        }
        else if (cmd == "ERASE") {
            long long setId, value;
            iss >> setId >> value;
            eset.erase(setId, value);
        }
        else if (cmd == "CONTAINS") {
            long long setId, value;
            iss >> setId >> value;
            cout << (eset.contains(setId, value) ? "YES" : "NO") << "\n";
        }
        else if (cmd == "SIZE") {
            long long setId;
            iss >> setId;
            cout << eset.size(setId) << "\n";
        }
        else if (cmd == "UNION") {
            long long setId1, setId2;
            iss >> setId1 >> setId2;
            cout << eset.unionSets(setId1, setId2) << "\n";
        }
        else if (cmd == "INTERSECT") {
            long long setId1, setId2;
            iss >> setId1 >> setId2;
            cout << eset.intersectSets(setId1, setId2) << "\n";
        }
        else if (cmd == "DIFFERENCE") {
            long long setId1, setId2;
            iss >> setId1 >> setId2;
            cout << eset.differenceSets(setId1, setId2) << "\n";
        }
        else if (cmd == "DELETE") {
            long long setId;
            iss >> setId;
            eset.deleteSet(setId);
        }
        else if (cmd == "MIN") {
            long long setId;
            iss >> setId;
            cout << eset.getMin(setId) << "\n";
        }
        else if (cmd == "MAX") {
            long long setId;
            iss >> setId;
            cout << eset.getMax(setId) << "\n";
        }
        else if (cmd == "PRINT") {
            long long setId;
            iss >> setId;
            eset.printSet(setId);
        }
    }

    return 0;
}
