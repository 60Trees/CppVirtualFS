#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class vfs {
public:
    class Path {
    public:
        Path() = default;
        Path(const std::string& p);
        Path(const char* p);

        Path operator/(const std::string& rhs) const;
        Path operator/(const char* rhs) const;

        std::string string() const;
        const std::string& str() const;

        bool empty() const;

        bool operator==(const Path& other) const;

        struct Hash {
            size_t operator()(const Path& p) const;
        };

        bool isFile(const vfs* fs) const;
        bool isDir(const vfs* fs) const;

        bool isExisting(const vfs* fs) const {
            return isFile(fs) || isDir(fs);
        }

        std::vector<std::string> getSegments() const;

        static Path fromSegments(const std::vector<std::string>& segs);

    private:
        std::string m_path;

        static std::string normalize(std::string p);

        friend class vfs;
    };

public:
    vfs() = default;

    void clear();

    void load_zip_or_dir(const std::filesystem::path& path);

    void temporarily_unload();
    void reload();

    std::vector<Path> ls(const Path& path) const;

    bool is_dir(const Path& path) const;
    bool is_file(const Path& path) const;

    size_t get_size(const Path& path) const;

    std::span<const uint8_t> get_file_contents(const Path& path) const;

    std::string_view get_file_str(const Path& path) const;

private:
    struct FileData {
        std::vector<uint8_t> bytes;
    };

    struct Source {
        std::filesystem::path path;
    };

private:
    void rebuild();

    void add_directory_source(const std::filesystem::path& dir);
    void add_zip_source(const std::filesystem::path& zip);

    void register_directory_tree(const Path& path);

private:
    std::vector<Source> m_sources;

    std::unordered_map<
        Path,
        std::shared_ptr<FileData>,
        Path::Hash
    > m_files;

    std::unordered_map<
        Path,
        std::unordered_set<Path, Path::Hash>,
        Path::Hash
    > m_directories;

    std::unordered_map<
        Path,
        size_t,
        Path::Hash
    > m_size_cache;
};
