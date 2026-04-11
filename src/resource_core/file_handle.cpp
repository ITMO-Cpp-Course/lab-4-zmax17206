#include "resource_core/file_handle.hpp"

#include <utility>

namespace lab4::resource
{

FileHandle::FileHandle(const std::string& path, const std::string& mode)
    : file_(std::fopen(path.c_str(), mode.c_str())), path_(path)
{
    if (!file_)
    {
        throw ResourceError("Failed to open file: " + path);
    }
}

FileHandle::~FileHandle()
{
    close();
}

FileHandle::FileHandle(FileHandle&& other) noexcept : file_(other.file_), path_(std::move(other.path_))
{
    other.file_ = nullptr;
}

FileHandle& FileHandle::operator=(FileHandle&& other) noexcept
{
    if (this != &other)
    {
        close();
        file_ = other.file_;
        path_ = std::move(other.path_);
        other.file_ = nullptr;
    }
    return *this;
}

bool FileHandle::is_open() const noexcept
{
    return file_ != nullptr;
}

const std::string& FileHandle::path() const noexcept
{
    return path_;
}

void FileHandle::close() noexcept
{
    if (file_)
    {
        std::fclose(file_);
        file_ = nullptr;
    }
}

} // namespace lab4::resource
