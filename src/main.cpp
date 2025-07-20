#include "BSP.h"
#include "Utility.h"

int main(int argc, char** argv) {
    #ifdef _WIN32
        ENABLE_ANSI();
    #endif

    CREATE_ASCII();

    if (argc < 3 || argc > 7) {
        cerr << LIGHT_YELLOW"[*] Usage: " << argv[0] << " [path] [--config {configPath} | --entity {entityPath}] [--export {...} | --save {...}]" RESET << endl;
        return 1;
    }

    try {
        BSP bspObject(argv[1]);

        int argPos;
        if (argPos = Utils::getArgIndex(argv, "--config"); argPos != -1) {
            BSP::UpdateMode updateMode = (strcmp(argv[Utils::getArgIndex(argv, "--utype") + 1], "1") == 0) ? BSP::BY_VALUE : BSP::BY_KEY;
            bspObject.UpdateEntityDataByConfig(argv[argPos + 1], updateMode);
        } else if (argPos = Utils::getArgIndex(argv, "--entity"); argPos != -1) {
            bspObject.ImportEntityData(argv[argPos + 1]);
        }

        if (argPos = Utils::getArgIndex(argv, "--export"); argPos != -1) {
            bspObject.ExportEntityData(argv[argPos + 1] ? argv[argPos + 1] : "");
        }
        else if (argPos = Utils::getArgIndex(argv, "--save"); argPos != -1) {
            bspObject.SaveData(argv[argPos + 1] ? argv[argPos + 1] : "");
        }
    } catch (exception& err) {
        cerr << endl << LIGHT_RED"[-] " << err.what() << RESET << endl;
        return 1;
    }

    cout << endl << LIGHT_GREEN"[+] Process successfully finished!" RESET << endl;

    return 0;
}
