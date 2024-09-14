/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/lib/arguments.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Function to check if an option has been parsed
int32_t fossil_arg_parse_has(fossil_option_t* options, int32_t num_options, const char*  option_name) {
    for (int32_t i = 0; i < num_options; ++i) {
        if (strcmp(option_name, options[i].name) == 0 && options[i].parsed) {
            return 1; // Option has been parsed
        }
    }
    return 0; // Option not found or not parsed
}

void fossil_arg_parse_usage(const char* program_name, fossil_option_t* options, int32_t num_options) {
    if (!program_name || !options) {
        fprintf(stderr, "Error: Invalid program name or options.\n");
        return;
    }

    printf("Usage: %s [options]\n\nOptions:\n", program_name);
    for (int32_t i = 0; i < num_options; ++i) {
        if (!options[i].name) {
            fprintf(stderr, "Error: Invalid option name.\n");
            continue;
        }

        printf("  -%s", options[i].name);
        switch (options[i].type) {
            case COPTION_TYPE_INT:
                printf(" <int>");
                break;
            case COPTION_TYPE_STRING:
                printf(" <string>");
                break;
            case COPTION_TYPE_BOOL:
                printf(" (flag)");
                break;
            case COPTION_TYPE_COMBO:
                printf(" {%s}", ((fossil_combo_choice_t*)options[i].extra_data)[0].name);
                for (int j = 1; j < options[i].num_choices; ++j) {
                    printf("|%s", ((fossil_combo_choice_t*)options[i].extra_data)[j].name);
                }
                break;
            case COPTION_TYPE_FEATURE:
                printf(" {enable|disable|auto}");
                break;
            default:
                fprintf(stderr, "Error: Invalid option type.\n");
        }
        printf("\n");
    }
}

void fossil_arg_parse(fossil_command_line_t* cmd, fossil_option_t* options, int32_t num_options) {
    if (!cmd || !options) {
        fprintf(stderr, "Error: Invalid command line or options.\n");
        return;
    }

    for (int32_t i = 1; i < cmd->argc; ++i) {
        const char* arg = cmd->argv[i];
        if (arg[0] == '-') {
            // Parse options
            for (int32_t j = 0; j < num_options; ++j) {
                if (strcmp(arg + 1, options[j].name) == 0) {
                    options[j].parsed = 1; // Mark the option as parsed
                    switch (options[j].type) {
                        case COPTION_TYPE_INT:
                            if (i + 1 < cmd->argc) {
                                options[j].value.int_val = atoi(cmd->argv[++i]);
                            } else {
                                fprintf(stderr, "Error: Missing argument for option '-%s'.\n", options[j].name);
                            }
                            break;
                        case COPTION_TYPE_STRING:
                            if (i + 1 < cmd->argc) {
                                options[j].value.str_val = cmd->argv[++i];
                            } else {
                                fprintf(stderr, "Error: Missing argument for option '-%s'.\n", options[j].name);
                            }
                            break;
                        // Handle other option types similarly
                        default:
                            fprintf(stderr, "Error: Unsupported option type.\n");
                    }
                    break; // Found and parsed the option, move to the next argument
                }
            }
        }
    }
}


void fossil_arg_check_unrecognized(fossil_command_line_t* cmd, fossil_option_t* options, int32_t num_options) {
    for (int32_t i = 1; i < cmd->argc; ++i) {
        const char* arg = cmd->argv[i];
        if (arg[0] == '-') {
            int32_t recognized = 0;
            for (int32_t j = 0; j < num_options; ++j) {
                if (strcmp(arg + 1, options[j].name) == 0) {
                    recognized = 1;
                    break;
                }
            }
            if (!recognized) {
                fprintf(stderr, "Error: Unrecognized option '%s'\n", arg);
                exit(EXIT_FAILURE);
            }
        }
    }
}

void fossil_arg_print_parsed_options(fossil_option_t* options, int32_t num_options) {
    for (int32_t i = 0; i < num_options; ++i) {
        printf("Option: %s, Parsed: %s\n", options[i].name, options[i].parsed ? "true" : "false");
    }
}

void fossil_arg_reset_parsed_flags(fossil_option_t* options, int32_t num_options) {
    for (int32_t i = 0; i < num_options; ++i) {
        options[i].parsed = 0;
    }
}

// Function to create combo choices
fossil_combo_choice_t* fossil_arg_create_fossil_combo_choice_ts(const char* names[], const int32_t values[], int32_t num_choices) {
    fossil_combo_choice_t* choices = malloc(num_choices * sizeof(fossil_combo_choice_t));
    if (!choices) {
        fprintf(stderr, "Memory allocation error for combo choices.\n");
        exit(EXIT_FAILURE);
    }

    for (int32_t i = 0; i < num_choices; ++i) {
        choices[i].name = names[i];
        choices[i].value = values[i];
    }

    return choices;
}

// Function to create options
fossil_option_t* fossil_arg_create_options(const char* names[], fossil_option_type_t types[], fossil_option_value_t values[], void* extra_data[], int32_t num_options) {
    fossil_option_t* options = malloc(num_options * sizeof(fossil_option_t));
    if (!options) {
        fprintf(stderr, "Memory allocation error for options.\n");
        exit(EXIT_FAILURE);
    }

    for (int32_t i = 0; i < num_options; ++i) {
        options[i].name = names[i];
        options[i].type = types[i];
        options[i].value = values[i];
        options[i].extra_data = extra_data[i];
        options[i].parsed = 0;
        options[i].num_choices = 0;
    }

    return options;
}
