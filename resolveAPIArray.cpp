#include "plugin.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>

static bool cbCommand(int argc, char* argv[])
{
    duint addr = 0, size = 0;

    if (argc < 3 || !DbgFunctions()->ValFromString(argv[1], &addr) || !DbgFunctions()->ValFromString(argv[2], &size))
    {
        _plugin_logputs("[" PLUGIN_NAME "] Error: Use an address as arg1 and number of entries as arg2.\n");
        return false;
    }

    int offset = 0x0;

   //Create CSV structure
    std::ofstream myfile;
    myfile.open("resolveAPIArray.csv");
    myfile << "Address,Offset,API,\n";

    for (int i = 0; i < size; i++) {
        std::stringstream ss_offset;
        ss_offset << std::hex << offset;
        std::string offset_str = ss_offset.str();
        //_plugin_logputs(offset_str.c_str());

        std::stringstream ss_addr;
        ss_addr << std::hex << addr;
        std::string addr_str = ss_addr.str();


        char label[MAX_STRING_SIZE] = "";
        DbgGetLabelAt((addr + offset), SEG_DEFAULT, label);
        std::stringstream ss_label;
        ss_label << label;
        std::string label_str = ss_label.str();
        std::string ouput_str = label_str;
        ouput_str.append(" - ");
        ouput_str.append(offset_str);
        ouput_str.append(" - ");
        ouput_str.append(addr_str);
        _plugin_logputs(ouput_str.c_str());

        //Write output to csv
        myfile << addr_str + "," + offset_str + "," + label_str + ",\n";

        offset = offset + 0x4;
    }
    myfile.close();

   
}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    if (!_plugin_registercommand(pluginHandle, PLUGIN_NAME, cbCommand, false))
        _plugin_logputs("[" PLUGIN_NAME "] Error registering the \"" PLUGIN_NAME "\" command!");
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here (clearing menus optional).
bool pluginStop()
{
    return true;
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}
