#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

int main()
{
    libconfig::Config cfg;

    try{
        cfg.readFile("./config.cfg");
    }
    catch(const FileIOException& fioex){
        std::cerr << "I/O error reading file." << std::endl;
        return (EXIT_FAILURE);
    }
    catch(const ParseException& pex){
        std::cerr << "Parse error at" << pex.getFile()
                    << ":"<<pex.getLine() << "-"
                    << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    //read version from config
    try{
        string version = cfg.lookup("version");

        int data = cfg.lookup("data");
        cout << "data" << data << endl;
        cout << "version" << version << endl << endl;
    }
    catch(const SettingNotFoundException& nfex){
        cerr << "NO version setting is config file" << endl;
    }
    // read group
    try{
        const Setting& log = cfg.lookup("log");
        string logpath1;
        log.lookupValue("log_path",logpath1);

        cout << "log path" << logpath1 << endl << endl;

        string logpath = cfg.lookup("log.log_path");
        cout << "log path" << logpath << endl;

        int64_t log_size = cfg.lookup("log.log_size");
        cout << "log size" << log_size << endl;

        int log_level = cfg.lookup("log.log_level");
        cout << "log level" << log_level << endl;
    }
    catch(const SettingNotFoundException& nfex){
        cerr << "NO log setting is config file" << endl;
    }

    //read list 

    try{
        const Setting& server = cfg.lookup("server");
        int count = server.getLength();
        cout << "server.count = " << count << endl;

        for(int i = 0; i < count; i++){
            string addr = "";
            int port = 0;
            if(!server[i].lookupValue("addr",addr)
               || !server[i].lookupValue("port",port))
            {
                cerr << "lookupValue error" << endl;
                continue;
            }
            cout << "server[" << i << "]" << addr << ":"
                 << port << endl;
        }
        {
            string addr = "";
            int port = 0;
            if(cfg.lookupValue("server[0].addr",addr)
                || cfg.lookupValue("server[0].port", port))
                cerr << "lookupValue 'server.[0].addr' error" << endl;
            else
                cout << "server[0] = " << addr << ":" << port << endl << endl;
        }
       
    }
    catch(const SettingNotFoundException& nfex){
        cerr << "NO log setting is config file" << endl;
    }
    //read test
    try{
        const Setting& root = cfg.getRoot();
        const Setting& uin = root["test"]["uin"];
        int count = uin.getLength();
        cout << "uin.length=" << count << endl;

        const Setting& test = cfg.lookup("test");
        const Setting& test2 = cfg.lookup("test.uin");
        for(int i = 0; i < count; i++){
            int64_t u = test["uin"][i];
            int64_t uu = uin[i];
            int64_t uuu = test2[i];
             cout << "uin[" << i << "] = " << u << ", " << uu << ", " << uuu << endl;
        }

        const Setting& server = root["test"]["server"];
        string addr = "";
        int port = 0;
        if (!server.lookupValue("addr", addr)
                || !server.lookupValue("port", port))
        {
            cerr << "test server lookupValue error" << endl;
        }
        else
            cout << "test server = " << addr << ":" << port << endl << endl;
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "test setting mistake in configuration file." << endl;
    }
    return 0;
}
