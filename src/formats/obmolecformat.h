/**********************************************************************
Copyright (C) 2005 Chris Morley

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
***********************************************************************/
#ifndef OB_MOLECULEFORMAT_H
#define OB_MOLECULEFORMAT_H

#include "mol.h"
#include "obconversion.h"

namespace OpenBabel {
///A format which converts to and/or from OBMol can derive from this class
///To save duplicating the code below.
///Derive from OBFormat if the object converted is not OBMol or 
///if interaction with the framework is required during the execution 
///of ReadMolecule() or WriteMolecule(), as for example in CMLFormat

class OBMoleculeFormat : public OBFormat
{
public:
	/// The "Convert" interface functions
	virtual bool ReadChemObject(OBConversion* pConv)
	{
		OBMol* pmol = new OBMol;
		bool ret=ReadMolecule(pmol,pConv);
		if(ret) //Do transformation and return molecule
			pConv->AddChemObject(pmol->DoTransformations(pConv->GetGeneralOptions()));
		else
			pConv->AddChemObject(NULL);
		return ret;
	};
	
	virtual bool WriteChemObject(OBConversion* pConv)
	{
		//Retrieve the target OBMol
		OBBase* pOb = pConv->GetChemObject();
		OBMol* pmol = dynamic_cast<OBMol*> (pOb);
		bool ret=false;
		if(pmol)
			ret=WriteMolecule(pmol,pConv);
		delete pOb; 
		return ret;
	};
};

}
#endif //OB_MOLECULEFORMAT_H