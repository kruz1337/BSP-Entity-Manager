#pragma once
#include <filesystem>
#include <fstream>
#include <format>
#include <iostream>

using namespace std;

//Sample taken from https://github.com/bernhardmgruber/hlbsp/
class BSP {
private:
    enum LumpType {
        LUMP_ENTITIES = 0,
        HEADER_LUMPS = 15,
    };

    struct Lump {
        int32_t offset; ///< File offset to data
        int32_t length; ///< Length of data
    };

    struct Header {
        int32_t version;         ///< Version number, must be 30 for a valid HL BSP file
        Lump lump[HEADER_LUMPS]; ///< Stores the directory of lumps.
    } header{};

    filesystem::path BspPath;

public:
    enum UpdateMode {
        BY_KEY = 0,
        BY_VALUE
    };

    string EntityData;

    explicit BSP(const filesystem::path& inputPath);
    void SaveData(const filesystem::path& savePath = "");
    void ExportEntityData(const filesystem::path& exportPath = "");
    void ImportEntityData(const filesystem::path& importPath);
    int UpdateEntityData(const string& search, const string& update, UpdateMode updateMode);
    void UpdateEntityDataByConfig(const filesystem::path& configPath, UpdateMode type);
};