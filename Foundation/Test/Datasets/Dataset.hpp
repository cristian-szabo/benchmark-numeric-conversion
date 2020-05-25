#pragma once

#include <string>

class Dataset
{
public:

    Dataset() = default;

    explicit Dataset(std::string name);

    const std::string& GetName() const;

private:

    std::string _name{};

};
