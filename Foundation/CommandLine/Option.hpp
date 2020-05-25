#pragma once

#include <string>

class Option
{
public:

    explicit Option(std::string name);

    explicit Option(std::string name, bool required, bool defined);

    virtual ~Option() = default;

    virtual bool Parse(std::string value) = 0;

    virtual std::string Help() const = 0;

    const std::string& GetName() const;

    void SetDescription(std::string description);

    bool IsRequired() const;

    bool IsDefined() const;

protected:

    const std::string& GetDescription() const;

    void SetRequired(bool required);

    void SetDefined(bool defined);

private:

    std::string _name{};

    std::string _description{};

    bool _required{ false };

    bool _defined{ false };

};
