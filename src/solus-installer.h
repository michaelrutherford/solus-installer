/* Copyright 2015 Michael Rutherford
*
* This file is part of solus-installer.
*
* solus-installer is free software: you can redistribute it
* and/or modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation, either version 2 of the
* License, or (at your option) any later version.
*
* solus-installer is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with solus-installer. If not, see http://www.gnu.org/licenses/.
*/

#ifndef solus_installer_h
#define solus_installer_h

#define WINDOW_X 750
#define WINDOW_Y 350
#define DIALOG_X 250
#define DIALOG_Y 250
#define ENTRY_WIDTH 15
#define ALIGN_LEFT 0

struct timezone {
        char *continent[20];
        char *location[25];
        char *utc[10];
};

#endif
