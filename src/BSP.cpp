#include "BSP.h"
#include "Utility.h"

BSP::BSP(const filesystem::path& inputPath) : BspPath(inputPath) {
    fstream file(inputPath, ios::in | ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Failed to open BSP file!");
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    if (header.version != 30) {
        throw runtime_error("Invalid BSP version (" + to_string(header.version) + ") instead of 30)");
    }

    int32_t bufferSize = header.lump[LumpType::LUMP_ENTITIES].length;
    EntityData.resize(bufferSize-1);

    file.seekg(header.lump[LumpType::LUMP_ENTITIES].offset, ios::beg);
    file.read(&EntityData[0], bufferSize);
    file.close();
}

void BSP::SaveData(const filesystem::path& savePath) {
    fstream saveFile;

    if (savePath.empty()) {
        saveFile.open(BspPath, ios::in | ios::out | ios::binary);
        if (!saveFile.is_open()) {
            throw runtime_error("Failed to open BSP file!");
        }
    }
    else {
        fstream defFile;

        defFile.open(BspPath, ios::in | ios::binary);
        if (!defFile.is_open()) {
            throw runtime_error("Failed to open BSP file!");
        }

        saveFile.open(savePath, ios::out | ios::binary);
        if (!saveFile.is_open()) {
            throw runtime_error("Failed to open save path!");
        }

        char buffer[1024];
        while (defFile.read(buffer, sizeof(buffer))) {
            saveFile.write(buffer, defFile.gcount());
        }
    }

    saveFile.seekp(header.lump[LumpType::LUMP_ENTITIES].offset, ios::beg);
    saveFile.write(EntityData.data(), EntityData.size());
    saveFile.close();
}

void BSP::ExportEntityData(const filesystem::path& exportPath) {
    filesystem::path relativePath = exportPath.empty() ? format("{}/{}.entity", BspPath.parent_path().empty() ? "." : BspPath.parent_path().string(), BspPath.stem().string()) : exportPath;

    fstream file(relativePath, ios::out | ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Failed to open config file!");
    }

    file.write(EntityData.data(), EntityData.size());
    file.close();
}

void BSP::ImportEntityData(const filesystem::path& importPath) {
    fstream file(importPath, ios::in | ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Failed to open config file!");
    }

    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    file.seekg(0, ios::end);

    file.read(EntityData.data(), fileSize);
    file.close();
}

int BSP::UpdateEntityData(const string& search, const string& update, UpdateMode updateMode) {
    int updateCount = 0;
    size_t lastPos = 0, linePos = 0, newLine = 0;

    while ((newLine = EntityData.find('\n', linePos)) != string::npos) {
        lastPos = linePos;
        string curLine = EntityData.substr(linePos, newLine - linePos);
        linePos = newLine + 1;

        size_t firstOp = curLine.find('"');
        size_t secOp = curLine.find('"', firstOp + 1);
        size_t thirdOp = curLine.find('"', secOp + 1);
        size_t fourthOp = curLine.find('"', thirdOp + 1);

        if (firstOp == string::npos ||
            secOp == string::npos ||
            thirdOp == string::npos ||
            fourthOp == string::npos) {
            continue;
        }

        string key = curLine.substr(firstOp + 1, secOp - 1);
        if (key.empty()) {
            throw runtime_error("Failed to allocate 'key' pointer!");
        }

        string value = curLine.substr(thirdOp + 1, fourthOp - thirdOp -1 );
        if (value.empty()) {
            throw runtime_error("Failed to allocate 'key' pointer!");
        }

        if (updateMode == BY_VALUE ? (search == value) : (search == key)) {
            curLine.replace(thirdOp + 1, value.size(), update);
            ++updateCount;
        }

        EntityData.replace(lastPos, newLine - lastPos, curLine);
    }

    return updateCount;
}

void BSP::UpdateEntityDataByConfig(const filesystem::path &configPath, UpdateMode updateMode) {
    fstream file(configPath, ios::in);
    if (!file.is_open()) {
        throw runtime_error("Failed to open config file!");
    }

    string curLine;
    while (getline(file, curLine)) {
        size_t equalOp = curLine.find('=');
        size_t firstOp = curLine.find('"');
        size_t secOp = curLine.find('"', firstOp + 1);
        size_t thirdOp = curLine.find('"', secOp + 1);
        size_t fourthOp = curLine.find('"', thirdOp + 1);

        if (equalOp == string::npos) {
            continue;
        }

        string key = firstOp == string::npos && secOp == string::npos ? curLine.substr(0, equalOp - 1) : curLine.substr(firstOp + 1, secOp - 1);
        if (key.empty()) {
            throw runtime_error("Failed to allocate 'key' pointer!");
        }

        string value = thirdOp == string::npos && fourthOp == string::npos ? curLine.substr(equalOp + 1, curLine.size()) : curLine.substr(thirdOp + 1, fourthOp - thirdOp -1 );
        if (value.empty()) {
            throw runtime_error("Failed to allocate 'value' pointer!");
        }

        Utils::trim(value);
        Utils::trim(key);

        if (UpdateEntityData(key, value, updateMode) > 0) {
            cout << LIGHT_YELLOW"[*] Update successful for '" << key << ": " << value << "'" RESET << endl;
        } else {
            cout << LIGHT_RED"[!] There is no update for '" << key << ": " << value << "'" RESET << endl;
        }
    }

    file.close();
}