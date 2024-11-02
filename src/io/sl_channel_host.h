#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <io/sl_generic_channel.h>
#include <sl_value_storage.h>

namespace Io {

class ChannelHost {
    public:
        enum Type {
            UDP,
        };

        ChannelHost(ValueStorage& storage): _storage(storage) {}
        ~ChannelHost();

        void startAll();
        void stopAll();
        void openAll();
        void closeAll();

        void configure(const std::string& name, GenericConfig *cfg);

        void setReadCb(const std::string& name, GenericChannel::Cb cb);

        void addChannel(const std::string& name, Type type);

    private:
        ValueStorage& _storage;
        std::unordered_map<std::string, GenericChannel *> _channels;
};

}