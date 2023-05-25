class Singleton
{
public:
    Singleton(Singleton& other) = delete;
    void operator = (const Singleton &) = delete;
    static Singleton* GetInstance(const std::string& value)
    {
        if(singleton_== nullptr)
            singleton_ = new Singleton(value);
        return singleton_;
    }
    void SomeBusinessLogic()
    {
    }
    std::string value() const
    {
        return value_;
    }
private:
    static Singleton* singleton_;
    std::string value_;
    // Singleton(const std::string value) : value_(value)
    // {
    // }
    Singleton(const std::string value)
    {
        value_ = value;
    }
};
Singleton* Singleton::singleton_= nullptr;