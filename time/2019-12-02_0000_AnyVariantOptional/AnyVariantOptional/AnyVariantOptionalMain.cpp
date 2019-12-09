#include <string>
#include <system_error>
#include <variant>
#include <charconv>
#include <iostream>

std::variant<int, float, std::string> TryParseString(std::string_view sv)
{
    // try with float first
    float fResult = 0.0f;
    const auto last = sv.data() + sv.size();
    const auto res = std::from_chars(sv.data(), last, fResult);
    if (res.ec != std::errc{} || res.ptr != last)
    {
        // if not possible, then just assume it's a string
        return std::string{sv};
    }
    // no fraction part? then just cast to integer
    if (static_cast<int>(fResult) == fResult)
        return static_cast<int>(fResult);
    return fResult;
}

void checkVariant()
{
    const auto var = TryParseString("12345.98");
    try {
        if(std::holds_alternative<int>(var))
            std::cout << "parsed as int: " << std::get<int>(var) << '\n';
        else if(std::holds_alternative<float>(var))
            std::cout << "parsed as float: " << std::get<float>(var) << '\n';
        else if(std::holds_alternative<std::string>(var))
            std::cout << "parsed as string: " << std::get<std::string>(var) << '\n';
    }
    catch(std::bad_variant_access&) {
        std::cout << "bad variant access...\n";
    }    
}

int main()
{
    
}