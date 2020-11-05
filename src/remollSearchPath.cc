#include "remollSearchPath.hh"

remollSearchPath* remollSearchPath::fInstance = nullptr;

remollSearchPath::remollSearchPath()
{
    // add CMAKE_INSTALL_FULL_DATADIR, CMAKE_INSTALL_PREFIX and CWD to search path
    #ifndef NO_FS_SUPPORT
    fSearchPath.push_back(fs::path(get_current_dir_name()));
    fSearchPath.push_back(fs::path(CMAKE_INSTALL_PREFIX));
    fSearchPath.push_back(fs::path(CMAKE_INSTALL_FULL_DATADIR));
    #endif
}

remollSearchPath *remollSearchPath::getInstance() {
    if (!fInstance) {
        fInstance = new remollSearchPath();
    }
    return fInstance;
}

remollSearchPath::~remollSearchPath() {}

void remollSearchPath::add(const std::string& path)
{
#ifndef NO_FS_SUPPORT
    // If directory to search in is inside CMAKE_INSTALL_PREFIX
    if(fs::exists(fs::path(std::string(CMAKE_INSTALL_PREFIX) + "/" + path))) {
        fSearchPath.push_back(fs::path(std::string(CMAKE_INSTALL_PREFIX) + "/" + path));
    }
        // If directory to search in is inside CMAKE_INSTALL_FULL_DATADIR
    else if(fs::exists(fs::path(std::string(CMAKE_INSTALL_FULL_DATADIR) + "/" + path))) {
        fSearchPath.push_back(fs::path(std::string(CMAKE_INSTALL_FULL_DATADIR) + "/" + path));
    }
        // If directory to search in is inside the current working directory
    else if(fs::exists(fs::path(get_current_dir_name()) / path)) {
        fSearchPath.push_back(fs::path(get_current_dir_name()) / path);
    }
        // Path not relative to CMAKE_INSTALL_PREFIX, CMAKE_INSTALL_FULL_DATADIR or CWD
        // path is probably an absolute path
    else if (fs::exists(fs::path(path))) {
        fSearchPath.push_back(fs::path(path));
    }
#endif
}

std::string remollSearchPath::operator() (const std::string& filename)
{
    // If the file you are looking for exists inside any of the
    // directories inside fSearchPath, return the filename prefixed with
    // the directory for which the full path exists
#ifndef NO_FS_SUPPORT
    for (auto path: fSearchPath) {
        if(fs::exists(path / filename)) {
            return (path / filename).string();
        }
    }
#endif

    // File not found in any of the search directories,
    // return the filename
    return std::string(filename); /* and pray everything work */
}