#pragma once

#include <map>
#include <string>
#include <memory>

#include <io/sl_generic_channel.h>

namespace Io {

class ChannelHost {
    public:
        enum Type {
            UDP,
        };

        ChannelHost() {}
        ~ChannelHost();

        void startAll();
        void stopAll();
        void openAll();
        void closeAll();

        void configure(const std::string& name, GenericConfig *cfg);

        void setReadCb(const std::string& name, GenericChannel::Cb cb);

        void addChannel(const std::string& name, Type type);

    private:
        std::map<std::string, GenericChannel *> _channels;
};

}