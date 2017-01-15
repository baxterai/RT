/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
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
 * File Name: LDsvg.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3i15a 11-August-2016
 *
 *******************************************************************************/


#ifndef HEADER_LD_SVG
#define HEADER_LD_SVG

#include "SHAREDglobalDefs.h"
#include "SHAREDvars.h"
#include "LDreferenceClass.h"
#include "XMLparserClass.h"

bool writeSVGfile(string xmlFileName, XMLparserTag* firstTagInXMLfile);
bool writeSVGfile(string xmlFileName, XMLparserTag* firstTagInXMLfile, int viewBoxMinX, int viewBoxMaxX, int viewBoxMinY, int viewBoxMaxY);
	void writeSVGheader(ofstream* writeFileObject, int viewBoxMinX, int viewBoxMaxX, int viewBoxMinY, int viewBoxMaxY);
	void writeSVGfooter(ofstream* writeFileObject);
void writeSVGline(XMLparserTag** currentTag, vec* pos1, vec* pos2, int col);
void writeSVGbox(XMLparserTag** currentTag, vec* pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse);
void writeSVGtext(XMLparserTag** currentTag, string text, vec* pos, int fontSize, int col);
void writeSVGboxTransparent(XMLparserTag** currentTag, vec* pos, double width, double height, int col, double boxOutlineWidth, bool useEllipse, double fillOpacity);
XMLparserTag* writeSVGgroup(XMLparserTag** currentTag, string* groupID);
void writeSVGconnector(XMLparserTag** currentTag, vec* pos1, vec* pos2, int col, string* startGroupID, string* endGroupID, double width);
string convertColourRGBtoHexString(colour* colourRGB);

#endif

