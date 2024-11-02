#pragma once

#include "sl_generic_channel.h"

namespace Io {

struct UdpConfig: GenericConfig {
    uint16_t port;
    std::string bindAddr;

    static const uint8_t TYPE = 1;
};

class UdpChannel: public GenericChannel {
    public:
        UdpChannel(ValueStorage& storage): GenericChannel(storage) {}
        virtual ~UdpChannel() {}

        void configure(const GenericConfig *cfg) override;
        
        bool open() override;
        bool close() override;

    protected:
        int _socket;
        uint16_t _port;
        std::string _bindAddr;

        bool getData(std::vector<uint8_t>& data) override;
};

}