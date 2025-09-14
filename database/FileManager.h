#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager {
public:
    FileManager();
    
    bool initializeDataDirectory();
    bool createDataFile(const std::string& filename);
    bool fileExists(const std::string& filename);
    std::string getDataDirectory();
    
private:
    std::string dataDirectory;
    bool createDirectory(const std::string& path);
};

#endif // FILEMANAGER_H
