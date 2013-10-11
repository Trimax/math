#include "../mathkernel/constants.h"

#include <string>

/* Integration result structure */
struct Expression
{
  char *expression;
  double s, f, p;

  double r;
  int err;
};

extern "C" DllExport void __stdcall Integrate( struct Expression *expr );

extern "C" DllExport void __stdcall Sample( int a );

