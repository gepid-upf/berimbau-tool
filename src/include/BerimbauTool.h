/**
 * @file BerimbauTool.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @brief Berimbau-tool is a software to manage the recordings of the "Berimbau"
 * toy. This is the header to the tool API.
 * 
 * @copyright
 * Copyright 2019 Angelo Elias Dalzotto
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

#ifndef _BERIMBAU_TOOL_H_
#define _BERIMBAU_TOOL_H_

#include <string>
#include <vector>

class BerimbauTool {
public:
    /**
     * Instrument options enumerator.
     * Has the same values of the embedded device.
     */
    enum class Instrument {
        CAXIXI,
        MOEDA,
        PRESA,
        SOLTA
    };

    /**
     * Definition of the data structure of the recordings.
     * Has the same values of the embedded device.
     */
    struct beat_t {
        uint32_t d_time;
        uint16_t res0;
        uint8_t instr;
        uint8_t res1;
    };

    /**
     * @brief Creates a recording based on a user .csv file.
     * 
     * @details The .csv must be structure as follows:
     *          # Indicates a commentary that will be ignored
     *          time(ms),[caxixi,moeda,presa,solta]
     *          # Example
     *          0,caxixi
     *          500,solta,
     *          1000,presa
     * 
     * @param fname The input csv file name.
     * 
     * @return  0 if success.
     *          1 if input file not existent.
     *          2 if invalid column number. Sets the line_no to the invalid row.
     *          3 if time column is not a integer. Sets line_no to invalid row and line_value to invalid value.
     *          4 if instrument not recognized. Sets line_no to invalid row and line_value to invalid text.
     */
    static int create(std::string &fname);

    /**
     * @brief Gets the row number of the csv input error.
     *
     * @return The number of the row the error has occurred.
     */
    static unsigned int get_error_line() { return line_no; }

    /**
     * @brief Gets the value that caused the error in the csv file.
     * 
     * @return The string that caused the error.
     */
    static std::string get_error_value() { return line_value; }

private:
    static unsigned int line_no;
    static std::string line_value;
};

#endif /* _BERIMBAU_TOOL_H_ */