#include "DataSetReader.h" 

std::vector<float> DataSetReader::split_string(std::string stringValue, char delimiter)
{
    size_t pos_start = 0;
    size_t delim_len = 1;
    size_t pos_end;
    std::string token;
    std::vector<float> splitValues;
    while((pos_end = stringValue.find(delimiter, pos_start)) != std::string::npos) 
    {
        token = stringValue.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splitValues.push_back(std::stof(token));
    }
    splitValues.push_back(std::stof(stringValue.substr(pos_start)));
    return splitValues;
}

std::vector<float> DataSetReader::split_comma_separated_string(std::string stringValue)
{
    return split_string(stringValue, ',');
}
