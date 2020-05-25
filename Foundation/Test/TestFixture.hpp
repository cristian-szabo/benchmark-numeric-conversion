#pragma once

class TestFixture
{
public:

    virtual ~TestFixture() = default;

    virtual void Setup();

    virtual void Teardown();

};
