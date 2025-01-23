#include "Arduino.hpp"
#include <string>

bool CArduino::ConnectToPort()
{
    this->handle = CreateFile(this->port, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (!this->handle)
        return false;

    DCB dcb = {};
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(this->handle, &dcb))
        return false;

    dcb.BaudRate = CBR_128000;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;

    if (!SetCommState(this->handle, &dcb))
        return false;

    return true;
}

bool CArduino::SendCmd(const std::vector<char>& params)
{
    std::string cmd(params.size(), 'x');
    for (int i = 0; i < params.size(); ++i) {
        cmd.at(i) = params.at(i);
    }

    DWORD written = 0;
    return WriteFile(this->handle, cmd.c_str(), cmd.length(), &written, nullptr);
}