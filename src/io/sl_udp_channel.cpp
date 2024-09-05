#include "sl_udp_channel.h"

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <fcntl.h>

namespace Io {

void UdpChannel::configure(const GenericConfig *cfg) {
    const UdpConfig *config = static_cast<const UdpConfig *>(cfg);

    if (config && cfg->type == UdpConfig::TYPE) {
        _port = config->port;
        _bindAddr = config->bindAddr;
    }
}
        
bool UdpChannel::open() {
    if (_opened.load())
        return true;

    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (!socket) {
        _opened.store(false);
        return false;
    }

    uint32_t yes = 1;

    setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    int flags = fcntl(_socket, F_GETFL, 0);
    fcntl(_socket, F_SETFL, flags | O_NONBLOCK);

    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_socket, (const sockaddr *) &addr, sizeof(addr)) != 0) {
        ::close(_socket);
        _opened.store(false);
        return false;
    }

    _opened.store(true);

    return true;
}

bool UdpChannel::close() {
    if (!_opened.load())
        return true;

    ::close(_socket)        ;

    _opened.store(false);

    return true;
}

bool UdpChannel::getData(std::vector<uint8_t>& data) {
    uint32_t bytesAvailable;

    if (ioctl(_socket, FIONREAD, &bytesAvailable) == 0 && bytesAvailable > 0) {
        sockaddr_in addr;
        socklen_t size = sizeof(addr);
        data.resize(bytesAvailable);
        
        int bytesRead = recvfrom(_socket, data.data(), bytesAvailable, 0, (sockaddr *) &addr, &size);

        if (bytesRead != bytesAvailable)
            data.resize(bytesRead);

        return true;
    }

    return false;
}

}
