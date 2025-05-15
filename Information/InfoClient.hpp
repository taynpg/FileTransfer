#ifndef INFOCLIENT_HPP
#define INFOCLIENT_HPP

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <string>

struct InfoClient {
    std::string id;
    std::string name;
    template <class Archive> void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(id), CEREAL_NVP(name));
    }
};

struct InfoClientVec {
    std::vector<InfoClient> vec;
    template <class Archive> void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(vec));
    }
};

#endif   // INFOCLIENT_HPP