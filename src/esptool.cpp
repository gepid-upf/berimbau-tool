/**
 * @file esptool.cpp
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @brief A C++ wrapper for python2 esptool.py.
 * 
 * @copyright
 * Copyright (C) 2014-2016 Fredrik Ahlberg, Angus Gratton, Espressif Systems (Shanghai) PTE LTD, other contributors as noted.
 * https://github.com/espressif/esptool
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <esptool.h>
#include <python2.7/Python.h>
#include <cstdlib>
#include <sstream>

#include <iostream>

std::string ESPTool::err_msg;

std::string ESPTool::get_esptool()
{
    char *idf_path = getenv("IDF_PATH");
    if(!idf_path)
        return std::string();

    std::ostringstream esptool;
    esptool << idf_path << "/components/esptool_py/esptool/esptool.py";
    return esptool.str();
}

int ESPTool::read_flash(uint32_t address, uint32_t size, std::string filename)
{
    std::string esptool = get_esptool();
    if(esptool.empty()){
        err_msg = "esptool.py not found";
        return 1;   // Not found.
    }

    long unsigned int lens[] = {esptool.size(), std::string("read_flash").size(),
                    std::to_string(address).size(), std::to_string(size).size(),
                    filename.size() };

    char *argv[5];
    for(int i = 0; i < 5; i++)
        argv[i] = new char[lens[i]];
    
    strcpy(argv[0], esptool.c_str());
    strcpy(argv[1], "read_flash");
    strcpy(argv[2], std::to_string(address).c_str());
    strcpy(argv[3], std::to_string(size).c_str());
    strcpy(argv[4], filename.c_str());

    return run_esptool(5, argv);
}

int ESPTool::write_flash(uint32_t address, std::string filename)
{
    std::string esptool = get_esptool();
    if(esptool.empty()){
        err_msg = "esptool.py not found";
        return 1;   // Not found.
    }

    long unsigned int lens[] = {esptool.size(), std::string("write_flash").size(),
                                std::to_string(address).size(), filename.size() };

    char *argv[4];
    for(int i = 0; i < 4; i++)
        argv[i] = new char[lens[i]];
    
    strcpy(argv[0], esptool.c_str());
    strcpy(argv[1], "write_flash");
    strcpy(argv[2], std::to_string(address).c_str());
    strcpy(argv[3], filename.c_str());

    return run_esptool(4, argv);
}

int ESPTool::run_esptool(int argc, char *argv[])
{
    Py_Initialize();

    PySys_SetArgv(argc, argv); // Sets esptool.py path and args

    // Import whole esptool.py
    PyObject *src = PyString_FromString("esptool");
    PyObject *mod = PyImport_Import(src);
    if(!mod){
        PyObject *type, *value, *tb;
        PyErr_Fetch(&type, &value, &tb);
        err_msg = PyString_AS_STRING(value);
        return 2;
    }

    // Get context from module
    PyObject *dict = PyModule_GetDict(mod);
    if(!dict){
        PyObject *type, *value, *tb;
        PyErr_Fetch(&type, &value, &tb);
        err_msg = PyString_AS_STRING(value);
        return 3;
    }

    // Get function from context
    PyObject *func = PyDict_GetItemString(dict, "main");

    if (!PyCallable_Check(func)){
        err_msg = "Impossível chamar função";
        return 4;
    }

    PyObject_CallObject(func, NULL);

    if(PyErr_Occurred()){
        PyObject *type, *value, *tb;
        PyErr_Fetch(&type, &value, &tb);
        err_msg = PyString_AS_STRING(PyObject_Str(value));
        return 5;
    }

    Py_Finalize();

    return 0;
}