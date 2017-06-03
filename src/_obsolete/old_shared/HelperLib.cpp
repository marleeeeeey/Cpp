#include <HelperLib.h>
#include <thread>

bool isProbability(float p)
{
    enum 
    {
        min = 0,
        max = 100,
    };

    if (p < min || p > max)
        throw std::logic_error("HelperLib: isProbability p < 0 || p > 100");

    if (getRandom<float>(min, max) <= p)
        return true;

    return false;
}

std::string removeFromString(const std::string & sourse, std::string remString)
{
    std::size_t foundPos = sourse.find(remString);

    if (foundPos == std::string::npos)
        return sourse;

    std::string ret = sourse;
    ret.erase(foundPos, remString.length());
    return ret;
}

void thread_sleep(unsigned time_ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

template<>
std::string to_string(const bool& t)
{
    std::ostringstream os;

    if (t)
        os << "true";
    else
        os << "false";

    return os.str();
}
