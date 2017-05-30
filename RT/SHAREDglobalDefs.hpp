/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: SHAREDglobalDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3k4a 21-May-2017
 * Description: Generic Construct Functions: shared global definitions (configure to compile different BAI projects)
 *
 *******************************************************************************/


#ifndef HEADER_SHARED_GLOBAL_DEFS
#define HEADER_SHARED_GLOBAL_DEFS


class SHAREDglobalDefsClass
{
};

	/**********
	SOURCE PROJECT VARIABLES;
	***********/

	//current/active projects;
//#define COMPILE_UNREAL_PROJECT
//#define COMPILE_CF		//compileCF.bat -> CF.exe
#define COMPILE_NLC		//makefile.NLC -> NLC.exe
//#define COMPILE_GIA		//makefile.GIA -> GIA.exe
//#define COMPILE_OR		//makefile.ATOR -> ATOR.exe
//#define COMPILE_CS		//makefile.CS -> CS.exe
//#define COMPILE_RT		//makefile.RT -> RT.exe
//#define COMPILE_ANN_WITH_RT	//makefile.ANNwithRT -> ANNwithRT.exe
//#define COMPILE_ANN		//makefile.ANN -> ANN.exe
//#define COMPILE_OLC		//compileOLC.bat -> OLC.exe



	/**********
	OS DEPENDENT VARIABLES;
	***********/

#define LINUX
#ifndef LINUX
	//else assume windows (affects default parts directory only - this is ISO C++ so it should compile on any platform)
	//#include <windows.h>	//incompatible with LDjpeg.hpp (must only include windows.h when need to)
#endif

#define SQL_MYSQL_VERSION_5_7_PLUS

	/**********
	COMPILATION TYPE DEPENDENT VARIABLES;
	***********/

#ifdef COMPILE_UNREAL_PROJECT
	#define USE_UNREAL
	#define USE_RT
	#ifdef LINUX
		#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/PARTS/"
		#define DEFAULT_PARTS_PRIMITIVES_DIRECTORY_FULL_PATH "/usr/share/local/LDRAW/P/"
	#else
		#define DEFAULT_PARTS_DIRECTORY_FULL_PATH "D:/Program Files (x86)/LDraw/PARTS/parts/"
		#define DEFAULT_PARTS_PRIMITIVES_DIRECTORY_FULL_PATH "D:/Program Files (x86)/LDraw/PARTS/p/"
	#endif
#endif

#ifdef COMPILE_CF
	#define USE_CF
#endif

#ifdef COMPILE_NLC
	#define USE_NLC
	#define USE_GIA
#endif

#ifdef COMPILE_GIA_WITH_CE
	#define USE_GIA
	#define USE_CE
#endif
#ifdef COMPILE_GIA
	#define USE_GIA
#endif
#ifdef USE_GIA
	#define USE_RT
#endif

#ifdef COMPILE_CS
	#define USE_CS
#endif
#ifdef USE_CS
	#define USE_RT
#endif

#ifdef COMPILE_OR
	#define USE_OR
#endif
#ifdef USE_OR
	#define USE_RT
#endif

#ifdef COMPILE_ANN
	#define USE_ANN
#endif
#ifdef COMPILE_ANN_WITH_RT
	#define USE_ANN
	#define USE_RT
#endif

#ifdef COMPILE_RT
	#define USE_RT
#endif


#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#ifdef USE_GIA
#include <unordered_map>	//requires C++11
#include <utility> // make_pair
#endif
#include <algorithm>
#include <stack>
#include <map>
#include <limits>
#include <sstream>
#include <iomanip>
using namespace std;



	//ANN, LRRC, + OR;
//Test variables (need optimisation)
#define MAX_ANN_BACK_PROPAGATION_ERROR (1000.0)



	//ASCII variables
#define CHAR_TAB '\t'
#define CHAR_COMMA ','
#define CHAR_NEWLINE '\n'
#define CHAR_OPEN_BRACKET '('
#define CHAR_CLOSE_BRACKET ')'
#define CHAR_OPEN_SQUARE_BRACKET '['
#define CHAR_CLOSE_SQUARE_BRACKET ']'
#define CHAR_DASH '-'
#define CHAR_VERTICAL_BAR '|'
#define CHAR_UNDERSCORE '_'
#define CHAR_SPACE ' '
#define CHAR_END_OF_STRING '\0'
#define CHAR_DEL (127)
#define CHAR_IRRELEVANT (CHAR_DEL)
#define CHAR_FORWARDSLASH '/'
#define CHAR_FULLSTOP '.'
#define CHAR_SEMICOLON ';'
#define CHAR_COLON ':'
#define CHAR_QUESTIONMARK '?'
#define CHAR_STAR '*'
#define CHAR_INVERTED_COMMAS '"'
#define CHAR_APOSTROPHE '\''
#define CHAR_BACKSLASH '\\'
#define CHAR_EQUALS '='
#define CHAR_INVERTEDCOMMAS '"'
#define CHAR_DECIMALPLACE (CHAR_FULLSTOP)
#define CHAR_DOLLAR '$'

#define STRING_TAB "\t"
#define STRING_NEW_LINE "\n"
#define STRING_SPACE " "
#define STRING_FULLSTOP "."
#define STRING_COMMA ","
#define STRING_INVERTEDCOMMAS "\""
#define STRING_APOSTROPHE "'"
#define STRING_INVERTED_COMMAS "\""

#define TM_STRUCT_YEAR_OFFSET 1900

#define INT_DEFAULT_VALUE (-1)
#define CPP_STRING_FIND_RESULT_FAIL_VALUE string::npos	//-1
#define BOOL_IRRELEVANT (false)
#define INT_IRRELEVANT (0)
#define BOOL_UNKNOWN_LEGACY (false)

#define EXIT_OK (0)
#define EXIT_ERROR (1)

#define EXE_FOLDER_PATH_MAX_LENGTH (1000)
extern string exeFolder;
extern string inputFolder;
extern string outputFolder;

#define constEffective

#endif

