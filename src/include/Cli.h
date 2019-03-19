/**
 * @file Cli.h
 * 
 * @author
 * Angelo Elias Dalzotto (150633@upf.br)
 * GEPID - Grupo de Pesquisa em Cultura Digital (gepid.upf.br)
 * Universidade de Passo Fundo (upf.br)
 * 
 * @brief Headers to the command-line interface for the berimbau-tool.
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

#ifndef _CLI_H_
#define _CLI_H_

#include <iostream>

class Cli {
public:
    /**
     * @brief Runs the CLI
     * 
     * @param argc Main argument counter to parser.
     * @param argv Pointer to char arrays for parsing.
     * 
     * @return 0 if success.
     *         Refer to create_rec() to error codes.
     */
    static int run(int &argc, char *argv[]);

private:
    /**
     * Enum Option
     * Controls the parsed options
     */
    enum class Option {
        CREATE
    };

    static Option opt;
    static std::string fname;

    /**
     * @brief Parse the CLI arguments.
     * 
     * @param argc Main argument counter to parser.
     * @param argv Pointer to char arrays for parsing.
     * 
     * @return  0 if success.
     *         -1 if invalid parameter.
     *         -2 if invalid option.
     *         -3 if no input file specified.
     */
    static int parse_args(int &argc, char *argv[]);

    /**
     * @brief Prints the CLI usage in case of parse_args failure.
     */
    static void print_usage();

    /**
     * @brief Creates a recording based on user input.
     * 
     * @return 0 if success.
     *         Refer to BerimbauTool::create() for error codes.
     */
    static int create_rec();

};

#endif /* _CLI_H_ */