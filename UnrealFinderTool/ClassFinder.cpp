#include "pch.h"
#include "NamesStore.h"
#include "ClassFinder.h"

std::vector<uintptr_t> ClassFinder::Find(const uintptr_t gObjAddress, const uintptr_t gNamesAddress, const std::string& objectType)
{
	std::vector<uintptr_t> ret;

	// Dump GObjects
	ObjectsStore::Initialize(gObjAddress, false);

	// Dump GNames
	NamesStore::Initialize(gNamesAddress, false);

	for each (UEObject var in FindThatObject(objectType))
		ret.push_back(reinterpret_cast<uintptr_t>(var.GetAddress()));

	return ret;
}

std::vector<UEObject> ClassFinder::FindThatObject(const std::string& typeName, const bool firstOnly)
{
	std::vector<UEObject> ret;

	for (size_t i = 0; i < ObjectsStore().GetObjectsNum(); ++i)
	{
		auto object = ObjectsStore().GetById(i);
		if (!object.IsValid()) continue;

		if (object.IsA(typeName))
		{
			ret.push_back(object);
			if (firstOnly) break;
		}
	}

	return ret;
}
