//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_LOG_H
#define CORE_LOG_H

#include "Console.h"

#define PRINT(...) Core::Console::WriteLine(__VA_ARGS__);


#define SUCCESS(...) Core::Console::SetMode(CONSOLE_MODE_SUCCESS); \
                     Core::Console::WriteLine(__VA_ARGS__); \
                     Core::Console::SetMode(CONSOLE_MODE_NORMAL);

#define WARNING(...) Core::Console::SetMode(CONSOLE_MODE_WARNING); \
                     Core::Console::WriteLine(__VA_ARGS__); \
                     Core::Console::SetMode(CONSOLE_MODE_NORMAL);

#define PERROR(...) Core::Console::SetMode(CONSOLE_MODE_ERROR); \
                    Core::Console::WriteLine(); \
                    Core::Console::WriteLine("(", __FUNCTION__, ")"); \
                    Core::Console::WriteLine(__VA_ARGS__); \
                    Core::Console::WriteLine(); \
                    Core::Console::SetMode(CONSOLE_MODE_NORMAL);

#endif // !CORE_LOG_H