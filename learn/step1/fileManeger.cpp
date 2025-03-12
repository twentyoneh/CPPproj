#include<iostream>
#include<string>
#include<fstream>
#include<memory>

class FileManager
{
private:
    std::unique_ptr<FILE, decltype(&std::fclose)> m_file;
public:
    explicit FileManager(const std::string& fileName,const std::string& mode); // mode: r - чтение, w - запись
    size_t write(const char* buffer, size_t size);
    size_t read(char* buffer, size_t size);
    bool isOpen() const;
    explicit operator bool() const;
};



FileManager::FileManager(const std::string& fileName, const std::string& mode)
    : m_file{std::fopen(fileName.c_str(), mode.c_str()), &std::fclose}
{
    if(!m_file)
    {
        throw std::runtime_error("Failed to open file:" + fileName);
    }
}

size_t FileManager::read(char* buffer, size_t size) {
    if (!m_file) return 0;
    return std::fread(buffer, 1, size, m_file.get());
}

size_t FileManager::write(const char* buffer, size_t size) {
    if (!m_file) return 0;
    return std::fwrite(buffer, 1, size, m_file.get());
}

bool FileManager::isOpen() const {
    return m_file != nullptr;
}

FileManager::operator bool() const {
    return isOpen();
}


int main()
{
    try {
        FileManager file("test.txt", "w");
        const char* data = "Hello, File!";
        file.write(data, sizeof(data));
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}