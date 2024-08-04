#include "gdrtmidiout.h"

using namespace godot;

void GDRtMidiOut::_bind_methods() {
	ClassDB::bind_method(D_METHOD("initialize", "api", "client_name"), &GDRtMidiOut::initialize);
	ClassDB::bind_method(D_METHOD("get_current_api"), &GDRtMidiOut::getCurrentApi);
	ClassDB::bind_method(D_METHOD("open_port", "portNumber", "portName"), &GDRtMidiOut::openPort);
	ClassDB::bind_method(D_METHOD("close_port"), &GDRtMidiOut::closePort);
	ClassDB::bind_method(D_METHOD("is_port_open"), &GDRtMidiOut::isPortOpen);
	ClassDB::bind_method(D_METHOD("open_virtual_port", "portName"), &GDRtMidiOut::openVirtualPort);
	ClassDB::bind_method(D_METHOD("get_port_count"), &GDRtMidiOut::getPortCount);
	ClassDB::bind_method(D_METHOD("get_port_name", "portNumber"), &GDRtMidiOut::getPortName);
	ClassDB::bind_method(D_METHOD("send_message", "message"), &GDRtMidiOut::sendMessage);
	// ClassDB::bind_method(D_METHOD("set_error_callback", "errorCallback", "userData"), &GDRtMidiOut::setErrorCallback);
}

GDRtMidiOut::GDRtMidiOut()
{
}

GDRtMidiOut::~GDRtMidiOut()
{
}

void GDRtMidiOut::_init()
{
}

void GDRtMidiOut::_process(float delta)
{
}

/*********** API ***********/

void GDRtMidiOut::initialize(int api, String clientName)
{
    try
    {
        auto c_name = std::string(clientName.utf8().get_data());
        auto api_ = static_cast<RtMidi::Api>(api);
        midiout = std::unique_ptr<RtMidiOut>(new RtMidiOut(api_, c_name));
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
    catch ( const std::exception& e )
    {
        ERR_PRINT(e.what());
    }
}

int GDRtMidiOut::getCurrentApi()
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return -1;
    }
    try
    {
        RtMidi::Api api = this->midiout->getCurrentApi();
        return static_cast<int>(api);
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
    return -1;
}

void GDRtMidiOut::openPort(unsigned int portNumber, String portName)
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return;
    }
    try
    {
        unsigned int u_pnum = (unsigned int)portNumber;
        std::string p_name = std::string(portName.utf8().get_data());
        this->midiout->openPort(portNumber, p_name);
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
}

void GDRtMidiOut::closePort(void)
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return;
    }
    try
    {
        this->midiout->closePort();
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
}

bool GDRtMidiOut::isPortOpen() const
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return false;
    }
    try
    {
        return this->midiout->isPortOpen();
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
    return false;
}

void GDRtMidiOut::openVirtualPort(const String portName)
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return;
    }
    try
    {
        auto p_name = std::string(portName.utf8().get_data());
        this->midiout->openVirtualPort(p_name);
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
}

unsigned int GDRtMidiOut::getPortCount(void)
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return 0;
    }
    try
    {
        return this->midiout->getPortCount();
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }

    return 0;
}

godot::String GDRtMidiOut::getPortName(unsigned int portNumber)
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return godot::String("");
    }
    try
    {
        std::string p_name = this->midiout->getPortName(portNumber);
        return godot::String(p_name.c_str());
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }

    return godot::String("");
}

void GDRtMidiOut::sendMessage(PackedByteArray message)
{
    if (!this->midiout)
    {
        ERR_PRINT("Run initialize() first");
        return;
    }
    if (message.size() <= 0)
        return;
    try
    {
        std::vector<unsigned char> c_msg;
        for (int i = 0; i < message.size(); i++)
        {
            auto decoded = message.decode_u8(i);
            c_msg.push_back(decoded);
        }
        this->midiout->sendMessage(&c_msg);
    }
    catch (RtMidiError e)
    {
        ERR_PRINT(e.getMessage().c_str());
    }
}

// void GDRtMidiOut::setErrorCallback(RtMidiErrorCallback errorCallback, void *userData)
// {
//     if (!this->midiout)
//     {
//         ERR_PRINT("Run initialize() first");
//         return;
//     }
//     try
//     {
//         this->midiout->setErrorCallback(errorCallback, userData);
//     }
//     catch (RtMidiError e)
//     {
//         ERR_PRINT(e.getMessage().c_str());
//     }
// }

/*********** API ***********/
