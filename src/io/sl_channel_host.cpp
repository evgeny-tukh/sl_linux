#include "sl_channel_host.h"
#include "sl_udp_channel.h"

namespace Io {

ChannelHost::~ChannelHost() {
    for (auto chn: _channels) {
        if (chn.second)
            delete chn.second;
    }
}

void ChannelHost::startAll() {
    for (auto chn: _channels)
        chn.second->start();
}

void ChannelHost::stopAll() {
    for (auto chn: _channels)
        chn.second->stop();
}

void ChannelHost::openAll() {
    for (auto chn: _channels)
        chn.second->open();
}

void ChannelHost::closeAll() {
    for (auto chn: _channels)
        chn.second->close();
}

void ChannelHost::configure(const std::string& name, GenericConfig *cfg) {
    auto channelPos = _channels.find(name);

    if (channelPos != _channels.end())
        channelPos->second->configure(cfg);
}

void ChannelHost::setReadCb(const std::string& name, GenericChannel::Cb cb) {
    auto channelPos = _channels.find(name);

    if (channelPos != _channels.end())
        channelPos->second->setReadCb(cb);
}

void ChannelHost::addChannel(const std::string& name, Type type) {
    GenericChannel *channel;

    switch (type) {
        case Type::UDP:
            _channels.emplace(std::pair<std::string, GenericChannel *>(name, new UdpChannel(_storage)));
            break;
    }
}

}