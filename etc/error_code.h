class error_code
{
private:
    const char *error_type;

public:
    error_code(const char *errorType)
    {
        error_type = errorType;
    };
    const char *What() const
    {
        return error_type;
    }
    ~error_code(){};
};
