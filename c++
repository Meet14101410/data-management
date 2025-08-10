#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// A simple data structure to hold a record
struct Record {
    int id;
    std::string name;
    std::string data;
};

// A class to manage the data
class DataManager {
private:
    // Use an unordered_map for O(1) average-case time complexity for lookups
    std::unordered_map<int, std::shared_ptr<Record>> records;
    int nextId = 1;

public:
    // Create a new record
    void createRecord(const std::string& name, const std::string& data) {
        auto newRecord = std::make_shared<Record>();
        newRecord->id = nextId++;
        newRecord->name = name;
        newRecord->data = data;
        records[newRecord->id] = newRecord;
        std::cout << "Created record with ID: " << newRecord->id << std::endl;
    }

    // Read a record by its ID
    std::shared_ptr<Record> readRecord(int id) {
        auto it = records.find(id);
        if (it != records.end()) {
            return it->second;
        }
        return nullptr; // Record not found
    }

    // Update a record's data
    bool updateRecord(int id, const std::string& newData) {
        auto record = readRecord(id);
        if (record) {
            record->data = newData;
            std::cout << "Updated record with ID: " << id << std::endl;
            return true;
        }
        std::cout << "Record with ID " << id << " not found." << std::endl;
        return false;
    }

    // Delete a record
    bool deleteRecord(int id) {
        auto it = records.find(id);
        if (it != records.end()) {
            records.erase(it);
            std::cout << "Deleted record with ID: " << id << std::endl;
            return true;
        }
        std::cout << "Record with ID " << id << " not found." << std::endl;
        return false;
    }

    // List all records
    void listAllRecords() {
        std::cout << "\n--- All Records ---" << std::endl;
        for (const auto& pair : records) {
            std::cout << "ID: " << pair.second->id << ", Name: " << pair.second->name << ", Data: " << pair.second->data << std::endl;
        }
    }
};

int main() {
    DataManager manager;

    manager.createRecord("Item A", "First piece of data.");
    manager.createRecord("Item B", "Second piece of data.");

    manager.listAllRecords();

    // Read a specific record
    if (auto record = manager.readRecord(1)) {
        std::cout << "\nFound record with ID 1: " << record->name << std::endl;
    }

    // Update a record
    manager.updateRecord(2, "Updated second piece of data.");

    // Delete a record
    manager.deleteRecord(1);
    
    manager.listAllRecords();

    return 0;
}
