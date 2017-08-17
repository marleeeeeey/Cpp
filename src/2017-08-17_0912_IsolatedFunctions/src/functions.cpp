#include "functions.h"


int one()
{
    return 1;
}


template <typename BoolVecT>
BoolVecT unpack_str_to_bool_vec(const std::string& in)
{
    BoolVecT out(in.size() * 8);

    auto it = out.begin();
    for (auto& entry : in) {
        auto entry_bitset = static_cast<std::bitset<8>>(
            static_cast<unsigned long>(entry));
        for (size_t i = 0; i < 8; ++i) {
            (*(it++)) = entry_bitset[i];
        }
    }

    return out;
}

std::vector<bool> read_vector_bool_from_bin_file(std::string & file_name, size_t count_bit)
{
    std::ifstream ifs(file_name, std::ios_base::binary);
    if (!ifs.is_open())
        throw std::logic_error("ERROR: File '" + file_name
            + "' cannot open. In read_vector_bool_from_bin_file");

    ifs.seekg(0, ifs.end);
    auto length = static_cast<size_t>(ifs.tellg());
    ifs.seekg(0, ifs.beg);

    if (count_bit > length * 8)
        throw std::logic_error("ERROR: Too small file '" + file_name + "'"
            + " for countBit=" + std::to_string(count_bit)
            + ". In read_vector_bool_from_bin_file");

    std::string str;
    str.resize(length);
    ifs.read(const_cast<char *>(str.data()), length);
    ifs.close();

    auto codes = unpack_str_to_bool_vec<std::vector<bool>>(str);
    codes.resize(count_bit);

    return codes;
}