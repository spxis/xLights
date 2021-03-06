#include "ScanObject.h"

#include <wx/socket.h>
#include "../xLights/UtilFunctions.h"

#include <log4cpp/Category.hh>

void IPObject::CheckPort80()
{
    _port80 = false;

    wxIPV4address addr;
    addr.Hostname(_ip);
    addr.Service(80);

    wxSocketClient* const client = new wxSocketClient(wxSOCKET_WAITALL | wxSOCKET_BLOCK);
    if (client != nullptr) {
        client->SetTimeout(5);

        if (client->Connect(addr)) {
            _port80 = true;
            _pinged = true; // even if ping previously failed ... now we have connected to it it is obviously ok.
        }
        delete client;
    }
}

IPObject::IPObject(const std::string& ip, const std::string& viaProxy, bool pinged)
{
    _ip = ip;
    _viaProxy = viaProxy;
    CheckPort80(); 
    _pinged = pinged;
}

bool IPObject::InSameSubnet(const std::string& ip) const
{
    return IsInSameSubnet(_ip, ip);
}

bool IPObject::operator<(const IPObject& ip2)
{
    wxIPV4address i1;
    wxIPV4address i2;
    i1.Hostname(_ip);
    i2.Hostname(ip2._ip);

    return (((sockaddr_in*)i1.GetAddressData())->sin_addr.s_addr <
            ((sockaddr_in*)i2.GetAddressData())->sin_addr.s_addr);
}
