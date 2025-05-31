#ifndef INFOCOMMUNICATE_HPP
#define INFOCOMMUNICATE_HPP

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cstdint>

constexpr int GBUFFER_SIZE = 256;
struct InfoCommunicate {
    std::string UUID;
    std::string data;
    uint8_t mark{};
    template <class Archive> void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(UUID), CEREAL_NVP(data), CEREAL_NVP(mark));
    }
};

#endif   // INFOCOMMUNICATE_HPP
