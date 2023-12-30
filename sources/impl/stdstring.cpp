#include <assert.h>
#include <sstream>
#include "impl/stdstring.h"
using namespace std;

static string* StringFactory(asUINT length, const char *s)
{
	return new string(s);
}

static void StringFactory_Generic(asIScriptGeneric* gen)
{
    asUINT length = gen->GetArgDWord(0);
    const char* s = (const char*)gen->GetArgAddress(1);
    string* ret = StringFactory(length, s);
    gen->SetReturnAddress(ret);
}

static void ConstructString(string *thisPointer)
{
	new(thisPointer) string();
}

static void ConstructString_Generic(asIScriptGeneric* gen)
{
    string* thisPointer = (string*)gen->GetObject();
    ConstructString(thisPointer);
}

static void DestructString(string *thisPointer)
{
    // TODO: This may not be sufficient to reclaim the string's memory.
	thisPointer->~string();
}

static void DestructString_Generic(asIScriptGeneric* gen)
{
    string* thisPointer = (string*)gen->GetObject();
    DestructString(thisPointer);
}

static void Assignment_Generic(asIScriptGeneric* gen)
{
    string* thisPointer = (string*)gen->GetObject();
    string* rhs = (string*)gen->GetArgAddress(0);
    *thisPointer = *rhs;
}

static void AddAssignment_Generic(asIScriptGeneric* gen)
{
    string* thisPointer = (string*)gen->GetObject();
    string* rhs = (string*)gen->GetArgAddress(0);
    *thisPointer += *rhs;
}

static void Equal_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    bool ret = *lhs == *rhs;
    gen->SetReturnDWord(ret);
}

static void NotEqual_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    bool ret = *lhs != *rhs;
    gen->SetReturnDWord(ret);
}

static void LessEqual_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    bool ret = *lhs <= *rhs;
    gen->SetReturnDWord(ret);
}

static void GreaterEqual_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    bool ret = *lhs >= *rhs;
    gen->SetReturnDWord(ret);
}

static void Less_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    bool ret = *lhs < *rhs;
    gen->SetReturnDWord(ret);
}

static void Greater_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    bool ret = *lhs > *rhs;
    gen->SetReturnDWord(ret);
}

static void Add_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    string* ret = new string(*lhs + *rhs);
    gen->SetReturnAddress(ret);
}

static void Size_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    size_t ret = self->size();
    gen->SetReturnDWord((asUINT)ret);
}

static string &AssignBitsToString(unsigned int i, string &dest)
{
	ostringstream stream;
	stream << hex << i;
	dest = stream.str();
	return dest;
}

static void AssignBitsToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    unsigned int i = gen->GetArgDWord(0);
    AssignBitsToString(i, *self);
    gen->SetReturnAddress(self);
}

static string &AddAssignBitsToString(unsigned int i, string &dest)
{
	ostringstream stream;
	stream << hex << i;
	dest += stream.str();
	return dest;
}

static void AddAssignBitsToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    unsigned int i = gen->GetArgDWord(0);
    AddAssignBitsToString(i, *self);
    gen->SetReturnAddress(self);
}

static string AddStringBits(string &str, unsigned int i)
{
	ostringstream stream;
	stream << hex << i;
	str += stream.str();
	return str;
}

static void AddStringBits_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    unsigned int rhs = gen->GetArgDWord(1);
    string* ret = new string(AddStringBits(*lhs, rhs));
    gen->SetReturnAddress(ret);
}

static string AddBitsString(unsigned int i, string &str)
{
	ostringstream stream;
	stream << hex << i;
	return stream.str() + str;
}

static void AddBitsString_Generic(asIScriptGeneric* gen)
{
    unsigned int lhs = gen->GetArgDWord(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    string* ret = new string(AddBitsString(lhs, *rhs));
    gen->SetReturnAddress(ret);
}

static string &AssignUIntToString(unsigned int i, string &dest)
{
	ostringstream stream;
	stream << i;
	dest = stream.str();
	return dest;
}

static void AssignUIntToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    unsigned int i = gen->GetArgDWord(0);
    AssignUIntToString(i, *self);
    gen->SetReturnAddress(self);
}

static string &AddAssignUIntToString(unsigned int i, string &dest)
{
	ostringstream stream;
	stream << i;
	dest += stream.str();
	return dest;
}

static void AddAssignUIntToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    unsigned int i = gen->GetArgDWord(0);
    AddAssignUIntToString(i, *self);
    gen->SetReturnAddress(self);
}

static string AddStringUInt(string &str, unsigned int i)
{
	ostringstream stream;
	stream << i;
	str += stream.str();
	return str;
}

static void AddStringUInt_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    unsigned int rhs = gen->GetArgDWord(1);
    string* ret = new string(AddStringUInt(*lhs, rhs));
    gen->SetReturnAddress(ret);
}

static string AddIntString(int i, string &str)
{
	ostringstream stream;
	stream << i;
	return stream.str() + str;
}

static void AddIntString_Generic(asIScriptGeneric* gen)
{
    int lhs = gen->GetArgDWord(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    string* ret = new string(AddIntString(lhs, *rhs));
    gen->SetReturnAddress(ret);
}

static string &AssignIntToString(int i, string &dest)
{
	ostringstream stream;
	stream << i;
	dest = stream.str();
	return dest;
}

static void AssignIntToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    int i = gen->GetArgDWord(0);
    AssignIntToString(i, *self);
    gen->SetReturnAddress(self);
}

static string &AddAssignIntToString(int i, string &dest)
{
	ostringstream stream;
	stream << i;
	dest += stream.str();
	return dest;
}

static void AddAssignIntToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    int i = gen->GetArgDWord(0);
    AddAssignIntToString(i, *self);
    gen->SetReturnAddress(self);
}

static string AddStringInt(string &str, int i)
{
	ostringstream stream;
	stream << i;
	str += stream.str();
	return str;
}

static void AddStringInt_Generic(asIScriptGeneric* gen)
{
    string* lhs = (string*)gen->GetArgAddress(0);
    int rhs = gen->GetArgDWord(1);
    string* ret = new string(AddStringInt(*lhs, rhs));
    gen->SetReturnAddress(ret);
}

static string AddUIntString(unsigned int i, string &str)
{
	ostringstream stream;
	stream << i;
	return stream.str() + str;
}

static void AddUIntString_Generic(asIScriptGeneric* gen)
{
    unsigned int lhs = gen->GetArgDWord(0);
    string* rhs = (string*)gen->GetArgAddress(1);
    string* ret = new string(AddUIntString(lhs, *rhs));
    gen->SetReturnAddress(ret);
}

static string &AssignDoubleToString(double f, string &dest)
{
	ostringstream stream;
	stream << f;
	dest = stream.str();
	return dest;
}

static void AssignDoubleToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    double f = gen->GetArgDouble(0);
    AssignDoubleToString(f, *self);
    gen->SetReturnAddress(self);
}

static string &AddAssignDoubleToString(double f, string &dest)
{
	ostringstream stream;
	stream << f;
	dest += stream.str();
	return dest;
}

static void AddAssignDoubleToString_Generic(asIScriptGeneric* gen)
{
    string* self = (string*)gen->GetObject();
    double f = gen->GetArgDouble(0);
    AddAssignDoubleToString(f, *self);
    gen->SetReturnAddress(self);
}

static string AddStringDouble(string &str, double f)
{
	ostringstream stream;
	stream << f;
	str += stream.str();
	return str;
}

static void AddStringDouble_Generic(asIScriptGeneric* gen)
{
    string* s = (string*)gen->GetArgAddress(0);
    double f = gen->GetArgDouble(1);
    string* ret = new string(AddStringDouble(*s, f));
    gen->SetReturnAddress(ret);
}

static string AddDoubleString(double f, string &str)
{
	ostringstream stream;
	stream << f;
	return stream.str() + str;
}

static void AddDoubleString_Generic(asIScriptGeneric* gen)
{
    double f = gen->GetArgDouble(0);
    string* s = (string*)gen->GetArgAddress(1);
    string* ret = new string(AddDoubleString(f, *s));
    gen->SetReturnAddress(ret);
}

void RegisterStdString(asIScriptEngine *engine)
{
	int r;

	// Register the bstr type
	r = engine->RegisterObjectType("string", sizeof(string), asOBJ_CLASS_CDA); assert( r >= 0 );

	// Register the bstr factory
	r = engine->RegisterStringFactory("string", asFUNCTION(StringFactory_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT,  "void f()",              asFUNCTION(ConstructString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_DESTRUCT,   "void f()",              asFUNCTION(DestructString_Generic),  asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ASSIGNMENT, "string &f(string &in)", asFUNCTION(Assignment_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ADD_ASSIGN, "string &f(string &in)", asFUNCTION(AddAssignment_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Register the global operator overloads
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,       "bool f(string &in, string &in)", asFUNCTION(Equal_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,    "bool f(string &in, string &in)", asFUNCTION(NotEqual_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LEQUAL,      "bool f(string &in, string &in)", asFUNCTION(LessEqual_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GEQUAL,      "bool f(string &in, string &in)", asFUNCTION(GreaterEqual_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_LESSTHAN,    "bool f(string &in, string &in)", asFUNCTION(Less_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_GREATERTHAN, "bool f(string &in, string &in)", asFUNCTION(Greater_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(string &in, string &in)", asFUNCTION(Add_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Register the object methods
	r = engine->RegisterObjectMethod("string", "uint length()", asFUNCTION(Size_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Automatic conversion from values
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ASSIGNMENT, "string &f(double)", asFUNCTION(AssignDoubleToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ADD_ASSIGN, "string &f(double)", asFUNCTION(AddAssignDoubleToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(string &in, double)", asFUNCTION(AddStringDouble_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(double, string &in)", asFUNCTION(AddDoubleString_Generic), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ASSIGNMENT, "string &f(int)", asFUNCTION(AssignIntToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ADD_ASSIGN, "string &f(int)", asFUNCTION(AddAssignIntToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(string &in, int)", asFUNCTION(AddStringInt_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(int, string &in)", asFUNCTION(AddIntString_Generic), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ASSIGNMENT, "string &f(uint)", asFUNCTION(AssignUIntToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ADD_ASSIGN, "string &f(uint)", asFUNCTION(AddAssignUIntToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(string &in, uint)", asFUNCTION(AddStringUInt_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(uint, string &in)", asFUNCTION(AddUIntString_Generic), asCALL_GENERIC); assert( r >= 0 );

	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ASSIGNMENT, "string &f(bits)", asFUNCTION(AssignBitsToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_ADD_ASSIGN, "string &f(bits)", asFUNCTION(AddAssignBitsToString_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(string &in, bits)", asFUNCTION(AddStringBits_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD,         "string f(bits, string &in)", asFUNCTION(AddBitsString_Generic), asCALL_GENERIC); assert( r >= 0 );
}


