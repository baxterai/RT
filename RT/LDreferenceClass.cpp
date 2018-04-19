/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LDreferenceClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Generic Ldraw Construct Functions
 * Project Version: 3m13b 22-February-2018
 * /
 *******************************************************************************/


/*LDreferenceClass.cpp: Defines a class for references to submodels/parts/units within a scene file*/

#ifdef COMPILE_UNREAL_PROJECT //comment with COMPILE_UNREAL_PROJECT
#include "ldrawVRv0.h"
#endif //comment with COMPILE_UNREAL_PROJECT
#include "LDreferenceClass.hpp"



LDreference::LDreference(void)
{
	initialiseLDreference("", 0, false);
}

LDreference::LDreference(string referenceName, int referenceColour, bool createNewSubmodel)
{
	initialiseLDreference(referenceName, referenceColour, createNewSubmodel);
}

LDreference::LDreference(string referenceName, int referenceColour, bool createNewSubmodel, bool topLevel)
{
	initialiseLDreference(referenceName, referenceColour, createNewSubmodel);
	#ifdef USE_UNREAL
	isTopLevel = topLevel;
	#endif
}

LDreference::LDreference(bool createNewSubmodel)
{
	initialiseLDreference("", 0, createNewSubmodel);
}

LDreference::~LDreference()
{
	/*
	#ifdef USE_LRRC
	if(subModelDetails != NULL)
	{
		delete subModelDetails;
	}
	#endif
	if(firstReferenceWithinSubModel != NULL)
	{
		delete firstReferenceWithinSubModel;
	}
	if(next != NULL)
	{
		delete next;
	}
	*/
}

void LDreference::initialiseLDreference(string referenceName, int referenceColour, bool createNewSubmodel)
{

	//Define default values for LDreference

	relativePosition.x = 0.0;
	relativePosition.y = 0.0;
	relativePosition.z = 0.0;

	absolutePosition.x = 0.0;
	absolutePosition.y = 0.0;
	absolutePosition.z = 0.0;

		//deformationMatrix initialisations here are required for bcc32 compiler
	deformationMatrix.a.x = 1.0;
	deformationMatrix.a.y = 0.0;
	deformationMatrix.a.z = 0.0;
	deformationMatrix.b.x = 0.0;
	deformationMatrix.b.y = 1.0;
	deformationMatrix.b.z = 0.0;
	deformationMatrix.c.x = 0.0;
	deformationMatrix.c.y = 0.0;
	deformationMatrix.c.z = 1.0;

	absoluteDeformationMatrix.a.x = 1.0;
	absoluteDeformationMatrix.a.y = 0.0;
	absoluteDeformationMatrix.a.z = 0.0;
	absoluteDeformationMatrix.b.x = 0.0;
	absoluteDeformationMatrix.b.y = 1.0;
	absoluteDeformationMatrix.b.z = 0.0;
	absoluteDeformationMatrix.c.x = 0.0;
	absoluteDeformationMatrix.c.y = 0.0;
	absoluteDeformationMatrix.c.z = 1.0;

	#ifdef USE_UNREAL
	relativeColourString = "";

	isTopLevel = false;

	intermediatePosition.x = 0.0;
	intermediatePosition.y = 0.0;
	intermediatePosition.z = 0.0;

	intermediateDeformationMatrix.a.x = 1.0;
	intermediateDeformationMatrix.a.y = 0.0;
	intermediateDeformationMatrix.a.z = 0.0;
	intermediateDeformationMatrix.b.x = 0.0;
	intermediateDeformationMatrix.b.y = 1.0;
	intermediateDeformationMatrix.b.z = 0.0;
	intermediateDeformationMatrix.c.x = 0.0;
	intermediateDeformationMatrix.c.y = 0.0;
	intermediateDeformationMatrix.c.z = 1.0;

	vertex1intermediatePosition.x = 0.0;
	vertex1intermediatePosition.y = 0.0;
	vertex1intermediatePosition.z = 0.0;
	vertex2intermediatePosition.x = 0.0;
	vertex2intermediatePosition.y = 0.0;
	vertex2intermediatePosition.z = 0.0;
	vertex3intermediatePosition.x = 0.0;
	vertex3intermediatePosition.y = 0.0;
	vertex3intermediatePosition.z = 0.0;
	vertex4intermediatePosition.x = 0.0;
	vertex4intermediatePosition.y = 0.0;
	vertex4intermediatePosition.z = 0.0;

	//#ifdef LDRAW_VR_IO_OPTIMISATION
	partAdditional = false;
	partModified = false;
	partDeleted = false;
	//#endif
	#endif

	colour = referenceColour;
	name = referenceName;
	next = NULL;
	isSubModelReference = false;

#ifdef USE_RT
	absoluteColour = DAT_FILE_DEFAULT_COLOUR;
#endif

		/*new parameters added to parseFile() 18-mar-07*/
	vertex1relativePosition.x = 0.0;
	vertex1relativePosition.y = 0.0;
	vertex1relativePosition.z = 0.0;
	vertex2relativePosition.x = 0.0;
	vertex2relativePosition.y = 0.0;
	vertex2relativePosition.z = 0.0;
	vertex3relativePosition.x = 0.0;
	vertex3relativePosition.y = 0.0;
	vertex3relativePosition.z = 0.0;
	vertex4relativePosition.x = 0.0;
	vertex4relativePosition.y = 0.0;
	vertex4relativePosition.z = 0.0;
	vertex1absolutePosition.x = 0.0;
	vertex1absolutePosition.y = 0.0;
	vertex1absolutePosition.z = 0.0;
	vertex2absolutePosition.x = 0.0;
	vertex2absolutePosition.y = 0.0;
	vertex2absolutePosition.z = 0.0;
	vertex3absolutePosition.x = 0.0;
	vertex3absolutePosition.y = 0.0;
	vertex3absolutePosition.z = 0.0;
	vertex4absolutePosition.x = 0.0;
	vertex4absolutePosition.y = 0.0;
	vertex4absolutePosition.z = 0.0;

	vertex1absolutePositionBackup.x = 0.0;
	vertex1absolutePositionBackup.y = 0.0;
	vertex1absolutePositionBackup.z = 0.0;
	vertex2absolutePositionBackup.x = 0.0;
	vertex2absolutePositionBackup.y = 0.0;
	vertex2absolutePositionBackup.z = 0.0;
	vertex3absolutePositionBackup.x = 0.0;
	vertex3absolutePositionBackup.y = 0.0;
	vertex3absolutePositionBackup.z = 0.0;
	vertex4absolutePositionBackup.x = 0.0;
	vertex4absolutePositionBackup.y = 0.0;
	vertex4absolutePositionBackup.z = 0.0;
	referenceEnabledMethod2DOD = true;

	type = REFERENCE_TYPE_UNDEFINED;

	/*Additional values used with recursive parser*/

	if(createNewSubmodel)
	{
		#ifdef USE_LRRC
		subModelDetails = new ModelDetails();
		#endif
		firstReferenceWithinSubModel = NULL;
	}
	else
	{
		#ifdef USE_LRRC
		subModelDetails = NULL;
		#endif
		firstReferenceWithinSubModel = NULL;
	}
}

void LDreferenceClassClass::copyReferencePosition(LDreference* r, LDreference* referenceToCopy)
{
	r->relativePosition.x = referenceToCopy->relativePosition.x;
	r->relativePosition.y = referenceToCopy->relativePosition.y;
	r->relativePosition.z = referenceToCopy->relativePosition.z;
	r->absolutePosition.x = referenceToCopy->absolutePosition.x;
	r->absolutePosition.y = referenceToCopy->absolutePosition.y;
	r->absolutePosition.z = referenceToCopy->absolutePosition.z;
}



int LDreferenceClassClass::obtainReferencePlayerID(const LDreference* referenceInThisPhaseStartSceneFile)
{
	#ifdef GAME_USE_FILENAME_AS_UNIQUE_UNIT_IDS
	return referenceInThisPhaseStartSceneFile->colour;
	#endif
	#ifdef GAME_USE_COLOUR_AS_UNIQUE_UNIT_IDS
	return (referenceInThisPhaseStartSceneFile->colour)%10;		//Eg the player ID is the least significant bits
	#endif

	return 1;
}

void LDreferenceClassClass::convertLdrawColourToDatFileRGB(const int dataFileColour, colour* col)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;


	if(dataFileColour == DAT_FILE_COLOUR_BLACK)
	{
		r = DAT_FILE_COLOUR_BLACK_RGB_R;
		g = DAT_FILE_COLOUR_BLACK_RGB_G;
		b = DAT_FILE_COLOUR_BLACK_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_BLUE)
	{
		r = DAT_FILE_COLOUR_BLUE_RGB_R;
		g = DAT_FILE_COLOUR_BLUE_RGB_G;
		b = DAT_FILE_COLOUR_BLUE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_GREEN)
	{
		r = DAT_FILE_COLOUR_GREEN_RGB_R;
		g = DAT_FILE_COLOUR_GREEN_RGB_G;
		b = DAT_FILE_COLOUR_GREEN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_CYAN)
	{
		r = DAT_FILE_COLOUR_CYAN_RGB_R;
		g = DAT_FILE_COLOUR_CYAN_RGB_G;
		b = DAT_FILE_COLOUR_CYAN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_RED)
	{
		r = DAT_FILE_COLOUR_RED_RGB_R;
		g = DAT_FILE_COLOUR_RED_RGB_G;
		b = DAT_FILE_COLOUR_RED_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_MAGENTA)
	{
		r = DAT_FILE_COLOUR_MAGENTA_RGB_R;
		g = DAT_FILE_COLOUR_MAGENTA_RGB_G;
		b = DAT_FILE_COLOUR_MAGENTA_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_BROWN)
	{
		r = DAT_FILE_COLOUR_BROWN_RGB_R;
		g = DAT_FILE_COLOUR_BROWN_RGB_G;
		b = DAT_FILE_COLOUR_BROWN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_LIGHTGREY)
	{
		r = DAT_FILE_COLOUR_LIGHTGREY_RGB_R;
		g = DAT_FILE_COLOUR_LIGHTGREY_RGB_G;
		b = DAT_FILE_COLOUR_LIGHTGREY_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKGREY)
	{
		r = DAT_FILE_COLOUR_DARKGREY_RGB_R;
		g = DAT_FILE_COLOUR_DARKGREY_RGB_G;
		b = DAT_FILE_COLOUR_DARKGREY_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_YELLOW)
	{
		r = DAT_FILE_COLOUR_YELLOW_RGB_R;
		g = DAT_FILE_COLOUR_YELLOW_RGB_G;
		b = DAT_FILE_COLOUR_YELLOW_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_WHITE)
	{
		r = DAT_FILE_COLOUR_WHITE_RGB_R;
		g = DAT_FILE_COLOUR_WHITE_RGB_G;
		b = DAT_FILE_COLOUR_WHITE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_ORANGE)
	{
		r = DAT_FILE_COLOUR_ORANGE_RGB_R;
		g = DAT_FILE_COLOUR_ORANGE_RGB_G;
		b = DAT_FILE_COLOUR_ORANGE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_PURPLE)
	{
		r = DAT_FILE_COLOUR_PURPLE_RGB_R;
		g = DAT_FILE_COLOUR_PURPLE_RGB_G;
		b = DAT_FILE_COLOUR_PURPLE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKBLUE)
	{
		r = DAT_FILE_COLOUR_DARKBLUE_RGB_R;
		g = DAT_FILE_COLOUR_DARKBLUE_RGB_G;
		b = DAT_FILE_COLOUR_DARKBLUE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKGREEN)
	{
		r = DAT_FILE_COLOUR_DARKGREEN_RGB_R;
		g = DAT_FILE_COLOUR_DARKGREEN_RGB_G;
		b = DAT_FILE_COLOUR_DARKGREEN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKRED)
	{
		r = DAT_FILE_COLOUR_DARKRED_RGB_R;
		g = DAT_FILE_COLOUR_DARKRED_RGB_G;
		b = DAT_FILE_COLOUR_DARKRED_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKYELLOW)
	{
		r = DAT_FILE_COLOUR_DARKYELLOW_RGB_R;
		g = DAT_FILE_COLOUR_DARKYELLOW_RGB_G;
		b = DAT_FILE_COLOUR_DARKYELLOW_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_AQUA)
	{
		r = DAT_FILE_COLOUR_AQUA_RGB_R;
		g = DAT_FILE_COLOUR_AQUA_RGB_G;
		b = DAT_FILE_COLOUR_AQUA_RGB_B;
	}
	#ifdef USE_UNREAL
	else if(dataFileColour == DAT_FILE_DEFAULT_COLOUR)
	{
		r = DAT_FILE_COLOUR_DEFAULT_RGB_R;
		g = DAT_FILE_COLOUR_DEFAULT_RGB_G;
		b = DAT_FILE_COLOUR_DEFAULT_RGB_B;
	}
	else
	{
		cerr << "invalid dat file colour for conversion to RGB" << endl;
		cerr << "dataFileColour = " << dataFileColour << endl;
		r = DAT_FILE_COLOUR_DEFAULT_RGB_R;
		g = DAT_FILE_COLOUR_DEFAULT_RGB_G;
		b = DAT_FILE_COLOUR_DEFAULT_RGB_B;
	}
	#else
	else
	{
		cerr << "invalid dat file colour for conversion to RGB" << endl;
		cerr << "dataFileColour = " << dataFileColour << endl;
		exit(EXIT_ERROR);
	}
	#endif


	col->r = r;
	col->g = g;
	col->b = b;

}




