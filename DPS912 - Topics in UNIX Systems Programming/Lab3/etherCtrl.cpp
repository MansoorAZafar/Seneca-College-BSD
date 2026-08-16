#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unordered_map>
#include <functional>

#define NAME_SIZE 16

using namespace std;

enum class Requests {
    IP_ADDRESS,
    NETWORK_MASK,
    BROADCAST_ADDRESS,
    MAC_ADDRESS,
    MTU
};

template <class T>
T getNetworkInformation(
    int fd,
    unsigned long request,
    int key,
    ifreq &ifr,
    const std::unordered_map<int, void*> &map,
    std::function<bool(ifreq&)> filter = nullptr
) {
    int ret = ioctl(fd, request, &ifr);
    if (ret < 0) {
        strerror(errno);
        return nullptr;
    } else if (filter != nullptr && !filter(ifr)) return nullptr;

    return reinterpret_cast<T>(map.at(key));
}

int main() {
    int fd;
    int selection;
    struct ifreq ifr;
    char if_name[NAME_SIZE];
    unsigned char *mac = NULL;

    const std::unordered_map<int, void*> map{
        {static_cast<int>(Requests::IP_ADDRESS), &ifr.ifr_addr},
        {static_cast<int>(Requests::NETWORK_MASK), &ifr.ifr_netmask},
        {static_cast<int>(Requests::BROADCAST_ADDRESS), &ifr.ifr_broadaddr},
        {static_cast<int>(Requests::MAC_ADDRESS), &ifr.ifr_hwaddr.sa_data},
        {static_cast<int>(Requests::MTU), &ifr.ifr_mtu}
    };

    std::unordered_map<int, std::string> cache{};
    const auto printNetworkInformation = [&](unsigned long request, Requests key, const char *prefix) {
        const int keyValue = static_cast<int>(key);
        if (cache.find(keyValue) == cache.end()) {
            const sockaddr_in* rawValue = getNetworkInformation<sockaddr_in*>(fd, request, keyValue, ifr, map);
            if (rawValue == nullptr)
                return;

            const char *value = inet_ntoa(rawValue->sin_addr);
            cache[keyValue] = value;
        }

        std::cout << prefix << cache[keyValue] << "\n";
    };

    cout << "Enter the interface name: ";
    cin >> if_name;

    size_t if_name_len = strlen(if_name);
    if (if_name_len < sizeof(ifr.ifr_name)) {
        memcpy(ifr.ifr_name, if_name, if_name_len);
        ifr.ifr_name[if_name_len] = 0;
    }
    else {
        cout << "Interface name is too long!" << endl;
        return -1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        cout << strerror(errno);
        return -1;
    }

    system("clear");
    do {
        cout << "Choose from the following:" << endl;
        cout << "1. Hardware address" << endl;
        cout << "2. IP address" << endl;
        cout << "3. Network mask" << endl;
        cout << "4. Broadcast address" << endl;
        cout << "5. MTU" << endl;
        cout << "0. Exit" << endl
             << endl;
        cin >> selection;
        switch (selection)
        {
        case 1:
            mac = getNetworkInformation<unsigned char*>(fd, SIOCGIFHWADDR, 3, ifr, map, [](ifreq& r){
                if (r.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
                    std::cout << "not an Ethernet interface\n";
                    return false;
                } 
                return true;
            });
            if(mac != nullptr) printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
            break;
        case 2:
            printNetworkInformation(SIOCGIFADDR, Requests::IP_ADDRESS, "IP Address: ");
            break;
        case 3:
            printNetworkInformation(SIOCGIFNETMASK, Requests::NETWORK_MASK, "Network Mask: ");
            break;
        case 4:
            printNetworkInformation(SIOCGIFBRDADDR, Requests::BROADCAST_ADDRESS, "Broadcast Address: ");
            break;
        case 5:
            int* mtu = getNetworkInformation<int*>(fd, SIOCGIFMTU, 4, ifr, map);
            std::cout << "MTU: " << *mtu << "\n";
            break;

        }
        if (selection != 0) {
            char key;
            cout << "Press any key to continue: ";
            cin >> key;
            system("clear");
        }
    } while (selection != 0);

    close(fd);
    return 0;
}
